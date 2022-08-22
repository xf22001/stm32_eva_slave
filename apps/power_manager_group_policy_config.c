

/*================================================================
 *
 *
 *   文件名称：power_manager_group_policy_config.c
 *   创 建 者：肖飞
 *   创建日期：2022年07月22日 星期五 12时30分44秒
 *   修改日期：2022年08月22日 星期一 15时22分47秒
 *   描    述：
 *
 *================================================================*/
#include "power_manager_group_policy_chain.h"

#include "power_manager.h"
#include "main.h"

#include "log.h"

void power_manager_restore_config(channels_info_t *channels_info)
{
	int i;
	int j;

	channels_config_t *channels_config = channels_info->channels_config;
	channels_settings_t *channels_settings = &channels_info->channels_settings;
	power_manager_settings_t *power_manager_settings = &channels_settings->power_manager_settings;

	channels_settings->power_module_settings.power_module_type = channels_config->power_module_config.power_module_default_type;
	channels_settings->power_module_settings.rate_current = 21;
	channels_settings->power_manager_settings.type = channels_config->power_manager_config.power_manager_default_type;
	channels_settings->module_max_output_voltage = 10000;
	channels_settings->module_min_output_voltage = 2000;
	channels_settings->module_max_output_current = 1000;
	channels_settings->module_min_output_current = 3;
	channels_settings->module_max_input_voltage = 0;//2530;
	channels_settings->module_min_input_voltage = 0;//1870;
	channels_settings->module_max_output_power = 30000;
	channels_settings->channels_max_output_power = 300000;
	channels_settings->power_manager_group_policy = POWER_MANAGER_GROUP_POLICY_PRIORITY;

	power_manager_settings->power_manager_group_number = 1;

	debug("power_manager_group_number:%d", power_manager_settings->power_manager_group_number);

	for(i = 0; i < power_manager_settings->power_manager_group_number; i++) {
		power_manager_group_settings_t *power_manager_group_settings = &power_manager_settings->power_manager_group_settings[i];

		power_manager_group_settings->channel_number = 1;
		power_manager_group_settings->relay_board_number_per_channel = 0;

		for(j = 0; j < power_manager_group_settings->relay_board_number_per_channel; j++) {
			power_manager_group_settings->slot_per_relay_board[j] = 0;
		}

		power_manager_group_settings->power_module_group_number = 0;

		for(j = 0; j < power_manager_group_settings->power_module_group_number; j++) {
			power_module_group_settings_t *power_module_group_settings = &power_manager_group_settings->power_module_group_settings[j];
			power_module_group_settings->power_module_number = 0;
		}
	}
}

void channel_info_reset_default_config(channel_info_t *channel_info)
{
	channel_config_t *channel_config = channel_info->channel_config;
	channel_settings_t *channel_settings = &channel_info->channel_settings;

	memset(channel_settings, 0, sizeof(channel_settings_t));

	channel_settings->channel_type = channel_config->channel_type;
	channel_settings->charger_settings.charger_type = channel_config->charger_config.charger_type;
	channel_settings->energy_meter_settings.type = channel_config->energy_meter_config.default_type;
	channel_settings->energy_meter_settings.request_addr = channel_config->energy_meter_config.request_addr;
	channel_settings->energy_meter_settings.energy_accuracy = channel_config->energy_meter_config.energy_accuracy;
	channel_settings->energy_meter_settings.voltage_accuracy = channel_config->energy_meter_config.voltage_accuracy;
	channel_settings->energy_meter_settings.curent_accuracy = channel_config->energy_meter_config.curent_accuracy;
	channel_settings->function_board_type = channel_config->function_board_config.default_type;

	channel_settings->max_output_power = 6000000;

	channel_settings->max_output_voltage = 10000;
	channel_settings->min_output_voltage = 500;
	channel_settings->max_output_current = 5000;
	channel_settings->min_output_current = 3;

	channel_settings->multi_charge_settings.enable = 1;
	channel_settings->multi_charge_settings.group = 0;
	channel_settings->multi_charge_settings.id = 0;
}
