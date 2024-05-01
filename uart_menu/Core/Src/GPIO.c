/*
 * GPIO.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Stepan
 */
#include "GPIO.h"

extern Menu_Item_t MGPIO1;

/* Variables */

GPIO_TypeDef* const GPIO_NONE= {0};
GPIO_TypeDef* current_GPIO = GPIO_NONE;

GPIO_InitTypeDef GPIO_init = {0};

uint32_t GPIO_pin=0;
uint32_t GPIO_command=0;
uint8_t GPIO_write_state=0;
char chosen_port='N'; uint8_t chosen_pin=0;

/* GPIO functions */

/* The general GPIO function called from the menu */
void GPIO(){
	Menu_type=GPIO_MENU_TYPE;
	create_menu(&MGPIO1);
}

/* MGPIO1 */
void GPIO_pin_select(){
	GPIO_input(GPIO_PIN_SELECT);
}
/* MGPIO2 */
void GPIO_pin_write(){
	GPIO_input(GPIO_PIN_WRITE);
	if(GPIO_write_state != GPIO_PIN_RESET)
	  {
	    current_GPIO->BSRR = GPIO_pin;
	  }
	else
	  {
		current_GPIO->BSRR = (uint32_t)GPIO_pin << 16U;
	  }
	Print_menu_value(GPIO_write_state);
	Back_menu();
	Print_menu();
}
/* MGPIO3 */
void GPIO_pin_init(){

	static uint8_t GPIO_init_status = 0;

	GPIO_InitTypeDef GPIO_init = {0};
	if(GPIO_init_status){
		 HAL_GPIO_DeInit(current_GPIO, GPIO_pin);

		 GPIO_init_status++;
		 GPIO_init_status %= 2;

		 Print_menu_value(GPIO_init_status);
		 Back_menu();
		 Print_menu();
	}
	else{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();

		HAL_GPIO_WritePin(current_GPIO, GPIO_pin, GPIO_PIN_RESET);
		GPIO_init.Pin = GPIO_pin;
		GPIO_init.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_init.Pull = GPIO_NOPULL;

		HAL_GPIO_Init(current_GPIO, &GPIO_init);

		GPIO_init_status++;
		GPIO_init_status %= 2;

		Print_menu_value(GPIO_init_status);
		Back_menu();
		Print_menu();
	}
}
/*MGPIO4*/
void GPIO_pin_speed(){
	char* speed_messages[]={"Low","Medium","High","Very high"};
	static uint8_t GPIO_speed_status = 0;
	GPIO_speed_status++; GPIO_speed_status %= 4;

	GPIO_init.Speed=GPIO_speed_status;
	HAL_GPIO_Init(current_GPIO, &GPIO_init);

	Print_menu_string(speed_messages[GPIO_speed_status]);
	Back_menu();
	Print_menu();
}


/*GPIO input functions */

/* User input of GPIO */
void GPIO_input(uint8_t GPIO_mode){
	switch (GPIO_mode){
		case GPIO_PIN_SELECT:
			GPIO_pin_input();
			GPIO_port_input();

			break;
		case GPIO_PIN_WRITE:
			GPIO_pin_write_input();

			break;
		default:
			break;
	}
	Print_menu();
}

void GPIO_pin_input(){
	Print_input_message("Input GPIO pin");
	GPIO_command = ASCII_TO_INT(command_recieve());
	GPIO_pin=GPIO_command;
	chosen_pin=GPIO_pin;
	if ((GPIO_pin <= 15) && ((GPIO_pin > 0))){
		GPIO_pin=1<<GPIO_pin;
	}
	else {GPIO_pin=0; chosen_pin=0;}
	/* Debug_output(pin_input); */
}

void GPIO_port_input(){
	Print_input_message("Input GPIO port");
	GPIO_command = command_recieve();
	GPIO_port_convert(ASCII_TO_INT(GPIO_command));
	/* Debug_output(GPIO_command); */
}

void GPIO_pin_write_input(){
	GPIO_write_state=(GPIO_write_state+1)%2;
}

/*Conversion of input_port from ASCII to int */
void GPIO_port_convert(uint8_t input){
	switch (input) {
		case A:
			current_GPIO = GPIOA;
			chosen_port='A';
			break;
		case B:
			current_GPIO = GPIOB;
			chosen_port='B';
			break;
		case C:
			current_GPIO = GPIOC;
			chosen_port='C';
			break;
		case D:
			current_GPIO = GPIOD;
			chosen_port='D';
			break;
		case E:
			current_GPIO = GPIOE;
			chosen_port='E';
			break;
		case H:
			current_GPIO = GPIOH;
			chosen_port='H';
			break;
		default:
			current_GPIO = GPIO_NONE;
			break;
	}
}
