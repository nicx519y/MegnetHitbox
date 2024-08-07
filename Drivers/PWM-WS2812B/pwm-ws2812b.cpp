#include "pwm-ws2812b.h"
#include "tim.h"
#include "utils.h"
#include "config.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* WS2812B data protocol
|-------------------------------------------|
|T0H | 0.4us      | +-150ns
|T1H | 0.8us      | +-150ns
|T0L | 0.85us     | +-150ns
|T1L | 0.45us     | +-150ns
|RES | above 50us |
|-------------------------------------------
*/

#define DMA_BUFFER_LEN (((ADC_KEY_COUNT % 2 == 0) ? (ADC_KEY_COUNT + 4) : (ADC_KEY_COUNT + 5)) * 24) //RES >= 4 * 24 * 300 * 1/240 = 120us

#define HIGH_CCR_CODE 183; // 1/240 * 183 = 0.76us; 1/240 * (300 - 183) = 0.49us;

#define LOW_CCR_CODE 83; // 1/240 * 83 = 0.35us; 1/240 * (300 - 83) = 0.90us;

WS2812B_StatusTypeDef WS2812B_Status = WS2812B_STOP;

uint8_t LED_COLORS[ADC_KEY_COUNT * 3];

uint8_t LED_BRIGHTNESS[ADC_KEY_COUNT];

uint32_t DMA_LED_Buffer[DMA_BUFFER_LEN]; 


void LEDDataToDMABuffer(const uint16_t start, const uint16_t length)
{
	if(start + length > ADC_KEY_COUNT) {
		return;
	}

	uint16_t i, j;
	uint16_t len = (start + length) * 3;

	for(j = start * 3; j < len; j += 3)
	{
		float brightness = (float)LED_BRIGHTNESS[j / 3] / 255;
		uint32_t color = RGBToHex((uint8_t)round(LED_COLORS[j] * brightness), (uint8_t)round(LED_COLORS[j + 1] * brightness), (uint8_t)round(LED_COLORS[j + 2] * brightness));
		for(i = 0; i < 24; i ++) {
			if(0x800000 & (color << i)) {
				DMA_LED_Buffer[j * 8 + i] = HIGH_CCR_CODE;
			} else {
				DMA_LED_Buffer[j * 8 + i] = LOW_CCR_CODE;
			}
		}
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	// printf("PulseFinished...\r\n");

	uint16_t start = DMA_BUFFER_LEN / 2 / 24;

	uint16_t length = ADC_KEY_COUNT - start;

	LEDDataToDMABuffer(start, length);

	// HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_1);
}

void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim)
{
	// printf("PulseFinishedHalfCplt...\r\n");

	uint16_t length = DMA_BUFFER_LEN / 2 / 24;

	LEDDataToDMABuffer(0, length);

}

void WS2812B_Init(void)
{
	memset(DMA_LED_Buffer, 0, DMA_BUFFER_LEN);
	memset(LED_BRIGHTNESS, LED_DEFAULT_BRIGHTNESS, ADC_KEY_COUNT);

	LEDDataToDMABuffer(0, ADC_KEY_COUNT);

	if(HAL_TIM_Base_GetState(&htim4) != HAL_TIM_STATE_READY) {
		MX_TIM4_Init();
	}
}

WS2812B_StatusTypeDef WS2812B_Start()
{
	if(WS2812B_Status != WS2812B_STOP) {
		return WS2812B_Status;
	}

	HAL_StatusTypeDef state = HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, (uint32_t *)&DMA_LED_Buffer, DMA_BUFFER_LEN);

	if(state == HAL_OK) {
		WS2812B_Status = WS2812B_RUNNING;
	} else {
		WS2812B_Status = WS2812B_ERROR;
	}
	return WS2812B_Status;
}

WS2812B_StatusTypeDef WS2812B_Stop()
{
    if(WS2812B_Status != WS2812B_RUNNING) {
        return WS2812B_Status;
    }

    HAL_StatusTypeDef state = HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_1);

    if(state == HAL_OK) {
		WS2812B_Status = WS2812B_STOP;
    } else {
		WS2812B_Status = WS2812B_ERROR;
    }
    return WS2812B_Status;
}

void WS2812B_SetAllLEDBrightness(const uint8_t brightness)
{
    memset(LED_BRIGHTNESS, brightness, ADC_KEY_COUNT);
}

void WS2812B_SetAllLEDColor(const uint8_t r, const uint8_t g, const uint8_t b)
{
    int length = ADC_KEY_COUNT * 3;
    for(int i = 0; i < length; i += 3) {
        LED_COLORS[i] = r;
        LED_COLORS[i + 1] = g;
        LED_COLORS[i + 2] = b;
    }
}

void WS2812B_SetLEDbrightness(const uint8_t brightness, const int16_t index)
{
	if(index >= 0 && index < ADC_KEY_COUNT) {
		LED_BRIGHTNESS[index] = brightness;
	}
}

void WS2812B_SetLEDColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint16_t index)
{
	if(index >= 0 && index < ADC_KEY_COUNT) {
		uint16_t idx = index * 3;
		LED_COLORS[idx] = r;
		LED_COLORS[idx + 1] = g;
		LED_COLORS[idx + 2] = b;
	}
}

WS2812B_StatusTypeDef WS2812B_GetStatus()
{
	return WS2812B_Status;
}



