/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f10x6.h"
#include "gpio.h"

void clockinit(){
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
}

void GPIO_init(){
	GPIO_PinConfig_t pincnfg;
	//A1 high impedence --> floating input
	pincnfg.GPIO_PinNumber = GPIO_PIN_1;
	pincnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA,&pincnfg);
	//B1 output push pull mode 10Mhz speed
	pincnfg.GPIO_PinNumber = GPIO_PIN_1;
	pincnfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pincnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB,&pincnfg);
	//A13 high impedence --> floating input
	pincnfg.GPIO_PinNumber = GPIO_PIN_13;
	pincnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA,&pincnfg);
	//B13 output push pull mode 10Mhz speed
	pincnfg.GPIO_PinNumber = GPIO_PIN_13;
	pincnfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pincnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB,&pincnfg);
}
void wait_ms(uint32_t time){
	uint32_t i,j;
	for(i=0; i<time ;i++)
		for(j=0 ; j<255 ; j++);
}
int main(void)
{
	clockinit();
	GPIO_init();
	/* Loop forever */
	for(;;){
		//A1 PUR switch always vcc when pressed 0B
		if(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0){
			MCAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
			while(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0);//single pressing
		}
		if(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_13)==1){ // pull down resistance
			MCAL_GPIO_TogglePin(GPIOB,GPIO_PIN_13);
		}
		wait_ms(1);
	}
}
