/*
 * gpio.c
 *
 *  Created on: Feb 11, 2024
 *      Author: Somia
 */
#include "gpio.h"
uint8_t Get_CRLH_pinPosition(uint16_t PinNumber){
	switch(PinNumber){
	    case GPIO_PIN_0:  return 0  ; break ;
	    case GPIO_PIN_1:  return 4  ; break ;
	    case GPIO_PIN_2:  return 8  ; break ;
	    case GPIO_PIN_3:  return 12 ; break ;
	    case GPIO_PIN_4:  return 16 ; break ;
	    case GPIO_PIN_5:  return 20 ; break ;
	    case GPIO_PIN_6:  return 24 ; break ;
	    case GPIO_PIN_7:  return 28 ; break ;
	    case GPIO_PIN_8:  return 0  ; break ;
	    case GPIO_PIN_9:  return 4  ; break ;
	    case GPIO_PIN_10: return 8  ; break ;
	    case GPIO_PIN_11: return 12 ; break ;
	    case GPIO_PIN_12: return 16 ; break ;
	    case GPIO_PIN_13: return 20 ; break ;
	    case GPIO_PIN_14: return 24 ; break ;
	    case GPIO_PIN_15: return 28 ; break ;
	}
}
/**================================================================
* @Fn          -MCAL_GPIO_Init
* @brief       - initializes gpio x pin y according to info provided in PinConfig
* @param [in]  - GPIOx: A B C D E gpio peripheral
* @param [in]  - PinConfig: pointer to a struct that contains the configuration of gpio pin
* @param [out] - none
* @retval      - none
* Note         - STM32F103 has A B C D E modules but the pkg LQFP48 doesnt fully inc C B and no E module
*/
void MCAL_GPIO_Init(GPIO_Typedef *GPIOx, GPIO_PinConfig_t *PinConfig){
     //Port configuration register low (GPIOx_CRL) configure pins  0-->7
	 //Port configuration register high (GPIOx_CRH) configure pins 8-->15
	volatile uint32_t * config_Reg = NULL;
	uint8_t  config_Pin = 0;
	config_Reg = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->CRL: &GPIOx->CRH;
	//clear CNF MODE for the pin
	(* config_Reg) &= ~(0xf << Get_CRLH_pinPosition(PinConfig->GPIO_PinNumber));
    //check pin input or output
	//output
	if ((PinConfig->GPIO_MODE > GPIO_MODE_INPUT_PD) && (PinConfig->GPIO_MODE < GPIO_MODE_AF_INPUT)){
		//mod --> speed first 2 bits
		config_Pin = ( ( ( (PinConfig->GPIO_MODE - 4) <<2 ) | (PinConfig->GPIO_Output_Speed)) & 0x0f);
		(* config_Reg) |= ( config_Pin << Get_CRLH_pinPosition(PinConfig->GPIO_PinNumber));
	}
	//input
	else{
		if ((PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO) || (PinConfig->GPIO_MODE == GPIO_MODE_Analog)){
				//mod --> 0x00
				config_Pin = ((( ( (PinConfig->GPIO_MODE) <<2 ) | 0x0)) & 0x0f);
			}
		else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT){
			//same as input floating
			config_Pin = ( (( ( GPIO_MODE_INPUT_FLO <<2 ) | 0x0)) & 0x0f);
		}
		else{
			//input pull up pull down
			config_Pin = ( ( (( GPIO_MODE_INPUT_PU <<2 ) | 0x0)) & 0x0f);
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU){
				//TABLE 20 pxODR 1
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else{
				//TABLE 20 pxODR 0
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}
	(* config_Reg) |= ( config_Pin << Get_CRLH_pinPosition(PinConfig->GPIO_PinNumber));


}
/**================================================================
* @Fn          -MCAL_GPIO_Deinit
* @brief       - reset all gpio reg for a specific port x: A B C D E
* @param [in]  - GPIOx: A B C D E gpio peripheral
* @param [out] - none
* @retval      - none
* Note         - STM32F103 has A B C D E modules but the pkg LQFP48 doesnt fully inc C B and no E module
*/
void MCAL_GPIO_Deinit(GPIO_Typedef *GPIOx){
	// 1- manual reset
	// manually put default value in regesters of GPIOx

	// 2 - using reset controller
	// better because we reset registers PLUS timers and circuit

	if (GPIOx == GPIOA){
		//set then reset to store to default
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	} else if (GPIOx == GPIOB){
		//set then reset to store to default
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}else if (GPIOx == GPIOC){
		//set then reset to store to default
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}else if (GPIOx == GPIOD){
		//set then reset to store to default
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}else if (GPIOx == GPIOE){
		//set then reset to store to default
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}

}
/**================================================================
* @Fn          -MCAL_GPIO_ReadPin
* @brief       - read value on specific pin
* @param [in]  - GPIOx: A B C D E gpio peripheral
* @param [in]  - PinNumber: choose pin number according to @ref GPIO_PINS_define
* @retval      - the value on the input pin (two values based on @ref GPIO_PIN_state)
* Note         - STM32F103 has A B C D E modules but the pkg LQFP48 doesnt fully inc C B and no E module
*/
uint8_t MCAL_GPIO_ReadPin (GPIO_Typedef *GPIOx , uint16_t PinNumber){
	uint8_t bitstatus;
	if (((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_RESET){bitstatus = GPIO_PIN_SET;}
	else {bitstatus = GPIO_PIN_RESET;}
	return bitstatus;
}
/**================================================================
* @Fn          -MCAL_GPIO_ReadPort
* @brief       - read value on specific port
* @param [in]  - GPIOx: A B C D E gpio peripheral
* @retval      - the value on the input port
* Note         - STM32F103 has A B C D E modules but the pkg LQFP48 doesnt fully inc C B and no E module
*/
uint16_t MCAL_GPIO_ReadPort (GPIO_Typedef *GPIOx){
	uint16_t port_value;
	port_value = (uint16_t)(GPIOx->IDR);
	return port_value;
}
/**================================================================
* @Fn          -MCAL_GPIO_ReadPin
* @brief       - read value on specific pin
* @param [in]  - GPIOx: A B C D E gpio peripheral
* @param [in]  - PinNumber: choose pin number according to @ref GPIO_PINS_define
* @param [in]  - Value: value written on pin (two values based on @ref GPIO_PIN_state)
* @retval      - none
* Note         - STM32F103 has A B C D E modules but the pkg LQFP48 doesnt fully inc C B and no E module
*/
void     MCAL_GPIO_WritePin  (GPIO_Typedef *GPIOx , uint16_t PinNumber , uint8_t Value){
	if (Value != GPIO_PIN_RESET){
		// method number one through oring in ODR reg
		// GPIOx->ODR |= PinNumber;

		// method number one through setting in BSRR reg
		//BSy: Port x Set bit y (y= 0 .. 15)
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Set the corresponding ODRx bi
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else{
		//BRy: Port x Reset bit y (y= 0 .. 15)
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Reset the corresponding ODRx bit
		GPIOx->BRR = (uint32_t)PinNumber;
	}

}
/**================================================================
* @Fn          -MCAL_GPIO_ReadPort
* @brief       - read value on specific port
* @param [in]  - GPIOx: A B C D E gpio peripheral
* @param [in]  - Value: value written on port
* @retval      - none
* Note         - STM32F103 has A B C D E modules but the pkg LQFP48 doesnt fully inc C B and no E module
*/
void     MCAL_GPIO_WritePort (GPIO_Typedef *GPIOx , uint16_t Value){
	GPIOx->ODR = (uint32_t)Value;
}
/**================================================================
* @Fn          - MCAL_GPIO_ReadPin
* @brief       - toggle value on specific pin
* @param [in]  - GPIOx: A B C D E gpio peripheral
* @param [in]  - PinNumber: choose pin number according to @ref GPIO_PINS_define
* @retval      - none
* Note         - STM32F103 has A B C D E modules but the pkg LQFP48 doesnt fully inc C B and no E module
*/
void     MCAL_GPIO_TogglePin   (GPIO_Typedef *GPIOx , uint16_t PinNumber){
	GPIOx->ODR ^= PinNumber;
}
/**================================================================
* @Fn          - MCAL_GPIO_ReadPin
* @brief       - lock a specific pin
* @param [in]  - GPIOx: A B C D E gpio peripheral
* @param [in]  - PinNumber: choose pin number according to @ref GPIO_PINS_define
* @retval      - OK and ERROR according to value @ref GPIO_LOCK_RETURN
* Note         - STM32F103 has A B C D E modules but the pkg LQFP48 doesnt fully inc C B and no E module
*/
uint8_t     MCAL_GPIO_LockPin   (GPIO_Typedef *GPIOx , uint16_t PinNumber){
	//Bit 16 LCKK[16]: Lock key
	//This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//0: Port configuration lock key not active
	//1: Port configuration lock key active. GPIOx_LCKR register is locked until an MCU reset
	//occurs.
	//LOCK key writing sequence:
	//Write 1
	//Write 0
	//Write 1
	//Read 0
	//Read 1 (this read is optional but confirms that the lock is active)
	//Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//Any error in the lock sequence will abort the lock.
	//Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//These bits are read write but can only be written when the LCKK bit is 0.
	//0: Port configuration not locked
	//1: Port configuration locked

	//1- set LCKK[16]
	volatile uint32_t tmp = 1<<16;
	//2- set LCKy
	tmp |= PinNumber;

	//Write 1
	GPIOx->LCKR = tmp;
	//Write 0
	GPIOx->LCKR = PinNumber;
	//Write 1
	GPIOx->LCKR = tmp;
	//Read 0
	tmp = GPIOx->LCKR;
	//Read 1  (this read is optional but confirms that the lock is active)
	if ((uint32_t)(GPIOx->LCKR & 1<<16)) {return GPIO_LOCK_RETURN_OK;}
	else {return GPIO_LOCK_RETURN_ERROR;}
}
