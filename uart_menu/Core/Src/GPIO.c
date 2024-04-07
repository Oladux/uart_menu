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

/* The general GPIO function called from the menu */
void GPIO(){
	create_menu(&MGPIO1);
}

void GPIO_pin_select(){
	GPIO_input(GPIO_PIN_SELECT);
}
void GPIO_pin_write(){
	GPIO_input(GPIO_PIN_WRITE);
	debug_output(1, GPIO_command);
	if(GPIO_command != GPIO_PIN_RESET)
	  {
	    current_GPIO->BSRR = pin_input;
	  }
	else
	  {
		current_GPIO->BSRR = (uint32_t)pin_input << 16U;
	  }
	Current_menu=Current_menu->parent;
	print_menu();
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
	print_menu();
}
void GPIO_pin_input(){
	print_input_message("Input GPIO pin");
	GPIO_command = ASCII_to_int(command_recieve());
	pin_input=GPIO_command;
	if ((pin_input <= 15) && ((pin_input > 0))){
		pin_input=pow(2,pin_input);
	}
	debug_output(1, pin_input);
}

void GPIO_port_input(){
	print_input_message("Input GPIO port");
	GPIO_command = command_recieve();
	GPIO_port_convert(GPIO_command);
	debug_output(1, GPIO_command);
}

void GPIO_pin_write_input(){
	print_input_message("Input GPIO value");
	GPIO_command=ASCII_to_int(command_recieve())%2;
}
/*Conversion of input_port from ASCII to int */
void GPIO_port_convert(uint8_t input){
	switch (input) {
		case A:
			current_GPIO = GPIOA;
			break;
		case B:
			current_GPIO = GPIOB;
			break;
		case C:
			current_GPIO = GPIOC;
			break;
		case D:
			current_GPIO = GPIOD;
			break;
		case E:
			current_GPIO = GPIOE;
			break;
		case H:
			current_GPIO = GPIOH;
			break;
		default:
			current_GPIO = GPIO_NONE;
			break;
	}
}
/*Conversion of input_pin from ASCII to int */
uint8_t ASCII_to_int(uint8_t ASCII_value){
	uint8_t out_value=0;
	out_value=ASCII_value-48;
	return out_value;
}


