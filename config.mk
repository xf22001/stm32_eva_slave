#
#
#================================================================
#   
#   
#   文件名称：config.mk
#   创 建 者：肖飞
#   创建日期：2021年08月26日 星期四 11时10分19秒
#   修改日期：2022年08月26日 星期五 15时41分02秒
#   描    述：
#
#================================================================

CONFIG_LIST := 

#CONFIG_LIST += USER_APP
#CONFIG_LIST += PSEUDO_ENV

CONFIG_LIST += IAP_INTERNAL_FLASH

CONFIG_LIST += DEVICE_TYPE_DC

CONFIG_LIST += STORAGE_OPS_25LC1024
#CONFIG_LIST += STORAGE_OPS_24LC128
#CONFIG_LIST += STORAGE_OPS_W25Q256

#CONFIG_LIST += NET_CLIENT_PROTOCOL_UDP
CONFIG_LIST += NET_CLIENT_PROTOCOL_TCP
#CONFIG_LIST += NET_CLIENT_PROTOCOL_TLS

#CONFIG_LIST += NET_CLIENT_REQUEST_DEFAULT
CONFIG_LIST += NET_CLIENT_REQUEST_SSE
#CONFIG_LIST += NET_CLIENT_REQUEST_OCPP_1_6

#CONFIG_LIST += CHARGER_CHANNEL_NATIVE
#CONFIG_LIST += CHARGER_CHANNEL_PROXY_REMOTE
CONFIG_LIST += CHARGER_CHANNEL_PROXY_LOCAL

CONFIG_LIST += DISABLE_DISPLAY
CONFIG_LIST += DISABLE_CARDREADER
CONFIG_LIST += DISABLE_POWER_MANAGER
CONFIG_LIST += DISABLE_VOICE
CONFIG_LIST += DISABLE_STORAGE

CONFIG_LIST += MULTI_CHARGE_PROXY

CONFIG_LIST += CHARGER_BMS_HANDLER_GB
#CONFIG_LIST += CHARGER_BMS_HANDLER_JP
#CONFIG_LIST += CHARGER_BMS_HANDLER_CCS
#CONFIG_LIST += CHARGER_BMS_HANDLER_GB_MULTI_CHARGE
#CONFIG_LIST += CHARGER_BMS_HANDLER_AC
#CONFIG_LIST += CHARGER_BMS_HANDLER_NOBMS

CONFIG_LIST += FUNCTION_BOARD_HANDLER_485
#CONFIG_LIST += FUNCTION_BOARD_HANDLER_V5
#CONFIG_LIST += FUNCTION_BOARD_HANDLER_CUSTOM
#CONFIG_LIST += ENABLE_CXX

$(foreach config_item,$(CONFIG_LIST),$(eval $(addprefix CONFIG_,$(config_item)) := $(config_item)))

CONFIG_CFLAGS := $(addprefix -D,$(CONFIG_LIST))
