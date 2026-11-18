#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	PWM_Init();
}

void Motor_SetRightSpeed(int8_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		PWM_SetCompare1(Speed);
	}
	else if(Speed == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		PWM_SetCompare1(-Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		PWM_SetCompare1(-Speed);
	}
}

void Motor_SetLeftSpeed(int8_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		PWM_SetCompare2(Speed);
	}
	else if(Speed == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		PWM_SetCompare2(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		PWM_SetCompare2(-Speed);
	}
}
