#ifndef SENTRYGLOBALS_H

#define SENTRYGLOBALS_H

#define LOG_ENABLED true

#define VRX_PIN  A1 // Arduino pin connected to VRX pin
#define VRY_PIN  A2 // Arduino pin connected to VRY pin
#define SW_PIN   5  // Arduino pin connected to SW  pin

#define LORA_RFM9X_CS 4
#define LORA_RFM9X_INT 7
#define LORA_RFM9X_RST 2
#define LORA_RFM9X_FREQ 915.0

#define LORA_RFM9X_MAX_MESSAGE_LEN 64

#define LORA_ADDR_SELF 0
#define LORA_ADDR_SPOTTER 1
#define LORA_ADDR_ACTOR 2
#define LORA_ADDR_BROADCAST 255

#endif