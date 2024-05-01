#ifndef _PINMAP_H_
#define _PINMAP_H_




#define BOARD 1

#if (BOARD == 1)
// #pragma message("Using Metro")
#define BOARD_METRO
// #define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64
// #define PICO_BOOT_STAGE2_CHOOSE_GENERIC_03H 1
// #define PICO_FLASH_SPI_CLKDIV 2
// #define PICO_FLASH_SIZE_BYTES (16 * 1024 * 1024)
// #define PICO_RP2040_B0_SUPPORTED 0
// #define PICO_RP2040_B1_SUPPORTED 0
// #define PICO_RP2040_B2_SUPPORTED 1

#define LED_PIN 13
#define PIN_KEY_ENTER 12
#define SDA_PIN 16 //SDA0
#define SCL_PIN 17 //SCL0
#define I2C_ID 0
#define SPI_ID_DISPLAY 1
#define SPI_DISP_SCK_PIN 26
#define SPI_DISP_MOSI_PIN 27
#define SPI_DISP_MISO_PIN 28
#define SPI_DISP0_CS_PIN 29
#define SPI_DISP1_CS_PIN 1
#define DISP0_RST_PIN 24
#define DISP1_RST_PIN 0
#define DISP0_DC_PIN 2
#define DISP1_DC_PIN 4
#define SPI_DISP0_CARD_CS_PIN 25
#define SPI_DISP1_CARD_CS_PIN 5
#define DISP0_LIGHT_PIN 3
#define DISP1_LIGHT_PIN 6

#elif (BOARD == 2)
#error "KB2040 not fully supported yet"
// #pragma message("Using KB2040")
#define BOARD_KB
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1
#define PICO_FLASH_SPI_CLKDIV 2
#define PICO_FLASH_SIZE_BYTES (8 * 1024 * 1024)
#define PICO_RP2040_B0_SUPPORTED 0
#define PICO_RP2040_B1_SUPPORTED 0

#define LED_PIN 0
#define SDA_PIN 28
#define SCL_PIN 29
#define PIN_KEY_ENTER 12
#define I2C_ID 0

#else
#error "Need to specify BOARD"
#endif






#endif
