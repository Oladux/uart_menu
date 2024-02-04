/*
 * shell.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */
#include "shell.h"
extern UART_HandleTypeDef huart2;

typedef const struct menu_item{
	uint8_t type;
	struct menu_item *prev;
	struct menu_item *next;
	struct menu_item *parent;
	struct menu_item *child;
	func_type  func;
	const char name[];
} menu_item;

uint8_t test1(uint8_t a){
	return a;
}
uint8_t test2(uint8_t a){
	return a;
}
uint8_t test3(uint8_t a){
	return a;
}
menu_item NONE = {0};
menu_item *first_menu;
menu_item *current_menu=&NONE;

MENU_COMMAND(m1,"TEST1",NONE,NONE,m2,test1);
MENU_COMMAND(m2,"TEST2",NONE,m1,m3,test2);
MENU_COMMAND(m3,"TEST3",NONE,m2,NONE,test3);
void init_menu(menu_item* menu)
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
	menu_item* buf_menu=&current_menu;

	while((buf_menu->prev)!=&NONE){
		buf_menu=buf_menu->prev;
	}

	while(buf_menu->next!=&NONE){
			HAL_UART_Transmit(&huart2, (uint8_t*)buf_menu->name, 5, 100);
	}

}

