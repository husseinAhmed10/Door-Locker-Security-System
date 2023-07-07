/*
 * DCmotor.h
 *
 *  Created on: May 6, 2023
 *      Author: T.S
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"


/*Data Types*/
#define motor_port PORTB_ID
#define motor_pin1 PIN0_ID
#define motor_pin2 PIN1_ID


typedef enum {
	stop=0, CW=1, ACW=2
} DcMotor_State;

/*Function Prototype*/
void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DCMOTOR_H_ */
