/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.6 */

#ifndef PB_LOCALONLY_PB_H_INCLUDED
#define PB_LOCALONLY_PB_H_INCLUDED
#include <pb.h>
#include "config.pb.h"
#include "module_config.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _LocalConfig { 
    /* The part of the config that is specific to the Device */
    bool has_device;
    Config_DeviceConfig device;
    /* The part of the config that is specific to the GPS Position */
    bool has_position;
    Config_PositionConfig position;
    /* The part of the config that is specific to the Power settings */
    bool has_power;
    Config_PowerConfig power;
    /* The part of the config that is specific to the Wifi Settings */
    bool has_network;
    Config_NetworkConfig network;
    /* The part of the config that is specific to the Display */
    bool has_display;
    Config_DisplayConfig display;
    /* The part of the config that is specific to the Lora Radio */
    bool has_lora;
    Config_LoRaConfig lora;
    /* The part of the config that is specific to the Bluetooth settings */
    bool has_bluetooth;
    Config_BluetoothConfig bluetooth;
    /* A version integer used to invalidate old save files when we make
 incompatible changes This integer is set at build time and is private to
 NodeDB.cpp in the device code. */
    uint32_t version;
} LocalConfig;

typedef struct _LocalModuleConfig { 
    /* The part of the config that is specific to the MQTT module */
    bool has_mqtt;
    ModuleConfig_MQTTConfig mqtt;
    /* The part of the config that is specific to the Serial module */
    bool has_serial;
    ModuleConfig_SerialConfig serial;
    /* The part of the config that is specific to the ExternalNotification module */
    bool has_external_notification;
    ModuleConfig_ExternalNotificationConfig external_notification;
    /* The part of the config that is specific to the Store & Forward module */
    bool has_store_forward;
    ModuleConfig_StoreForwardConfig store_forward;
    /* The part of the config that is specific to the RangeTest module */
    bool has_range_test;
    ModuleConfig_RangeTestConfig range_test;
    /* The part of the config that is specific to the Telemetry module */
    bool has_telemetry;
    ModuleConfig_TelemetryConfig telemetry;
    /* The part of the config that is specific to the Canned Message module */
    bool has_canned_message;
    ModuleConfig_CannedMessageConfig canned_message;
    /* A version integer used to invalidate old save files when we make
 incompatible changes This integer is set at build time and is private to
 NodeDB.cpp in the device code. */
    uint32_t version;
} LocalModuleConfig;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define LocalConfig_init_default                 {false, Config_DeviceConfig_init_default, false, Config_PositionConfig_init_default, false, Config_PowerConfig_init_default, false, Config_NetworkConfig_init_default, false, Config_DisplayConfig_init_default, false, Config_LoRaConfig_init_default, false, Config_BluetoothConfig_init_default, 0}
#define LocalModuleConfig_init_default           {false, ModuleConfig_MQTTConfig_init_default, false, ModuleConfig_SerialConfig_init_default, false, ModuleConfig_ExternalNotificationConfig_init_default, false, ModuleConfig_StoreForwardConfig_init_default, false, ModuleConfig_RangeTestConfig_init_default, false, ModuleConfig_TelemetryConfig_init_default, false, ModuleConfig_CannedMessageConfig_init_default, 0}
#define LocalConfig_init_zero                    {false, Config_DeviceConfig_init_zero, false, Config_PositionConfig_init_zero, false, Config_PowerConfig_init_zero, false, Config_NetworkConfig_init_zero, false, Config_DisplayConfig_init_zero, false, Config_LoRaConfig_init_zero, false, Config_BluetoothConfig_init_zero, 0}
#define LocalModuleConfig_init_zero              {false, ModuleConfig_MQTTConfig_init_zero, false, ModuleConfig_SerialConfig_init_zero, false, ModuleConfig_ExternalNotificationConfig_init_zero, false, ModuleConfig_StoreForwardConfig_init_zero, false, ModuleConfig_RangeTestConfig_init_zero, false, ModuleConfig_TelemetryConfig_init_zero, false, ModuleConfig_CannedMessageConfig_init_zero, 0}

