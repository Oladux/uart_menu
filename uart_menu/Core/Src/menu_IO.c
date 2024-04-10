/*
 * menu_IO.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Stepan
 */
#include "menu_IO.h"
extern UART_HandleTypeDef huart2;
extern uint8_t menu_select_index;
extern GPIO_TypeDef current_GPIO;
extern uint8_t chosen_pin;
extern char chosen_port;

uint8_t menu_item_index=1;
uint32_t debug_value=0;
char* welcome_message="Welcome to UART menu. "
					  "Use arrows to navigate.\n";
char GPIO_str[5]="0";

void Print_menu(){
	Menu_Item_t* buf_menu=Current_menu;
		while((buf_menu->prev)!=&NONE){
				buf_menu=buf_menu->prev;
			}
		print_status();
		while(buf_menu->next!=&NONE){
			print_menu_string(buf_menu->name);
			buf_menu=buf_menu->next;
			menu_item_index++;
		}
		print_menu_string(buf_menu->name);
		HAL_UART_Transmit(&huart2, (uint8_t*)"--------------------\n", 21, 100);
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

void print_status(){
	switch (Menu_type){
		case NAVIGATION_MENU_TYPE:
			HAL_UART_Transmit(&huart2, (uint8_t*)welcome_message, lenstr(welcome_message), 100);
			HAL_UART_Transmit(&huart2, (uint8_t*)"--------------------\n", 21, 100);
			break;
		case GPIO_MENU_TYPE:
			sprintf(GPIO_str,"P%c%d%c",chosen_port,chosen_pin,'\n');
			HAL_UART_Transmit(&huart2, (uint8_t*)"Chosen pin:", 11, 100);
			HAL_UART_Transmit(&huart2, (uint8_t*)GPIO_str, 4, 100);
			HAL_UART_Transmit(&huart2, (uint8_t*)"--------------------\n", 21, 100);
	}
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
	//debug_output(0,0);
	return	command;
}

void debug_output(uint32_t data){
	char debug_value[2]={0};
	uint32_t buf=0;
	uint8_t digits=1,i=0;

	do{
		++digits;
		buf/= 10;
	}while (buf!= 0);

	do{
		debug_value[(digits-1)-i]=(char)(data%10)+'0';
		data/=10;
		++i;
	}while (i<digits);

	HAL_UART_Transmit(&huart2, (uint8_t*)debug_value, digits, 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 100);

}
