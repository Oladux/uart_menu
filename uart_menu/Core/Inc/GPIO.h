/*
 * GPIO.h
 *
 *  Created on: Mar 30, 2024
 *      Author: Stepan
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_
#endif /* INC_GPIO_H_ */

//Functions prototypes

void GPIO_port_convert(uint8_t);
void GPIO_pin_convert(uint8_t);

void GPIO_pin_input();
void GPIO_port_input();

void GPIO_pin_select();
void GPIO_input(uint8_t);

enum GPIO_INPUT_MODE{
	PIN_SELECT,
};
