/*
 * shell.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */

#ifndef INC_SHELL_H_
#define INC_SHELL_H_
#include "main.h"

typedef enum {
	COMMAND_TYPE,
	SUBMENU_TYPE
} item_type;


#define MENU_COMMAND(id, name, parent, prev, next , func) \
	extern menu_item parent; 	\
	extern menu_item prev; 	 \
	extern menu_item next;   \
	menu_item id={(uint8_t)COMMAND_TYPE, (void*)&prev, (void*)&next, (void*)&parent, (void*)func, {name}}

#define SUB_MENU(id, name, parent, prev, next , sub) \
	extern menu_item parent; \
	extern menu_item prev; 	 \
	extern menu_item next;   \
	extern menu_item sub;   \
	menu_item id = {.type = SUBMENU_TYPE, .prev=&prev, .next=&next, .func=NULL, .parent=parent, .sub=&sub, .name=name}

#endif /* INC_SHELL_H_ */
