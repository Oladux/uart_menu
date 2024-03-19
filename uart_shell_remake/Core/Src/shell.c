/*
 * shell.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */
#include "shell.h"
extern UART_HandleTypeDef huart2;

uint8_t menu_select_index=1;
char input_command[1]={" "};

menu_item_type NONE = {0};
menu_item_type* first_menu;
menu_item_type* current_menu=&NONE;

event_type input_type(){
	event_type event=0;
	HAL_UART_Receive(&huart2, (uint8_t*)input_command, 1, HAL_MAX_DELAY);

	int operation=(int)(input_command[0]);

	switch (operation) {
		case LEFT:
			event = ESCAPE_EVENT;
			break;
		case UP:
			event = PREV_EVENT;
			break;
		case RIGHT:
			event = ENTER_EVENT;
			break;
		case DOWN:
			event = NEXT_EVENT;
			break;
		default:
			event = NONE_EVENT;
			break;
	}
	return event;
}
void init_menu(menu_item_type* menu)
{
	current_menu=menu;
	first_menu=&NONE;
	print_menu();
}

uint8_t menu_action(event_type ev_type){
	if((current_menu==NULL)||(current_menu == &NONE)) return 0;
	else{
		switch(ev_type){
			case ENTER_EVENT:
				switch (current_menu->type) {
					case (COMMAND_TYPE):
							menu_select_index=1;
							return current_menu->func(0);
					case (OPTION_TYPE):
							if(((current_menu->child)!=&NONE)){
								current_menu=current_menu->child;
								first_menu=&NONE;
								menu_select_index=1;
								print_menu();
								break;
								}
							else{
								print_menu();
								break;
							}
					break;
			}
				break;
			case ESCAPE_EVENT:
				if(current_menu->parent==&NONE) return 0;
				else{
					menu_select_index=index_menu();
					current_menu=current_menu->parent;
					reload_menu();
					print_menu();
				}
				break;
			case NEXT_EVENT:
				if (current_menu->next==&NONE) return 0;
				else{
					menu_select_index++;
					current_menu=current_menu->next;
					print_menu();
				}
				break;
			case PREV_EVENT:
				if (current_menu->prev==&NONE) return 0;
				else{
					menu_select_index--;
					current_menu=current_menu->prev;
					print_menu();
				}
				break;
			case NONE_EVENT:
			default:
				break;
		}
				return 1;
	}
}
uint8_t menu_item_index=1;
void print_menu(){
	menu_item_type* buf_menu=current_menu;

	while((buf_menu->prev)!=&NONE){
		buf_menu=buf_menu->prev;
	}

	while(buf_menu->next!=&NONE){
			print_menu_string(buf_menu->name);
			buf_menu=buf_menu->next;
			menu_item_index++;
	}
	print_menu_string(buf_menu->name);
	HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 100);
	menu_item_index=1;
}

uint8_t index_menu(){
	menu_item_type* buf_menu=current_menu;
	uint8_t index=1;
	while(buf_menu->prev!=&NONE){
		buf_menu=buf_menu->prev;
		index++;
	}
	return index;
}

void reload_menu(){
	while(current_menu->prev!=&NONE){
		current_menu=current_menu->prev;
	}
}
void print_menu_string(char* string){
	char str[2];
	snprintf(str,3,"%d)",menu_item_index);
	HAL_UART_Transmit(&huart2, (uint8_t*)str, 2, 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)string, sizeof(string)+1, 100);
	if(menu_select_index==menu_item_index){
		HAL_UART_Transmit(&huart2, (uint8_t*)"*", 1, 100);
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 100);
}










