/*
 * KeyMatrix.h
 *
 *  Created on: 13 mars 2026
 *      Author: ZachariaFOFANA
 */

#ifndef FRONT_CORE_INC_KEYMATRIX_H_
#define FRONT_CORE_INC_KEYMATRIX_H_

#include "main.h"

void on_key_pressed(int row, int col);
void on_key_released(int row, int col);
uint8_t read_row(int r);
void matrix_process(void);
void activate_col(int c);
void deactivate_all_cols(void);

#define ROWS 6
#define COLS 4
#define KEYS (ROWS * COLS)
#define DEBOUNCE_COUNT 5

#define MAX_HUE 360
#define DEFAULT_SAT 200
#define DEFAULT_VAL 200

#define UART_KEY_PRESSED 0x80
#define UART_KEY_RELEASED 0x00
#define UART_KEY_MASK 0x7F

typedef enum {
	STABLE_RELEASED = 0,
	BOUNCE_PRESSING,
	STABLE_PRESSED,
	BOUNCE_RELEASING
} key_state_t;

typedef struct {
	key_state_t state;
	uint8_t stable_count;
} key_info_t;

typedef struct {
	uint16_t hue;
	uint8_t used;
	uint8_t active;
	uint8_t pressed;
} keys_t;

extern int led_lut[KEYS];


#endif /* FRONT_CORE_INC_KEYMATRIX_H_ */
