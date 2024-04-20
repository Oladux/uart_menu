/*
 * menu_misc.c
 *
 *  Created on: 20 апр. 2024 г.
 *      Author: Stepan
 */
#include "menu_misc.h"

char* converted_str;
uint8_t Lenstr(const char* str)
{
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}
void int_to_str(int16_t input_int){
	uint8_t digits = 0;
	uint32_t buf = input_int;
	do{
		++digits;
		buf/= 10;
	}while (buf != 0);
	char str[digits];
	sprintf(str,"%d",input_int);
	converted_str = str;
}
