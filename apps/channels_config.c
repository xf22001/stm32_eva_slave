

/*================================================================
 *
 *
 *   文件名称：channels_config.c
 *   创 建 者：肖飞
 *   创建日期：2021年01月18日 星期一 09时26分44秒
 *   修改日期：2022年09月06日 星期二 09时44分45秒
 *   描    述：
 *
 *================================================================*/
#include "channels_config.h"
#include "os_utils.h"
#include "ntc_temperature.h"
#include "main.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern ADC_HandleTypeDef hadc1;

static energy_meter_config_item_t energy_meter_config_item_0_0 = {
	.type = ENERGY_METER_TYPE_DC,
	.huart = &huart3,
};

static energy_meter_config_item_t *energy_meter_config_item_0_sz[] = {
	&energy_meter_config_item_0_0,
};

static function_board_config_item_t function_board_config_item_0_0 = {
	.type = FUNCTION_BOARD_TYPE_485,
	.huart = &huart3,
};

static function_board_config_item_t *function_board_config_item_0_sz[] = {
	&function_board_config_item_0_0,
};

static channel_config_t channel0_config = {
	.channel_type = CHANNEL_TYPE_PROXY_LOCAL,
	.charger_config = {
		.charger_type = CHANNEL_CHARGER_BMS_TYPE_GB_MULTI_CHARGE,
		.hcan_bms = &hcan2,
		.output_relay_gpio = relay_6_GPIO_Port,
		.output_relay_pin = relay_6_Pin,
		.charger_lock_state_gpio = in_1_GPIO_Port,
		.charger_lock_state_pin = in_1_Pin,
		.relay_charger_lock_gpio = relay_3_GPIO_Port,
		.relay_charger_lock_pin = relay_3_Pin,
		.charger_auxiliary_power_choose_gpio = relay_4_GPIO_Port,
		.charger_auxiliary_power_choose_pin = relay_4_Pin,
		.charger_auxiliary_power_onoff_gpio = relay_5_GPIO_Port,
		.charger_auxiliary_power_onoff_pin = relay_5_Pin,
	},
	.energy_meter_config = {
		.default_type = ENERGY_METER_TYPE_NONE,
		.energy_accuracy = VALUE_ACCURACY_2,
		.voltage_accuracy = VALUE_ACCURACY_1,
		.curent_accuracy = VALUE_ACCURACY_3,
		.size = ARRAY_SIZE(energy_meter_config_item_0_sz),
		.items = energy_meter_config_item_0_sz,
	},
	.function_board_config = {
		.default_type = FUNCTION_BOARD_TYPE_485,
		.size = ARRAY_SIZE(function_board_config_item_0_sz),
		.items = function_board_config_item_0_sz,
	},
	.cp_gpio = in_a_cc1_GPIO_Port,
	.cp_pin = in_a_cc1_Pin,
	.cp_connect_state = GPIO_PIN_SET,
};

static channel_config_t *channel_config_sz[] = {
	&channel0_config,
};

//static card_reader_config_item_t card_reader_config_item_0 = {
//	.type = CARD_READER_TYPE_ZLG,
//	.huart = &huart2,
//};

static card_reader_config_item_t card_reader_config_item_0 = {
	.type = CARD_READER_TYPE_PSEUDO,
	.huart = NULL,
};

static card_reader_config_item_t *card_reader_config_item_sz[] = {
	&card_reader_config_item_0,
};

static channels_config_t channels_config_0 = {
	.id = 0,
	.channel_number = ARRAY_SIZE(channel_config_sz),
	.channel_config = channel_config_sz,
	.voice_config = {
	},
	.card_reader_config = {
		.default_type = CARD_READER_TYPE_PSEUDO,
		.size = ARRAY_SIZE(card_reader_config_item_sz),
		.items = card_reader_config_item_sz,
	},
	.display_config = {
		//.huart = &huart6,
	},
	.proxy_channel_info = {
		.hcan = &hcan1,
	},
	.multi_charge_info = {
		.hcan = &hcan1,
	},
	.board_temperature_adc = &hadc1,
	.board_temperature_adc_rank = 0,
};

static channels_config_t *channels_config_sz[] = {
	&channels_config_0,
};

channels_config_t *get_channels_config(uint8_t id)
{
	int i;
	channels_config_t *channels_config = NULL;
	channels_config_t *channels_config_item = NULL;

	for(i = 0; i < ARRAY_SIZE(channels_config_sz); i++) {
		channels_config_item = channels_config_sz[i];

		if(channels_config_item->id == id) {
			channels_config = channels_config_item;
			break;
		}
	}

	return channels_config;
}

int adc_value_helper(adc_value_type_t adc_value_type, uint16_t adc_value)
{
	int value = 0;

	switch(adc_value_type) {
		case ADC_VALUE_TYPE_BOARD_TEMPERATURE: {
			value = get_ntc_temperature(10000, adc_value, 4095);
		}
		break;

		case ADC_VALUE_TYPE_CP_AD_VOLTAGE: {
			value = adc_value * 3300 / 4096;//0v-1.2v 采样 0v-12v

			//(V - 0.5) * 2 / 102 * 8 * 4 / 3 = u
			//V - 0.5 = u / (2 / 102 * 8 * 4 / 3)
			//修正前
			//V = u / (2 / 102 * 8 * 4 / 3) + 0.5
			//修正后
			//V = u / (1.8667 / 101.8667 * 8 * 4 / 3) + 0.5

			value = value * 5.1159817458616805 / 10 + 50;
		}
		break;

		default: {
			app_panic();
		}
		break;
	}

	return value;
}
