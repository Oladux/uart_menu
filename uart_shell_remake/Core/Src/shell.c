/*
 * shell.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */
#include "shell.h"
typedef const struct menu_item{
	uint8_t type;
	void *prev;
	void *next;
	void *parent;
	void *sub;
	void *func;
	const char name[];
} menu_item;

uint8_t test(){
	return 1;
}
menu_item NONE = {0, (void*)0,(void*)0, (void*)0,(void*)0, 0};
menu_item *first_menu;
menu_item *current_menu=&NONE;

MENU_COMMAND(m1,"TEST",NONE,NONE,NONE,test);
void init_menu(menu_item* menu)
{
	current_menu=menu;
	first_menu=&NONE;
}

