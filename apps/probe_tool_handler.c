

/*================================================================
 *
 *
 *   文件名称：probe_tool_handler.c
 *   创 建 者：肖飞
 *   创建日期：2020年03月20日 星期五 12时48分07秒
 *   修改日期：2022年08月12日 星期五 15时10分21秒
 *   描    述：
 *
 *================================================================*/
#include "probe_tool_handler.h"

#include <string.h>

#include "lwip/netdb.h"
#include "lwip/inet.h"

#include "flash.h"
#include "iap.h"
#include "app.h"
#include "ftp_client.h"
#include "channels.h"
#include "card_reader.h"

#include "sal_hook.h"

#define LOG_UDP
#include "log.h"

static void fn1(request_t *request)
{
	probe_server_chunk_sendto(request->payload.fn, (void *)0x8000000, 512);
}

#include "test_event.h"
static void fn2(request_t *request)
{
	try_get_test_event();
}

static void fn3(request_t *request)
{
	static uint32_t file_crc32 = 0;

	uint32_t data_size = request->header.data_size;
	uint32_t data_offset = request->header.data_offset;
	uint32_t total_size = request->header.total_size;
	uint32_t stage = request->payload.stage;
	uint8_t *data = (uint8_t *)(request + 1);
	uint8_t start_upgrade_app = 0;

	if(is_app() == 1) {
		if(set_app_valid(0) != 0) {
			debug("");
			return;
		}

		_printf("reset to bootloader!\n");

		HAL_NVIC_SystemReset();
		return;
	}

	if(stage == 0) {
		flash_erase_sector(IAP_CONST_FW_ADDRESS_START_SECTOR, IAP_CONST_FW_ADDRESS_SECTOR_NUMBER);
	} else if(stage == 1) {
		if(data_size == 4) {
			uint32_t *p = (uint32_t *)data;
			file_crc32 = *p;
		}
	} else if(stage == 2) {
		flash_write(IAP_CONST_FW_ADDRESS + data_offset, data, data_size);

		if(data_offset + data_size == total_size) {
			uint32_t read_offset = 0;
			uint32_t crc32 = 0;

			while(read_offset < total_size) {
				uint32_t i;
				uint32_t left = total_size - read_offset;
				uint32_t read_size = (left > 32) ? 32 : left;
				uint8_t *read_buffer = (uint8_t *)(IAP_CONST_FW_ADDRESS + read_offset);

				for(i = 0; i < read_size; i++) {
					crc32 += read_buffer[i];
				}

				read_offset += read_size;
			}

			_printf("crc32:%x, file_crc32:%x\n", crc32, file_crc32);

			if(crc32 == file_crc32) {
				start_upgrade_app = 1;
			}
		}
	}

	loopback(request);

	if(start_upgrade_app != 0) {
		_printf("start upgrade app!\n");

		if(set_firmware_size(total_size) != 0) {
			debug("");
		}

		if(set_firmware_valid(1) != 0) {
			debug("");
		}

		if(set_firmware_valid(0) != 0) {
			debug("");
		}

		if(set_app_valid(1) != 0) {
			debug("");
		}

		HAL_NVIC_SystemReset();
	}
}

static int p_host(struct hostent *ent)
{
	int ret = 0;
	char **cp;

	if(ent == NULL) {
		ret = -1;
		return ret;
	}

	_printf("\n");

	_printf("h_name:%s\n", ent->h_name);
	_printf("h_aliases:\n");
	cp = ent->h_aliases;

	while(*cp != NULL) {
		_printf("%s\n", *cp);
		cp += 1;

		if(*cp != NULL) {
			//_printf(", ");
		}
	}

	_printf("h_addrtype:%d\n", ent->h_addrtype);

	_printf("h_length:%d\n", ent->h_length);

	_printf("h_addr_list:\n");
	cp = ent->h_addr_list;

	while(*cp != NULL) {
		_printf("%s\n", inet_ntoa(**cp));
		cp += 1;

		if(*cp != NULL) {
			//_printf(", ");
		}
	}

	return ret;
}

