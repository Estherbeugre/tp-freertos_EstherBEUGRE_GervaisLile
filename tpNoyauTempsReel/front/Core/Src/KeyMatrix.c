/*
 * KeyMatrix.c
 *
 *  Created on: 13 mars 2026
 *      Author: ZachariaFOFANA
 */

#include "KeyMatrix.h"
#include "dma.h"
#include "lptim.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

static key_info_t key_matrix[ROWS][COLS];

int led_lut[KEYS] =
{
		14, 15, 16, 17,
		0, -1, -1, 1,
		2, 3, 4, 5,
		6, 7, 8, 9,
		10, 11, 12, 13,
		14, 15, 16, 17
};

void on_key_pressed(int row, int col)
{
	int key = row * COLS + col;
	int led = led_lut[key];

	if (led != -1)
	{
//		/* TODO Delete as soon as UART Works */
//		uint16_t enc[4];
//		enc[0] = __HAL_TIM_GET_COUNTER(&htim2);
//		enc[1] = __HAL_TIM_GET_COUNTER(&htim3);
//		enc[2] = __HAL_TIM_GET_COUNTER(&htim1);
//		enc[3] = HAL_LPTIM_ReadCounter(&hlptim1);
//
//		uint8_t r, g, b;
//		hsv_to_rgb_u8(enc[key % 4] % MAX_HUE, DEFAULT_SAT, DEFAULT_VAL, &r, &g, &b);
//		ledBuffer[led] = (Color) { .R = r, .G = g, .B = b };
//		show(&hspi2);
//		/* END DELETE */

		uint8_t data = UART_KEY_PRESSED | key;
		HAL_UART_Transmit(&huart2, &data, 1, HAL_MAX_DELAY);
	}
}



void on_key_released(int row, int col)
{
	int key = row * COLS + col;
	int led = led_lut[key];

	if (led != -1)
	{
//		/* TODO Delete as soon as UART Works */
//		ledBuffer[led] = (Color) { .R = 0, .G = 0, .B = 0 };
//		show(&hspi2);
//		/* END DELETE */

		uint8_t data = UART_KEY_RELEASED | key;
		HAL_UART_Transmit(&huart2, &data, 1, HAL_MAX_DELAY);
	}
}

uint8_t read_row(int r)
{
	switch(r)
	{
	case 0:
		return HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin);
	case 1:
		return HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin);
	case 2:
		return HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin);
	case 3:
		return HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin);
	case 4:
		return HAL_GPIO_ReadPin(ROW5_GPIO_Port, ROW5_Pin);
	case 5:
		return HAL_GPIO_ReadPin(ROW6_GPIO_Port, ROW6_Pin);
	default:
		return 0;
	}
}

void matrix_process(void)
{
	for (int c = 0; c < COLS; c++) {

		activate_col(c);

		for (int r = 0; r < ROWS; r++) {
			uint8_t raw = read_row(r);

			key_info_t *k = &key_matrix[r][c];

			switch (k->state) {
			case STABLE_RELEASED:
				if (raw == 1) {
					k->state = BOUNCE_PRESSING;
					k->stable_count = 0;
				}
				break;

			case BOUNCE_PRESSING:
				if (raw == 1) {
					if (++k->stable_count >= DEBOUNCE_COUNT) {
						k->state = STABLE_PRESSED;
						// --> Événement appui validé
						on_key_pressed(r, c);
					}
				} else {
					k->state = STABLE_RELEASED; // annule
				}
				break;

			case STABLE_PRESSED:
				if (raw == 0) {
					k->state = BOUNCE_RELEASING;
					k->stable_count = 0;
				}
				break;

			case BOUNCE_RELEASING:
				if (raw == 0) {
					if (++k->stable_count >= DEBOUNCE_COUNT) {
						k->state = STABLE_RELEASED;
						// --> Événement relâché validé
						on_key_released(r, c);
					}
				} else {
					k->state = STABLE_PRESSED; // annule
				}
				break;
			}
		}

		deactivate_all_cols();
	}
}

void activate_col(int c)
{
	switch(c)
	{
	case 0:
		HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_SET);
		break;
	default:
		HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(COL3_GPIO_Port, COL4_Pin, GPIO_PIN_RESET);
		break;
	}
}

void deactivate_all_cols(void)
{
	HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_RESET);
}
