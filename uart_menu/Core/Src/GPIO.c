/*
 * GPIO.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Stepan
 */
#include <menu.h>
#include "GPIO.h"

extern Menu_Item_t MGPIO1;

GPIO_TypeDef* const GPIO_NONE= {0};
GPIO_TypeDef* current_GPIO = GPIO_NONE;

uint32_t pin_input=0;
uint32_t GPIO_command=0;
uint8_t GPIO_write_state=0;
char chosen_port='N'; uint8_t chosen_pin=0;

/* The general GPIO function called from the menu */
void GPIO(){
	create_menu(&MGPIO1);
	Menu_type=GPIO_MENU_TYPE;
	Print_menu();
}

/*MGPIO1*/
void GPIO_pin_select(){
	GPIO_input(GPIO_PIN_SELECT);
}
/*MGPIO2*/
void GPIO_pin_write(){
	GPIO_input(GPIO_PIN_WRITE);
	if(GPIO_write_state != GPIO_PIN_RESET)
	  {
	    current_GPIO->BSRR = pin_input;
	  }
	else
	  {
		current_GPIO->BSRR = (uint32_t)pin_input << 16U;
	  }
	Current_menu=Current_menu->prev;
	Print_menu();
}

/* User input of GPIO in HAL format */
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
	print_input_message("Input GPIO pin");
	GPIO_command = ASCII_TO_INT(command_recieve());
	pin_input=GPIO_command;
	chosen_pin=pin_input;
	if ((pin_input <= 15) && ((pin_input > 0))){
		pin_input=1<<pin_input;
	}
	else {pin_input=0; chosen_pin=0;}
	debug_output(pin_input);
}

void GPIO_port_input(){
	print_input_message("Input GPIO port");
	GPIO_command = command_recieve();
	GPIO_port_convert(ASCII_TO_INT(GPIO_command));
	debug_output(GPIO_command);
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
