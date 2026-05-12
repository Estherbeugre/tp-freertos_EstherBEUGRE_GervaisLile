/*
 * Neopixels.h
 *
 *  Created on: 13 mars 2026
 *      Author: ZachariaFOFANA
 */

#ifndef FRONT_CORE_INC_NEOPIXELS_H_
#define FRONT_CORE_INC_NEOPIXELS_H_

#include "spi.h"
#include <stdint.h>

//Color hsvColor(float h, float s, float l);

//Color hsvColor(float h, float s, float v) {
//    Color result;
//
//    fast_hsv2rgb_32bit(h * HSV_HUE_MAX, s * HSV_SAT_MAX, v * HSV_VAL_MAX, &result.R, &result.G, &result.B);
//
//    return result;
//}
#define LED_COUNT 18

/* SPI should be set to 12MBit/s, data 8 bits */
#define SPI_NEO0 ((uint8_t) 0b11000000)
#define SPI_NEO1 ((uint8_t) 0b11111100)

typedef struct color {
	uint8_t G;
	uint8_t R;
	uint8_t B;
} Color;

void setLed(int i, Color color);
void show(SPI_HandleTypeDef *hspi);

#define BITSPERLED (3 * 8)

// 32: 32 Bytes at 5MHz = 51.2µs reset time
extern uint8_t spiBuffer[LED_COUNT * BITSPERLED + 32];
extern Color ledBuffer[LED_COUNT];


void setLed(int i, Color color);

void show(SPI_HandleTypeDef *hspi);


void hsv_to_rgb_u8(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b);


#endif /* FRONT_CORE_INC_NEOPIXELS_H_ */
