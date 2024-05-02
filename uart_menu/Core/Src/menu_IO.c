/*
 * menu_IO.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Stepan
 */
#include "menu_IO.h"

/* Externs */

extern UART_HandleTypeDef huart2;
extern uint8_t menu_select_index;
extern GPIO_TypeDef current_GPIO;
extern uint8_t chosen_pin;
extern char chosen_port;
extern char* converted_str;

/* Variables */

uint8_t menu_item_index = 1;
uint8_t print_value_flag = 0;
uint8_t print_string_flag = 0;
uint32_t menu_status_output = 0, menu_value_output = 0;

char* welcome_message="Welcome to UART menu. "
					  "Use arrows to navigate.\n";
char* divide_message = "--------------------\n";
char GPIO_pin_str[5] = "";
char* menu_value_str = "";

/*Menu I/O functions */

/* Prints the entire menu */
void Print_menu(){
	Menu_Item_t* buf_menu=Current_menu;
	while((buf_menu->prev) != &NONE){
			buf_menu = buf_menu->prev;
	}
	Print_menu_status();
	while(buf_menu->next!=&NONE){
			print_menu_string(buf_menu->name);
			buf_menu = buf_menu->next;
			menu_item_index++;
	}
	print_menu_string(buf_menu->name);
	HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)divide_message, 21, 100);
	menu_item_index = 1;
}

void print_menu_string(const char* print_string){
	char str[3+Lenstr(print_string)];
	snprintf(str,3+Lenstr(print_string),"%d)%s", menu_item_index, print_string);

	HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)str, Lenstr(str), 100);

	if(menu_select_index == menu_item_index){

		HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)"*", 1, 100);

		if(print_value_flag){
			int_to_str(menu_value_output);

			sprintf(str,"     %s",converted_str);
			HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)str, Lenstr(str), 100);

			print_value_flag = 0;
		}

		if(print_string_flag){
			sprintf(str,"     %s",menu_value_str);
			HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)str, Lenstr(str), 100);

			print_string_flag = 0;

		}
	}
	HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)"\n", 1, 100);
}


/* Prints the status of current MENU_TYPE */
void Print_menu_status(){
	char str[100];
	uint8_t nav_message_lenght=Lenstr(welcome_message)+Lenstr(divide_message);
	uint8_t GPIO_message_lenght=Lenstr(GPIO_pin_str)+Lenstr(divide_message)+14;
	switch (Menu_type){
		case NAVIGATION_MENU_TYPE:
			snprintf(str,nav_message_lenght+2,"%s%s",welcome_message,divide_message);
			HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)str, Lenstr(str), 100);
			break;
#ifdef GPIO_MENU_MODULE_ENABLE
		case GPIO_MENU_TYPE:
			sprintf(GPIO_pin_str,"P%c%d%s",chosen_port,chosen_pin,"\n");
			snprintf(str,GPIO_message_lenght+2,"Chosen pin:%s%s",GPIO_pin_str,divide_message);
			HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)str, Lenstr(str), 100);
			break;
#endif
	}
}

/* Prints a input message to the user */
void Print_input_message(const char* str){
	uint8_t str_len= Lenstr(str)+2;
	char string[str_len];
	snprintf(string,str_len,"%s%c: ",str,'\n');
	HAL_UART_Transmit(&CHOSEN_UART, (uint8_t*)string, str_len-1, 100);
}

/* Prints a value of menu item */
void Print_menu_value(int16_t value){
	print_value_flag=1;
	menu_value_output=value;
}

/* Prints a info string of menu item */
void Print_menu_string(char* string){
	print_string_flag=1;
	menu_value_str=string;
}


uint8_t command_recieve(){
	char input_command[1]={" "};
	HAL_UART_Receive(&CHOSEN_UART, (uint8_t*)input_command, 1, HAL_MAX_DELAY);
	uint8_t command=(int)(input_command[0]);
	return command;
}
/*
void Debug_output(int16_t data){
	int_to_str(data);
	HAL_UART_Transmit(&huart2, (uint8_t*)converted_str, Lenstr(converted_str), 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 100);
}
*/
