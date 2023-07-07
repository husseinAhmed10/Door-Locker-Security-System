/*
 * buzzer.c
 *
 *  Created on: May 23, 2023
 *      Author: T.S
 */

#include "buzzer.h"
#include "gpio.h"
#include "std_types.h"

void Buzzer_init() {

	GPIO_setupPinDirection(buzzer_port, buzzer_pin, PIN_OUTPUT);

	/*Silent at the beginning*/
	GPIO_writePin(buzzer_port, buzzer_pin, LOGIC_LOW);

	GPIO_setupPinDirection(led_port, led_pin, PIN_OUTPUT);

	/*Off at the beginning*/
	GPIO_writePin(led_port, led_pin, LOGIC_LOW);

}

/*b. void Buzzer_on(void)
 ● Description
 ⮚ Function to enable the Buzzer through the GPIO.
 ● Inputs: None
 ● Return: None*/

void Buzzer_on(void) {

	/*Sound Alarm*/
	GPIO_writePin(buzzer_port, buzzer_pin, LOGIC_HIGH);
	/*on at the alarm*/
	GPIO_writePin(led_port, led_pin, LOGIC_HIGH);

}

/*c. void Buzzer_off(void)
 ● Description
 ⮚ Function to disable the Buzzer through the GPIO.
 ● Inputs: None
 ● Return: No*/

void Buzzer_off(void) {

	/*Silent*/
	GPIO_writePin(buzzer_port, buzzer_pin, LOGIC_LOW);
	/*Off */
	GPIO_writePin(led_port, led_pin, LOGIC_LOW);

}