static void get_host_by_name(char *content, uint32_t size)
{
	struct hostent *ent;
	char *hostname = (char *)os_calloc(1, RECV_BUFFER_SIZE);
	int ret;
	int fn;
	int catched;

	//_hexdump("content", (const char *)content, size);

	if(hostname == NULL) {
		return;
	}

	hostname[0] = 0;

	ret = sscanf(content, "%d %s%n", &fn, hostname, &catched);

	if(ret == 2) {
		_printf("hostname:%s!\n", hostname);
		ent = gethostbyname(hostname);
		p_host(ent);
	} else {
		_printf("no hostname!\n");
	}

	os_free(hostname);
}

static void fn4(request_t *request)
{
	const ip_addr_t *local_ip = get_default_ipaddr();
	_printf("local host ip:%s\n", inet_ntoa(*local_ip));

	get_host_by_name((char *)(request + 1), request->header.data_size);
	memset(request, 0, RECV_BUFFER_SIZE);
}

uint16_t osGetCPUUsage(void);
int get_brk_size(void);
static void fn5(request_t *request)
{
	int size = xPortGetFreeHeapSize();
	uint8_t *os_thread_info;
	uint32_t ticks = osKernelSysTick();
	uint16_t cpu_usage = osGetCPUUsage();
	size_t total_heap_size = get_total_heap_size();
	size_t heap_size;
	size_t heap_count;
	size_t heap_max_size;

	get_mem_info(&heap_size, &heap_count,  &heap_max_size);

	_printf("cpu usage:%d\n", cpu_usage);
	_printf("free os heap size:%d\n", size);
	_printf("brk size:%d\n", get_brk_size());
	_printf("total heap size:%d, free heap size:%d, used:%d, heap count:%d, max heap size:%d\n",
	        total_heap_size,
	        total_heap_size - heap_size,
	        heap_size,
	        heap_count,
	        heap_max_size);
	_printf("current ticks:%lu\n", ticks);
	_printf("%lu day %lu hour %lu min %lu sec\n",
	        ticks / (1000 * 60 * 60 * 24),//day
	        (ticks % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60),//hour
	        (ticks % (1000 * 60 * 60)) / (1000 * 60),//min
	        (ticks % (1000 * 60)) / (1000)//sec
	       );

	if(size < 4 * 1024) {
		return;
	}

	size = 1024;

	os_thread_info = (uint8_t *)os_calloc(1, size);

	if(os_thread_info == NULL) {
		return;
	}

	osThreadList(os_thread_info);

	_printf("%-15s\t%s\t%s\t%s\t%s\n", "name", "state", "prio", "stack", "no");
	_puts((const char *)os_thread_info);

	vTaskGetRunTimeStats((char *)os_thread_info);

	_printf("\n\n%-15s\t%s\t\t%s\n", "name", "count", "percent");
	_puts((const char *)os_thread_info);

	_printf("\n");

	os_free(os_thread_info);

	if(is_app() == 1) {
		_printf("in app!\n");
	} else {
		_printf("in bootloader!\n");
	}
}

static void fn6(request_t *request)
{
}

static void fn7(request_t *request)
{
	char *content = (char *)(request + 1);
	int fn;
	int op;
	int start;
	int size;
	int catched;
	int ret;

	ret = sscanf(content, "%d %d %d %d%n", &fn, &op, &start, &size, &catched);

	if(ret == 4) {
	}
}

static void fn8(request_t *request)
{
}

static void fn9(request_t *request)
{
}

//#include "test_https.h"
//void set_connect_enable(uint8_t enable);
static void fn10(request_t *request)
{
	//char *url = "https://httpbin.org/get";
	//char *url = "ws://192.168.41.2:8080/ocpp/";
	//char *url = "ws://47.244.218.210:8080/OCPP/echoSocket/13623";
	//char *url = "wss://35.201.125.176:433/SSECHINAEVSE";
	//char *url = "https://216.58.199.110";
	//char *url = "wss://ocpp-16-json.dev-plugitcloud.com/SSECHINAEVSE";
	//char *url = "wss://iot-ebus-ocpp-v16-server-test.azurewebsites.net/ws/test123";
	//test_https(url);
	//set_connect_enable(1);
}

//http://coolaf.com/tool/chattest
//11 0 ws://82.157.123.54:9010/ajaxchattest
//11 0 wss://echo.websocket.org
//11 0 tcp://112.74.40.227:12345
//11 0 udp://112.74.40.227:12345
static void fn11(request_t *request)
{
}

