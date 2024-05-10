/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.9-dev */

#ifndef PB_MESHTASTIC_MESHTASTIC_MESSAGE_PB_H_INCLUDED
#define PB_MESHTASTIC_MESHTASTIC_MESSAGE_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
/* Representation of a received or sent message to be stored long-term to create a
 message history */
typedef struct _meshtastic_Message {
    /* The sending node's short name. */
    char sender_short_name[5];
    /* Whether the message is from this device. */
    bool from_self;
    /* TODO: Comment */
    char content[237];
    /* Values 1 through 7 indicate what secondary channel index this message was sent on.
 Value 0 indicates that this message was sent on the primary channel. Value 8
 indicates that this message was sent as a direct message. */
    uint32_t category;
    /* The time this message was received by the esp32 (secs since 1970).
 Note: this field is _never_ sent on the radio link itself (to save space) Times
 are typically not sent over the mesh, but they will be added to any Packet
 (chain of SubPacket) sent to the phone (so the phone can know exact time of reception) */
    uint32_t rx_time;
    /* TODO: Write comment */
    bool rx_ack;
} meshtastic_Message;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define meshtastic_Message_init_default          {"", 0, "", 0, 0, 0}
#define meshtastic_Message_init_zero             {"", 0, "", 0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define meshtastic_Message_sender_short_name_tag 1
#define meshtastic_Message_from_self_tag         2
#define meshtastic_Message_content_tag           3
#define meshtastic_Message_category_tag          4
#define meshtastic_Message_rx_time_tag           5
#define meshtastic_Message_rx_ack_tag            6

/* Struct field encoding specification for nanopb */
#define meshtastic_Message_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, STRING,   sender_short_name,   1) \
X(a, STATIC,   SINGULAR, BOOL,     from_self,         2) \
X(a, STATIC,   SINGULAR, STRING,   content,           3) \
X(a, STATIC,   SINGULAR, UINT32,   category,          4) \
X(a, STATIC,   SINGULAR, FIXED32,  rx_time,           5) \
X(a, STATIC,   SINGULAR, BOOL,     rx_ack,            6)
#define meshtastic_Message_CALLBACK NULL
#define meshtastic_Message_DEFAULT NULL

extern const pb_msgdesc_t meshtastic_Message_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define meshtastic_Message_fields &meshtastic_Message_msg

/* Maximum encoded size of messages (where known) */
#define MESHTASTIC_MESHTASTIC_MESSAGE_PB_H_MAX_SIZE meshtastic_Message_size
#define meshtastic_Message_size                  260

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
