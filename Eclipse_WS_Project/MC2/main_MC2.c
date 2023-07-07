/*
 * main_MC2.c
 *
 *  Created on: Jul 1, 2023
 *      Author: T.S
 */

#include "uart.h"
#include "twi.h"
#include "external_eeprom.h"
#include "DCmotor.h"
#include "Timer1.h"
#include "buzzer.h"
#include <util/delay.h>
#include <avr/io.h>

#define HMI_MC1_READY_UART			0x00
#define CONTROL_MC2_READY_UART		0xFF

#define PASSWORD_MATCH			TRUE
#define PASSWORD_UNMATCH		FALSE

#define CHANGING_PASSWORD 3

#define password_length 5

uint8 matching = 0;	/*To check matching when password enter in the main menu*/
uint8 g_wrongPasswordCounter = 0;	/*counter for # of wrong password*/

/*Compared value calculation: compared value = (8MHz/1024 prescalar) = 7812.5 ~ 7813*/

Timer1_ConfigType g_timer1_config = { 0, 7813, CLK_PRESCALER_1024, COMPARE_MODE };
uint8 g_ticks;
void Timer_CallBackFunction(void) {
	g_ticks++;
}

uint8 password[password_length + 2];	/*Created password*/
uint8 confirm[password_length + 2];		/*Confirmed password*/

uint8 saved_pass[password_length + 2];	/*password get from EEPROM*/
uint8 entered_pass[password_length + 2];	/*password entered for the main menu*/

/*Function Prototype*/

uint8 ReceivePassword();

uint8 compare_password_confirmation(uint8 *password, uint8 *confirm);
void Save_password_eeprom();
void read_password_eeprom();

void Door(void);

void Buzzer_Alarm(void);
void check_password_entered();

/*Main Function*/

int main(void) {

	uint8 receivedbyte;


	SREG |= (1 << 7);
	UART_configType configPtr = { 9600, NO_Parity, One_Stop_Bit, Data_8_Bits };
	UART_init(&configPtr);

	TWI_ConfigType config = {(0x1), 0x02};
	TWI_init(&config);

	DcMotor_Init();
	Buzzer_init();

	/*Do not go to main menu until password creation at the beginning*/

	do {
		receivedbyte = ReceivePassword();
	} while (receivedbyte == 0);

	while (1) {

		/*Send Ready byte to HMI_ECU to start sending password string*/
		UART_sendByte(CONTROL_MC2_READY_UART);
		receivedbyte = UART_recieveByte();

		if (receivedbyte == '+') {

			do {
				UART_sendByte(CONTROL_MC2_READY_UART);

				UART_receiveString(entered_pass);

				check_password_entered();
			} while (matching == 0);

			Door();
		} else if (receivedbyte == '-') {
			do {
				UART_sendByte(CONTROL_MC2_READY_UART);

				UART_receiveString(entered_pass);

				check_password_entered();
			} while (matching == 0);

			do {
				receivedbyte = ReceivePassword();
			} while (receivedbyte == 0);
		}

	}

	return 0;
}

/*Function Definition*/

/*To receive the password from the user only
 * Return matching password or not*/

uint8 ReceivePassword() {

	/*1->clock , 2->anti*/

	uint8 receiveByte;

	/*Send Ready byte to HMI_ECU to start sending password string*/
	UART_sendByte(CONTROL_MC2_READY_UART);

	UART_receiveString(password);

	UART_sendByte(CONTROL_MC2_READY_UART);

	UART_receiveString(confirm);

	matching=0;
	matching = compare_password_confirmation(password, confirm);

	/*****************************Send Confirmation***********************************/
	/*Wait for HMI_ECU to be ready*/
	/*while (UART_recieveByte() != HMI_MC1_READY_UART) {
		}	//it's better to use this method
	 */

	receiveByte = UART_recieveByte();

	if (matching) {
		UART_sendByte(PASSWORD_MATCH);
		//Control_StorePasswordInEEPROM(password_first);
		Save_password_eeprom();
		return 1;

	}

	else {
		UART_sendByte(PASSWORD_UNMATCH);
		//Control_CompareAndStorePassword();
		return 0;
	}

}

/*Compare the matching between the received password and the confirmation password*/

uint8 compare_password_confirmation(uint8 *password, uint8 *confirm) {


		for (uint8 i = 0; i < 5; i++) {

			if (password[i] == confirm[i]) {
				if (i == 4) {
					//UART_sendByte(CONTROL_MC2_READY_UART);
					//UART_sendByte(PASSWORD_MATCH);
					//matching = 1;
					return 1;
				}

				continue;
			} else {
				//UART_sendByte(CONTROL_MC2_READY_UART);
				//UART_sendByte(PASSWORD_UNMATCH);
				//break;
				return 0;
			}

		}


}

/*Store the password in EEPROM*/

void Save_password_eeprom() {

	for (uint8 i = 0; i < password_length; i++) {
		/*The stored address is 0x00 */
		EEPROM_writeByte((0x00) + i, (password [i]));
		_delay_ms(100);
	}

}

/*Read the password from EEPROM*/

void read_password_eeprom() {

	for (uint8 i = 0; i < password_length; i++) {
		/*The stored address is 0x00 */
		EEPROM_readByte((0x00) + i, &(saved_pass [i]));
		_delay_ms(100);
	}

}

/*
 * • rotates motor for 15-seconds CW and display a message on the screen
“Door is Unlocking”
• hold the motor for 3-seconds.
• rotates motor for 15-seconds A-CW and display a message on the screen
“Door is Locking”
*/

void Door(void) {
	Timer1_init(&g_timer1_config);
	Timer1_setCallBack(&Timer_CallBackFunction);

	g_ticks = 0;
	DcMotor_Rotate(1, 100);
	while (g_ticks < 15)
		;

	g_ticks = 0;
	DcMotor_Rotate(0, 100);
	while (g_ticks < 3)
		;

	g_ticks = 0;
	DcMotor_Rotate(2, 100);
	while (g_ticks < 15)
		;

	DcMotor_Rotate(0, 100);
	Timer1_deInit();
}

/*If the two passwords are not matched for the third consecutive time, then:
• Activate Buzzer for 1-minute.
• Display error message on LCD for 1 minute.*/

void Buzzer_Alarm(void) {
	Timer1_init(&g_timer1_config);
	Timer1_setCallBack(&Timer_CallBackFunction);

	Buzzer_on();

	g_ticks = 0;
	while (g_ticks < 60)
		;

}

/*To compared the entered password to the one saved in EEPROM*/

void check_password_entered() {

	uint8 receiveByte;
	read_password_eeprom();
	matching = 0;
	for (uint8 i = 0; i < 5; i++) {

		if (entered_pass[i] == saved_pass[i]) {
			if (i == 4) {
				receiveByte = UART_recieveByte();
				UART_sendByte(PASSWORD_MATCH);
				matching = 1;
				g_wrongPasswordCounter = 0;
			}

			continue;
		} else {
			g_wrongPasswordCounter++;
			receiveByte = UART_recieveByte();
			UART_sendByte(PASSWORD_UNMATCH);

			if (g_wrongPasswordCounter == CHANGING_PASSWORD) {
				Buzzer_Alarm();
				matching = 1;
				g_wrongPasswordCounter=0;
			}

			break;
		}

	}

}