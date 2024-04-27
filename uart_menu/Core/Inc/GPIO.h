/*
 * GPIO.h
 *
 *  Created on: Mar 30, 2024
 *      Author: Stepan
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_
#include <menu.h>
#endif /* INC_GPIO_H_ */

#define ASCII_TO_INT(ASCII_value) ASCII_value-48
//Functions prototypes

extern void Print_menu_value(char*);

void GPIO_port_convert(uint8_t);
//uint8_t ASCII_to_int(uint8_t);

void GPIO_pin_input();
void GPIO_port_input();

void GPIO_input(uint8_t);
void GPIO_pin_select();
void GPIO_pin_write();
void GPIO_pin_write_input();

enum GPIO_INPUT_MODE{
	GPIO_PIN_SELECT,
	GPIO_PIN_WRITE,
};

