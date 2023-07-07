/*
 * DCmotor.c
 *
 *  Created on: May 6, 2023
 *      Author: T.S
 */

#include "DCmotor.h"
#include "common_macros.h"
#include <avr/io.h>
#include "gpio.h"
#include "pwm.h"
#include "std_types.h"

/*
 • Description
 ➢ The Function responsible for setup the direction for the two
 motor pins through the GPIO driver.
 ➢ Stop at the DC-Motor at the beginning through the GPIO driver.
 • Inputs: None
 • Return: None
 */

void DcMotor_Init(void) {

	/*Set the pin direction*/
	GPIO_setupPinDirection(motor_port, motor_pin1, PIN_OUTPUT);
	GPIO_setupPinDirection(motor_port, motor_pin2, PIN_OUTPUT);

	/*Stop at the beginning*/
	GPIO_writePin(motor_port, motor_pin1, LOGIC_LOW);
	GPIO_writePin(motor_port, motor_pin2, LOGIC_LOW);

}

/*
 • Description:
 ➢ The function responsible for rotate the DC Motor CW/ or A-CW or
 stop the motor based on the state input state value.
 ➢ Send the required duty cycle to the PWM driver based on the
 required speed value.
 • Inputs:
 ➢ state: The required DC Motor state, it should be CW or A-CW or stop.
 DcMotor_State data type should be declared as enum or uint8.
 ➢ speed: decimal value for the required motor speed, it should be from
 0 → 100. For example, if the input is 50, The motor should rotate with
 50% of its maximum speed.
 • Return: None
 * */

void DcMotor_Rotate(DcMotor_State state, uint8 speed) {

	uint8 currentSpeed = (((float32) speed / 100) * 256);

	switch (state) {

	case 1: /*Clockwise */

		GPIO_writePin(motor_port, motor_pin1, LOGIC_HIGH);
		GPIO_writePin(motor_port, motor_pin2, LOGIC_LOW);

		if (speed == 25) {

			/*PWM_Timer0_Start(64);*/
			/*PWM_Timer0_Start(((float32)speed/100)*256);*/
			PWM_Timer0_Start(currentSpeed);
		} else if (speed == 50) {

			/*PWM_Timer0_Start(128);*/
			/*PWM_Timer0_Start(((float32)speed/100)*256);*/
			PWM_Timer0_Start(currentSpeed);

		} else if (speed == 75) {

			/*PWM_Timer0_Start(192);*/
			/*PWM_Timer0_Start(((float32)speed/100)*256);*/
			PWM_Timer0_Start(currentSpeed);

		} else if (speed == 100) {

			/*PWM_Timer0_Start(255);*/
			/*PWM_Timer0_Start(((float32)speed/100)*255);*/
			PWM_Timer0_Start(currentSpeed-1);

		}

		break;

	case 2: /*Anti clock wise */

		GPIO_writePin(motor_port, motor_pin2, LOGIC_HIGH);
		GPIO_writePin(motor_port, motor_pin1, LOGIC_LOW);

		if (speed == 25) {

			PWM_Timer0_Start(64);
		} else if (speed == 50) {

			PWM_Timer0_Start(128);

		} else if (speed == 75) {

			PWM_Timer0_Start(192);

		} else if (speed == 100) {

			PWM_Timer0_Start(255);

		}

		break;

	default: /*Stop*//*case 0*/

		GPIO_writePin(motor_port, motor_pin1, LOGIC_LOW);
		GPIO_writePin(motor_port, motor_pin2, LOGIC_LOW);
		PWM_Timer0_Start(0);

	}

}
