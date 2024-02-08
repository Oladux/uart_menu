/*
 * shell.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */
#include "shell.h"
extern UART_HandleTypeDef huart2;

uint8_t menu_index=1;
char input_command[1]={" "};

menu_item_type NONE = {0};
menu_item_type* first_menu;
menu_item_type* current_menu=&NONE;

event_type input_type(){
	event_type event=0;

	HAL_UART_Receive(&huart2, (uint8_t*)input_command, 1, HAL_MAX_DELAY);

	int operation=(int)(input_command[0]);
	HAL_UART_Transmit(&huart2, (uint8_t*)operation, 3, 100);

	switch (operation) {
		case LEFT:
			event = ESCAPE_EVENT;
			break;
		case UP:
			event = PREV_EVENT;
			break;
		case RIGHT:
			event = NEXT_EVENT;
			break;
		case DOWN:
			event = ENTER_EVENT;
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
}

uint8_t menu_action(event_type ev_type){
	if((current_menu==NULL)||(current_menu == &NONE)) return 0;
	else{
		switch(ev_type){
			case ENTER_EVENT:
				switch (current_menu->type) {
					case (COMMAND_TYPE):
							return current_menu->func(0);

					case (CHILD_MENU_TYPE):
							current_menu=current_menu->child;
							first_menu=&NONE;
							break;
			}
			case ESCAPE_EVENT:
				if(current_menu->parent==&NONE) return 0;
				else{
					current_menu=current_menu->parent;
				}
				break;
			case NEXT_EVENT:
				if (current_menu->next==&NONE) return 0;
				else{
					current_menu=current_menu->next;
				}
				break;
			case PREV_EVENT:
				if (current_menu->prev==&NONE) return 0;
				else{
					current_menu=current_menu->prev;
				}
				break;
			case NONE_EVENT:
			default:
				break;
		}
				return 1;
	}

}
void print_menu(){
	menu_item_type* buf_menu=current_menu;

	while((buf_menu->prev)!=&NONE){
		buf_menu=buf_menu->prev;
	}

	while(buf_menu->next!=&NONE){
			print_menu_string(buf_menu->name);
			buf_menu=buf_menu->next;
			menu_index++;
	}
	print_menu_string(buf_menu->name);
	menu_index=1;
}

void print_menu_string(char* string){
	char str[2];
	snprintf(str,3,"%d)",menu_index);
	HAL_UART_Transmit(&huart2, (uint8_t*)str, 2, 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)string, sizeof(string)+1, 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 100);
}















