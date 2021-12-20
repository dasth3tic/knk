/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5 */

#ifndef PB_REMOTE_HARDWARE_PB_H_INCLUDED
#define PB_REMOTE_HARDWARE_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _HardwareMessage_Type { 
    HardwareMessage_Type_UNSET = 0, 
    HardwareMessage_Type_WRITE_GPIOS = 1, 
    HardwareMessage_Type_WATCH_GPIOS = 2, 
    HardwareMessage_Type_GPIOS_CHANGED = 3, 
    HardwareMessage_Type_READ_GPIOS = 4, 
    HardwareMessage_Type_READ_GPIOS_REPLY = 5 
} HardwareMessage_Type;

/* Struct definitions */
/* An example app to show off the plugin system. This message is used for
 REMOTE_HARDWARE_APP PortNums.

 Also provides easy remote access to any GPIO.

 In the future other remote hardware operations can be added based on user interest
 (i.e. serial output, spi/i2c input/output).

 FIXME - currently this feature is turned on by default which is dangerous
 because no security yet (beyond the channel mechanism).
 It should be off by default and then protected based on some TBD mechanism
 (a special channel once multichannel support is included?) */
typedef struct _HardwareMessage { 
    /* What type of HardwareMessage is this? */
    HardwareMessage_Type typ; 
    /* What gpios are we changing. Not used for all MessageTypes, see MessageType for details */
    uint64_t gpio_mask; 
    /* For gpios that were listed in gpio_mask as valid, what are the signal levels for those gpios.
 Not used for all MessageTypes, see MessageType for details */
    uint64_t gpio_value; 
} HardwareMessage;


/* Helper constants for enums */
#define _HardwareMessage_Type_MIN HardwareMessage_Type_UNSET
#define _HardwareMessage_Type_MAX HardwareMessage_Type_READ_GPIOS_REPLY
#define _HardwareMessage_Type_ARRAYSIZE ((HardwareMessage_Type)(HardwareMessage_Type_READ_GPIOS_REPLY+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define HardwareMessage_init_default             {_HardwareMessage_Type_MIN, 0, 0}
#define HardwareMessage_init_zero                {_HardwareMessage_Type_MIN, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define HardwareMessage_typ_tag                  1
#define HardwareMessage_gpio_mask_tag            2
#define HardwareMessage_gpio_value_tag           3

/* Struct field encoding specification for nanopb */
#define HardwareMessage_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    typ,               1) \
X(a, STATIC,   SINGULAR, UINT64,   gpio_mask,         2) \
X(a, STATIC,   SINGULAR, UINT64,   gpio_value,        3)
#define HardwareMessage_CALLBACK NULL
#define HardwareMessage_DEFAULT NULL

extern const pb_msgdesc_t HardwareMessage_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define HardwareMessage_fields &HardwareMessage_msg

/* Maximum encoded size of messages (where known) */
#define HardwareMessage_size                     24

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
