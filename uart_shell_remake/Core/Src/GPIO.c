/*
 * GPIO.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Stepan
 */
#include <menu.h>
#include "GPIO.h"

GPIO_TypeDef* const GPIO_NONE= {0};
GPIO_TypeDef* current_GPIO = GPIO_NONE;

uint32_t pin_input;
uint16_t port_input;

/* The general GPIO function called from the menu */
void GPIO(){
	GPIO_handler();
}

/* The GPIO handler that calls all other functions */
void GPIO_handler(){
		GPIO_port_input();
		GPIO_pin_input();
	    current_GPIO->BSRR=pin_input;
	    HAL_GPIO_WritePin(current_GPIO, current_GPIO->BSRR,1);
}

/* User input of GPIO pin in HAL format */
void GPIO_pin_input(){
	print_menu_string("Input GPIO pin:\n");
	uint8_t command = command_recieve();
	GPIO_pin_convert(command);
	if ((pin_input <= 15)&&((pin_input > 0))){
		pin_input=pow(2,pin_input);
	}
}

/*User input of GPIO port in HAL format */
void GPIO_port_input(){
	print_menu_string("Input GPIO port:\n");
	uint8_t command = command_recieve();
	GPIO_port_convert(command);
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
void GPIO_pin_convert(uint8_t input){
	switch (input) {
		case 48:
			pin_input = 0;
			break;
		case 49:
			pin_input = 1;
			break;
		case 50:
			pin_input = 2;
			break;
		case 51:
			pin_input = 3;
			break;
		case 52:
			pin_input = 4;
			break;
		case 53:
			pin_input = 5;
			break;
		case 54:
			pin_input = 6;
			break;
		case 55:
			pin_input = 7;
			break;
		case 56:
			pin_input = 8;
			break;
		case 57:
			pin_input = 9;
			break;
		case 10:
			pin_input = 10;
			break;
		case 11:
			pin_input = 11;
			break;
		case 12:
			pin_input = 12;
			break;
		case 13:
			pin_input = 13;
			break;
		case 14:
			pin_input = 14;
			break;
		case 15:
			pin_input = 15;
			break;
		default:
			pin_input = 0;
			break;
	}
}


