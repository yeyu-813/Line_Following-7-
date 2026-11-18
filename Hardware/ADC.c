#include "stm32f10x.h"
#include "ADC.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_adc.h>

void Adc_Init(void)
{
    // 1. ��ʱ�ӣ�GPIOA + ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
    
    // 2. ����PA7Ϊģ������ģʽ�����룩
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  // ģ�����룬ר��ADCģʽ
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 3. ADCʱ�ӷ�Ƶ��72MHz / 6 = 12MHz��ADC���14MHz�������Ƶ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    
    // 4. ����ADC��������
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;      // ��������ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;           // ��ͨ��������ɨ��
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;     // ����ת��������һ��תһ��
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  // �����Ҷ��룬�����ȡ
    ADC_InitStructure.ADC_NbrOfChannel = 1;                  // 1��ͨ��
    ADC_Init(ADC1, &ADC_InitStructure);
    
    // 5. ʹ��ADC
    ADC_Cmd(ADC1, ENABLE);
    
    // 6. ADCУ׼�������������������׼��
    ADC_ResetCalibration(ADC1);                    // ��λУ׼�Ĵ���
    while(ADC_GetResetCalibrationStatus(ADC1));    // �ȴ���λ���
    ADC_StartCalibration(ADC1);                    // ��ʼУ׼
    while(ADC_GetCalibrationStatus(ADC1));         // �ȴ�У׼���
}

// ��ȡPA7(ͨ��7)��ADCԭʼֵ����Χ 0~4095
uint16_t Adc_GetValue(void)
{
    // 1. ���ù���ͨ����ͨ��7����1��ת��������ʱ��239.5���ڣ�Խ��Խ�ȶ���
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_239Cycles5);
    
    // 2. ��������һ��ת��
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    
    // 3. �ȴ�ת����ɣ�EOC��־��1��
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    
    // 4. ��ȡת�������ͬʱ�Զ����EOC��־
    return ADC_GetConversionValue(ADC1);
}
