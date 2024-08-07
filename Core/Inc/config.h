#ifndef __CONFIG_H__
#define __CONFIG_H__

// ADC按钮数量
#define ADC_KEY_COUNT 16

#define DEFAULT_KEY_LABEL {}

// key LABEL枚举值顺序
#define KEY_LABEL_ARR { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 }

// LED 灯的索引顺序
#define LED_INDEX_ARR { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }

// LED 默认颜色
#define LED_DEFAULT_COLOR { 128, 128, 128 }

// LED 默认亮度
#define LED_DEFAULT_BRIGHTNESS 128

#define ADC1_DMA_BUFFER_LEN 8

#define ADC2_DMA_BUFFER_LEN 8

// 按键总行程
#define KEY_TRAVEL 30

// 每毫米产生的ADC值最小差异，小于这个差异不是最佳状态
#define KEY_MIN_ADC_PER_TRAVEL 600     

#endif /* __CONFIG_H__ */