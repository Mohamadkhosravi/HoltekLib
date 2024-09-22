#ifndef RCC_H__
#define RCC_H__
#include "BA45F5240.h"
#// Clock source options
#define CLOCK_SOURCE_HIRC   0x00  // High-speed internal RC
#define CLOCK_SOURCE_LIRC   0x01  // Low-speed internal RC (32 kHz)

// Clock frequency definitions (HIRC)
#define INTERNAL_16_MHZ  0b00001101  // 16 MHz internal clock
#define INTERNAL_8_MHZ   0b00001001  // 8 MHz internal clock
#define INTERNAL_4_MHZ   0b00000101  // 4 MHz internal clock
#define INTERNAL_2_MHZ   0b00000001  // 2 MHz internal clock

// Watchdog timeout periods (WDTC)
#define WDT_TIMEOUT_4_MS     0b00001000  // 4 ms
#define WDT_TIMEOUT_16_MS    0b00001001  // 16 ms
#define WDT_TIMEOUT_64_MS    0b00001010  // 64 ms
#define WDT_TIMEOUT_256_MS   0b00001011  // 256 ms
#define WDT_TIMEOUT_1_SEC    0b00001100  // 1.024 sec
#define WDT_TIMEOUT_4_SEC    0b00001101  // 4.096 sec
#define WDT_TIMEOUT_16_SEC   0b00001110  // 16.384 sec
#define WDT_TIMEOUT_65_SEC   0b00001111  // 65.536 sec
#define WDT_DISABLED         0b00000000  // WDT disabled

// Power modes (FHSIR)
#define FAST_MODE     0b00000000  // FAST Mode with high-speed oscillator
#define SLOW_MODE     0b00000010  // SLOW Mode with low-speed oscillator
#define SLEEP_MODE    0b00000001  // SLEEP Mode
#define IDLE0_MODE    0b00000100  // IDLE0 Mode
#define IDLE1_MODE    0b01000100  // IDLE1 Mode (high and low-speed oscillators on)



// Wakeup Key Configuration
#define ENABLE_WAKEUP_KEY     1
#define DISABLE_WAKEUP_KEY    0

// Default configurations (can be modified for specific project needs)
#define CONFIG_CLOCK_INTERNAL    INTERNAL_8_MHZ  // Default clock setting: 8 MHz
#define CONFIG_WDT               WDT_TIMEOUT_4_SEC  // Default WDT setting: 4.096 sec
#define CONFIG_POWER_MODE        FAST_MODE  // Default power mode: FAST
#define CONFIG_ENABLE_WAKEUP_KEY ENABLE_WAKEUP_KEY  // Enable wake-up key

// Function Prototypes
void RCC_Init(void);  

#endif  
