/*
 * gpio.h
 *
 *  Created on: Feb 11, 2024
 *      Author: Somia
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f10x6.h"
//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct{
	uint16_t GPIO_PinNumber ; //Specify GPIO pin number, must be a value of ref GPIO_PINS_define
    uint8_t  GPIO_MODE; //Specify GPIO pin operation mode, must be a value of ref GPIO_MODE_define
    uint8_t  GPIO_Output_Speed; //Specify GPIO pin if output the speed, must be a value of ref GPIO_SPEED_define
}GPIO_PinConfig_t;
//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PINS_define
#define GPIO_PIN_0 ((uint16_t)0x0001) //pin 0 1
#define GPIO_PIN_1 ((uint16_t)0x0002) //pin 1 10
#define GPIO_PIN_2 ((uint16_t)0x0004) //pin 2 100
#define GPIO_PIN_3 ((uint16_t)0x0008) //pin 3 1000
#define GPIO_PIN_4 ((uint16_t)0x0010) //pin 4
#define GPIO_PIN_5 ((uint16_t)0x0020) //pin 5
#define GPIO_PIN_6 ((uint16_t)0x0040) //pin 6
#define GPIO_PIN_7 ((uint16_t)0x0080) //pin 7
#define GPIO_PIN_8 ((uint16_t)0x0100) //pin 8
#define GPIO_PIN_9 ((uint16_t)0x0200) //pin 9
#define GPIO_PIN_10 ((uint16_t)0x0400) //pin 10
#define GPIO_PIN_11 ((uint16_t)0x0800) //pin 11
#define GPIO_PIN_12 ((uint16_t)0x1000) //pin 12
#define GPIO_PIN_13 ((uint16_t)0x2000) //pin 13
#define GPIO_PIN_14 ((uint16_t)0x4000) //pin 14
#define GPIO_PIN_15 ((uint16_t)0x8000) //pin 15
#define GPIO_PIN_ALL ((uint16_t)0xFFFF)

//@ref GPIO_MODE_define
#define GPIO_MODE_Analog          0x00000000u //Analog mode
#define GPIO_MODE_INPUT_FLO       0x00000001u //Floating input
#define GPIO_MODE_INPUT_PU        0x00000002u //pull up
#define GPIO_MODE_INPUT_PD        0x00000003u //pull down
#define GPIO_MODE_OUTPUT_PP       0x00000004u //general purpose push pull
#define GPIO_MODE_OUTPUT_OD       0x00000005u //general purpose open drain
#define GPIO_MODE_OUTPUT_AF_PP    0x00000006u //alternative function push pull
#define GPIO_MODE_OUTPUT_AF_OD    0x00000007u //alternative function open drain
#define GPIO_MODE_AF_INPUT        0x00000008u //Floating input (reset state) == Alternate function input

//@ref GPIO_SPEED_define
#define GPIO_SPEED_10M 0x00000001u // max speed 10 mega HZ
#define GPIO_SPEED_2M  0x00000002u // max speed 2 mega HZ
#define GPIO_SPEED_50M 0x00000003u // max speed 50 mega HZ

//@ref GPIO_PIN_state
#define GPIO_PIN_SET 1   //HIGH
#define GPIO_PIN_RESET 0 //LOW

//@ref GPIO_LOCK_RETURN
#define GPIO_LOCK_RETURN_OK    0
#define GPIO_LOCK_RETURN_ERROR 1
/*@ref Module_REF_NAME_define
*/
/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void     MCAL_GPIO_Init      (GPIO_Typedef *GPIOx, GPIO_PinConfig_t *PinConfig);
void     MCAL_GPIO_Deinit    (GPIO_Typedef *GPIOx);
uint8_t  MCAL_GPIO_ReadPin   (GPIO_Typedef *GPIOx , uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort  (GPIO_Typedef *GPIOx);
void     MCAL_GPIO_WritePin  (GPIO_Typedef *GPIOx , uint16_t PinNumber , uint8_t Value);
void     MCAL_GPIO_WritePort (GPIO_Typedef *GPIOx , uint16_t Value);
void     MCAL_GPIO_TogglePin   (GPIO_Typedef *GPIOx , uint16_t PinNumber);
uint8_t  MCAL_GPIO_LockPin   (GPIO_Typedef *GPIOx , uint16_t PinNumber);



#endif /* INC_GPIO_H_ */
