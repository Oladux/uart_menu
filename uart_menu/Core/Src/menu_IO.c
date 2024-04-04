/*
 * menu_IO.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Stepan
 */
#include "menu_IO.h"

extern UART_HandleTypeDef huart2;
extern uint8_t menu_select_index;

uint8_t menu_item_index=1;

void print_menu(){
	Menu_Item_t* buf_menu=Current_menu;
		while((buf_menu->prev)!=&NONE){
				buf_menu=buf_menu->prev;
			}

		while(buf_menu->next!=&NONE){
			print_menu_string(buf_menu->name);
			buf_menu=buf_menu->next;
			menu_item_index++;
		}
		print_menu_string(buf_menu->name);
		HAL_UART_Transmit(&huart2, (uint8_t*)"--------------------", 20, 100);
		HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 100);
		menu_item_index=1;
	}

void print_menu_string(const char* string){
	char str[2];
	snprintf(str,3,"%d)",menu_item_index);
	HAL_UART_Transmit(&huart2, (uint8_t*)str, 2, 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)string, lenstr(string), 100);
	if(menu_select_index==menu_item_index){
		HAL_UART_Transmit(&huart2, (uint8_t*)"*", 1, 100);
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 100);
}

void print_input_message(const char* str){
	uint8_t str_len= lenstr(str)+2;
	char string[str_len];
	snprintf(string,str_len,"%s: ",str);
	HAL_UART_Transmit(&huart2, (uint8_t*)string, str_len-1, 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 100);
}
uint8_t command_recieve(){
	char input_command[1]={" "};
	HAL_UART_Receive(&huart2, (uint8_t*)input_command, 1, HAL_MAX_DELAY);
	uint8_t command=(int)(input_command[0]);
	return	command;
}
