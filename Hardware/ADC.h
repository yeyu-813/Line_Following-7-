#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

void Adc_Init(void);
uint16_t Adc_GetValue(void);   // 读取PA7通道的ADC原始值

#endif
