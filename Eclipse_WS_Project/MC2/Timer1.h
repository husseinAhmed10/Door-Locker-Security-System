/*
 * Timer1.h
 *
 *  Created on: Jul 1, 2023
 *      Author: T.S
 */

#ifndef TIMER1_H_
#define TIMER1_H_


/*Data Types*/

#include "std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum
{
	NO_CLK_SOURCE, CLK_PRESCALER_1, CLK_PRESCALER_8, CLK_PRESCALER_64, CLK_PRESCALER_256, CLK_PRESCALER_1024
}Timer1_Prescaler;

typedef enum
{
	NORMAL_MODE, COMPARE_MODE = 4
}Timer1_Mode;

typedef struct {
uint16 initial_value;
uint16 compare_value;
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;


/*Function Definition*/


/*a.
● Description
⮚ Function to initialize the Timer driver
● Inputs: pointer to the configuration structure with type
Timer1_ConfigType.
● Return: None*/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*b.
● Description
⮚ Function to disable the Timer1.
● Inputs: None
● Return: None*/
void Timer1_deInit(void);

/*c.
● Description
⮚ Function to set the Call Back function address.
● Inputs: pointer to Call Back function.
● Return: None*/
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