//12 10.42.0.1 2121 /user.mk anonymous
//12 10.42.0.1 2121 /user.mk user pass
//12 ftp.gnu.org 21 /gnu/tar/tar-1.32.tar.gz anonymous
//12 ftp.sjtu.edu.cn 21 /centos/2/centos2-scripts-v1.tar anonymous
static void fn12(request_t *request)
{
	char *content = (char *)(request + 1);
	int fn;
	int catched;
	int ret;
	ftp_server_path_t *ftp_server_path = (ftp_server_path_t *)os_alloc(sizeof(ftp_server_path_t));

	if(ftp_server_path == NULL) {
		return;
	}

	memset(ftp_server_path, 0, sizeof(ftp_server_path_t));

	ret = sscanf(content, "%d %s %s %s %s %s %n", &fn, ftp_server_path->host, ftp_server_path->port, ftp_server_path->path, ftp_server_path->user, ftp_server_path->password, &catched);

	debug("ret:%d", ret);

	if((ret == 6) || (ret == 5)) {
		debug("server host:\'%s\', server port:\'%s\', path\'%s\', user:\'%s\', password\'%s\'", ftp_server_path->host, ftp_server_path->port, ftp_server_path->path, ftp_server_path->user, ftp_server_path->password);
		request_ftp_client_download(ftp_server_path->host, ftp_server_path->port, ftp_server_path->path, ftp_server_path->user, ftp_server_path->password, FTP_CLIENT_ACTION_DOWNLOAD, NULL, NULL);
	}

	os_free(ftp_server_path);
}

static void fn13(request_t *request)
{
	char *content = (char *)(request + 1);
	int fn;
	int catched;
	int ret;
	struct tm tm;
	time_t ts;

	ret = sscanf(content, "%d %04d%02d%02d%02d%02d%02d %n",
	             &fn,
	             &tm.tm_year,
	             &tm.tm_mon,
	             &tm.tm_mday,
	             &tm.tm_hour,
	             &tm.tm_min,
	             &tm.tm_sec,
	             &catched);
	debug("ret:%d", ret);

	if(ret == 7) {
		tm.tm_year -= 1900;
		tm.tm_mon -= 1;
		ts = mktime(&tm);

		if(set_time(ts) == 0) {
			debug("set time successful!");
		} else {
			debug("set time failed!");
		}
	}

	ts = get_time();
	tm = *localtime(&ts);
	debug("tm %04d-%02d-%02d %02d:%02d:%02d",
	      tm.tm_year + 1900,
	      tm.tm_mon + 1,
	      tm.tm_mday,
	      tm.tm_hour,
	      tm.tm_min,
	      tm.tm_sec);
}

static void fn14(request_t *request)
{
	char *content = (char *)(request + 1);
	int fn;
	int channel_id;
	int type;//channel_event_type_t
	int catched;
	int ret;

	ret = sscanf(content, "%d %d %d %n",
	             &fn,
	             &channel_id,
	             &type,
	             &catched);
	debug("ret:%d", ret);

	if(ret == 3) {
	}
}

static void fn15(request_t *request)
{
	char *content = (char *)(request + 1);
	int fn;
	int catched;
	int ret;

	ret = sscanf(content, "%d %n",
	             &fn,
	             &catched);
	debug("ret:%d", ret);

	if(ret == 1) {
	}
}

static void fn16(request_t *request)
{
	char *content = (char *)(request + 1);
	int fn;
	int catched;
	int ret;

	ret = sscanf(content, "%d %n",
	             &fn,
	             &catched);
	debug("ret:%d", ret);

	if(ret == 1) {
	}
}

static void fn17(request_t *request)
{
	char *content = (char *)(request + 1);
	int fn;
	int catched;
	int ret;

	ret = sscanf(content, "%d %n", &fn, &catched);

	if(ret == 1) {
	}
}

static void fn18(request_t *request)
{
}

static server_item_t server_map[] = {
	{1, fn1},
	{2, fn2},
	{3, fn3},
	{4, fn4},
	{5, fn5},
	{6, fn6},
	{7, fn7},
	{8, fn8},
	{9, fn9},
	{10, fn10},
	{11, fn11},
	{12, fn12},
	{13, fn13},
	{14, fn14},
	{15, fn15},
	{16, fn16},
	{17, fn17},
	{18, fn18},
};

server_map_info_t server_map_info = {
	.server_map = server_map,
	.server_map_size = ARRAY_SIZE(server_map),
};
