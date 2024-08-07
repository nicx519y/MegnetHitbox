#ifndef __WS2812B_H__
#define __WS2812B_H__

#include "stm32h7xx_hal.h"

/**
  * @brief  WS2812B Status structures definition
  */
typedef enum
{
  WS2812B_STOP         = 0x00,
  WS2812B_RUNNING      = 0x01,
  WS2812B_ERROR        = 0x02
} WS2812B_StatusTypeDef;

void WS2812B_Init(void);

void WS2812B_SetAllLEDBrightness(const uint8_t brightness);

void WS2812B_SetAllLEDColor(const uint8_t r, const uint8_t g, const uint8_t b);

void WS2812B_SetLEDBrighting(const uint8_t brightness, const uint16_t index);

void WS2812B_SetLEDColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint16_t index);

WS2812B_StatusTypeDef WS2812B_Start();

WS2812B_StatusTypeDef WS2812B_Stop();

WS2812B_StatusTypeDef WS2812B_GetStatus();

#endif /* __WS2812B_H__ */