/* Field tags (for use in manual encoding/decoding) */
#define LocalConfig_device_tag                   1
#define LocalConfig_position_tag                 2
#define LocalConfig_power_tag                    3
#define LocalConfig_network_tag                  4
#define LocalConfig_display_tag                  5
#define LocalConfig_lora_tag                     6
#define LocalConfig_bluetooth_tag                7
#define LocalConfig_version_tag                  8
#define LocalModuleConfig_mqtt_tag               1
#define LocalModuleConfig_serial_tag             2
#define LocalModuleConfig_external_notification_tag 3
#define LocalModuleConfig_store_forward_tag      4
#define LocalModuleConfig_range_test_tag         5
#define LocalModuleConfig_telemetry_tag          6
#define LocalModuleConfig_canned_message_tag     7
#define LocalModuleConfig_version_tag            8

/* Struct field encoding specification for nanopb */
#define LocalConfig_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  device,            1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  position,          2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  power,             3) \
X(a, STATIC,   OPTIONAL, MESSAGE,  network,           4) \
X(a, STATIC,   OPTIONAL, MESSAGE,  display,           5) \
X(a, STATIC,   OPTIONAL, MESSAGE,  lora,              6) \
X(a, STATIC,   OPTIONAL, MESSAGE,  bluetooth,         7) \
X(a, STATIC,   SINGULAR, UINT32,   version,           8)
#define LocalConfig_CALLBACK NULL
#define LocalConfig_DEFAULT NULL
#define LocalConfig_device_MSGTYPE Config_DeviceConfig
#define LocalConfig_position_MSGTYPE Config_PositionConfig
#define LocalConfig_power_MSGTYPE Config_PowerConfig
#define LocalConfig_network_MSGTYPE Config_NetworkConfig
#define LocalConfig_display_MSGTYPE Config_DisplayConfig
#define LocalConfig_lora_MSGTYPE Config_LoRaConfig
#define LocalConfig_bluetooth_MSGTYPE Config_BluetoothConfig

#define LocalModuleConfig_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  mqtt,              1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  serial,            2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  external_notification,   3) \
X(a, STATIC,   OPTIONAL, MESSAGE,  store_forward,     4) \
X(a, STATIC,   OPTIONAL, MESSAGE,  range_test,        5) \
X(a, STATIC,   OPTIONAL, MESSAGE,  telemetry,         6) \
X(a, STATIC,   OPTIONAL, MESSAGE,  canned_message,    7) \
X(a, STATIC,   SINGULAR, UINT32,   version,           8)
#define LocalModuleConfig_CALLBACK NULL
#define LocalModuleConfig_DEFAULT NULL
#define LocalModuleConfig_mqtt_MSGTYPE ModuleConfig_MQTTConfig
#define LocalModuleConfig_serial_MSGTYPE ModuleConfig_SerialConfig
#define LocalModuleConfig_external_notification_MSGTYPE ModuleConfig_ExternalNotificationConfig
#define LocalModuleConfig_store_forward_MSGTYPE ModuleConfig_StoreForwardConfig
#define LocalModuleConfig_range_test_MSGTYPE ModuleConfig_RangeTestConfig
#define LocalModuleConfig_telemetry_MSGTYPE ModuleConfig_TelemetryConfig
#define LocalModuleConfig_canned_message_MSGTYPE ModuleConfig_CannedMessageConfig

extern const pb_msgdesc_t LocalConfig_msg;
extern const pb_msgdesc_t LocalModuleConfig_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define LocalConfig_fields &LocalConfig_msg
#define LocalModuleConfig_fields &LocalModuleConfig_msg

/* Maximum encoded size of messages (where known) */
#define LocalConfig_size                         334
#define LocalModuleConfig_size                   270

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
