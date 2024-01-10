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

//#define LORA_RFM9X_MAX_MESSAGE_LEN 64
#define LORA_RFM9X_MAX_MESSAGE_LEN 128
#define LORA_MAX_CHUNK_SIZE 100 // leave 28 bytes for metadata
#define LORA_MAX_CHUNK_IN_BUFFER_SIZE 1024 // max size allowed for any chunk bunch
#define LORA_MAX_CHUNK_TIME_MILLIS 8000 // max time to wait for all chunks to arrive

#define LORA_CHUNK_START_KEY "CHUNKSTART"
#define LORA_CHUNK_END_KEY "CHUNKEND:"
#define LORA_ACK_TIMEOUT 1000

#define LORA_ADDR_SELF 0
#define LORA_ADDR_SPOTTER 1
#define LORA_ADDR_ACTOR 2
#define LORA_ADDR_BROADCAST 255

#define THERMAL_INTERPOLATE_BUFFER_SIZE 3072 // 48 * 32

#define THERMAL_ENCODE_BUFFER_SIZE 0 // no encoding/decoding needed yet

#define THERMAL_WIDTH 32
#define THERMAL_HEIGHT 24

// 1331 pins: sckl (SCL); mosi (SDA); cs(CS); rst (RES); dc (DC)
#define Display_1331_SCLK 12
#define Display_1331_MOSI 11
#define Display_1331_CS   6
#define Display_1331_RST  1
#define Display_1331_DC   3

#define DISPLAY_STATUS_X 28
#define DISPLAY_STATUS_Y 54


// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

#endif