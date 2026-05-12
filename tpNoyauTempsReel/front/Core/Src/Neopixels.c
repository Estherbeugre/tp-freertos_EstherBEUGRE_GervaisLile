#include "Neopixels.h"
#include "main.h"
#include "dma.h"
#include "lptim.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

uint8_t spiBuffer[LED_COUNT * BITSPERLED + 32];
Color ledBuffer[LED_COUNT];

static void buildSPIbuffer(void) {
    for (int i = 0; i < LED_COUNT; i++) {

        uint8_t m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b] = (ledBuffer[i].G & m) ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }

        m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b + 8] = (ledBuffer[i].R & m) ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }

        m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b + 16] = (ledBuffer[i].B & m) ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }
    }
}

void setLed(int i, Color color) {
    ledBuffer[i] = color;
}

void show(SPI_HandleTypeDef *hspi) {
    buildSPIbuffer();
    HAL_SPI_Transmit_DMA(hspi, spiBuffer, LED_COUNT * BITSPERLED + 32);
}

static inline uint8_t mul8(uint8_t a, uint8_t b)
{
    return (uint8_t)(((uint16_t)a * (uint16_t)b) >> 8);
}

void hsv_to_rgb_u8(uint16_t h, uint8_t s, uint8_t v,
                   uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (h >= 360) {
        h = h % 360;
    }

    uint8_t region = h / 60;
    uint8_t remainder = (h % 60) * 255 / 60;

    uint8_t p = mul8(v, 255 - s);
    uint8_t q = mul8(v, 255 - mul8(s, remainder));
    uint8_t t = mul8(v, 255 - mul8(s, 255 - remainder));

    switch (region) {
    case 0:
        *r = v; *g = t; *b = p;
        break;
    case 1:
        *r = q; *g = v; *b = p;
        break;
    case 2:
        *r = p; *g = v; *b = t;
        break;
    case 3:
        *r = p; *g = q; *b = v;
        break;
    case 4:
        *r = t; *g = p; *b = v;
        break;
    default:
        *r = v; *g = p; *b = q;
        break;
    }
}
