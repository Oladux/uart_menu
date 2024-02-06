/*
 * shell.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */

#ifndef INC_SHELL_H_
#define INC_SHELL_H_
#include "main.h"
#include <stdio.h>

typedef uint8_t (*func_type)(void* p);



typedef enum {
	COMMAND_TYPE,
	CHILD_MENU_TYPE
} item_type;

typedef enum{
	NONE_EVENT,
	ENTER_EVENT,
	ESCAPE_EVENT,
	NEXT_EVENT,
	PREV_EVENT,
//	INC_EVENT,
//	DEC_EVENT
} event_type;

typedef const struct menu_item{
	uint8_t type;
	struct menu_item *prev;
	struct menu_item *next;
	struct menu_item *parent;
	struct menu_item *child;
	func_type  func;
	const char name[];
} menu_item_type;

extern  menu_item_type* menu_first;
extern  menu_item_type* menu_current;
extern  menu_item_type NONE;

#define MENU_COMMAND(_id, _name, _parent, _prev, _next , _func) \
	extern menu_item_type _parent; 	\
	extern menu_item_type _prev; 	 \
	extern menu_item_type _next;   \
	menu_item_type _id = {.type = COMMAND_TYPE, .prev = (void*)&_prev, .next = (void*)&_next, .parent = (void*)&_parent, .func =(void*) _func, .name = _name}

#define SUB_MENU(id, name, parent, prev, next , sub) \
	extern menu_item parent; \
	extern menu_item prev; 	 \
	extern menu_item next;   \
	extern menu_item sub;   \
	menu_item id = {.type = SUBMENU_TYPE, .prev=&prev, .next=&next, .func=NULL, .parent=parent, .sub=&sub, .name=name}

void init_menu(menu_item_type*);
uint8_t menu_action(event_type);
void print_menu();
void print_menu_string();

#endif /* INC_SHELL_H_ */
