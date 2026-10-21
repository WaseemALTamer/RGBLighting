/*
    THIS CODE IS GENERATED. DO NOT CHANGE.
    IF YOU WANT TO CHANGE IT, MODIFY THE PYTHON PROTOCOL
    AND REGENERATE THIS CODE.
*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <stddef.h>

typedef enum ContentType {
    CONTENT_TYPE_NONE = 0,
    CONTENT_TYPE_BYTES_STREAM = 1,
    CONTENT_TYPE_MESSAGE = 2,
    CONTENT_TYPE_COMMAND = 3,
    CONTENT_TYPE_INFORMATION = 4,
    CONTENT_TYPE_DISCOVERY = 5,
    CONTENT_TYPE_WIFI_CONNECT = 6,
    CONTENT_TYPE_SET_DEVICE_STATUS = 7,
    CONTENT_TYPE_SET_DEVICE_NAME = 8,
    CONTENT_TYPE_SET_DATE_TIME = 9,
    CONTENT_TYPE_SET_SEQUENCE = 10,
    CONTENT_TYPE_SET_SETTING = 11,
    CONTENT_TYPE_SET_BRIGHTNESS = 12,
    CONTENT_TYPE_RGB_STREAM = 13,
} ContentType;


typedef enum DeviceStatus {
    DEVICE_STATUS_NONE = 0,
    DEVICE_STATUS_BOOTING = 1,
    DEVICE_STATUS_NORMAL = 2,
    DEVICE_STATUS_NETWORK_ERROR = 3,
    DEVICE_STATUS_UNKNOWN_ERROR = 4,
} DeviceStatus;


typedef enum SequenceType {
    SEQUENCE_TYPE_NONE = 0,
    SEQUENCE_TYPE_RAINBOW = 1,
    SEQUENCE_TYPE_BREATHING = 2,
    SEQUENCE_TYPE_WAVE = 3,
    SEQUENCE_TYPE_COLOR_CYCLE = 4,
    SEQUENCE_TYPE_SLEEP = 5,
    SEQUENCE_TYPE_WAKEUP = 6,
    SEQUENCE_TYPE_COLOR_WIPE = 7,
    SEQUENCE_TYPE_CHASE = 8,
    SEQUENCE_TYPE_PULSE = 9,
    SEQUENCE_TYPE_FIRE = 10,
    SEQUENCE_TYPE_TWINKLE = 11,
    SEQUENCE_TYPE_SCANNER = 12,
    SEQUENCE_TYPE_PROGRESS = 13,
    SEQUENCE_TYPE_ALERT = 14,
    SEQUENCE_TYPE_DANGOUR = 15,
    SEQUENCE_TYPE_NOTIFICATION = 16,
} SequenceType;


typedef struct{
    uint32_t length;
    const uint8_t *content;
} BytesStream;

typedef struct{
    uint64_t sequence_number;
    ContentType content_type;
    const uint8_t *content;
} Command;

typedef struct{
} Discovery;

typedef struct{
    uint32_t firmware_version;
    uint8_t device_type;
    uint16_t led_count;
    uint8_t status;
} Information;

typedef struct{
    uint8_t version;
    char device_name[64];
    uint8_t mac_address[6];
    double time_stamp;
    uint8_t is_encrypted;
    ContentType content_type;
    const uint8_t *content;
} Message;

typedef struct{
    uint16_t starting_led;
    float transition_duration;
    const uint8_t *content;
} RGBStream;

typedef struct{
    uint8_t value;
    float transition_duration;
} SetBrightness;

typedef struct{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint32_t year;
} SetDateTime;

typedef struct{
    char device_name[64];
} SetDeviceName;

typedef struct{
    DeviceStatus status;
} SetDeviceStatus;

typedef struct{
    SequenceType sequence;
    float speed;
    float width;
    float height;
    uint8_t direction;
    uint8_t color_one[3];
    uint8_t color_two[3];
    uint8_t color_three[3];
    uint8_t color_four[3];
    uint8_t color_five[3];
} SetSequence;

typedef struct{
} SetSetting;

typedef struct{
    char ssid[32];
    char password[64];
} WifiConnect;


#ifdef __cplusplus
extern "C" {
#endif

uint8_t *bytes_stream_encode(
    const BytesStream *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *bytes_stream_decode(
    BytesStream *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *command_encode(
    const Command *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *command_decode(
    Command *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *discovery_encode(
    const Discovery *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *discovery_decode(
    Discovery *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *information_encode(
    const Information *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *information_decode(
    Information *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *message_encode(
    const Message *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *message_decode(
    Message *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *r_g_b_stream_encode(
    const RGBStream *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *r_g_b_stream_decode(
    RGBStream *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *set_brightness_encode(
    const SetBrightness *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *set_brightness_decode(
    SetBrightness *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *set_date_time_encode(
    const SetDateTime *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *set_date_time_decode(
    SetDateTime *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *set_device_name_encode(
    const SetDeviceName *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *set_device_name_decode(
    SetDeviceName *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *set_device_status_encode(
    const SetDeviceStatus *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *set_device_status_decode(
    SetDeviceStatus *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *set_sequence_encode(
    const SetSequence *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *set_sequence_decode(
    SetSequence *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *set_setting_encode(
    const SetSetting *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *set_setting_decode(
    SetSetting *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);

uint8_t *wifi_connect_encode(
    const WifiConnect *msg,
    uint8_t *buffer,
    size_t *buffer_size
);

const uint8_t *wifi_connect_decode(
    WifiConnect *msg,
    const uint8_t *buffer,
    size_t *buffer_size
);


#ifdef __cplusplus
}
#endif

#endif /* PROTOCOL_H */
