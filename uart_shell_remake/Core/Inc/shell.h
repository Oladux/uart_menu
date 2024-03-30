/*
 * shell.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */

#ifndef INC_SHELL_H_
#define INC_SHELL_H_
#include "main.h"



typedef uint8_t (*func_type)(void* p);

typedef enum {
	COMMAND_TYPE,
	OPTION_TYPE
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
#define LEFT 28
#define RIGHT 29
#define UP 30
#define DOWN 31

typedef const struct menu_item{
	uint8_t type;
	struct menu_item *prev;
	struct menu_item *next;
	struct menu_item *parent;
	struct menu_item *child;
	func_type  func;
	const char name[];
} menu_item_type;

typedef const struct menu_func{
	func_type* func;
	uint8_t flag;
} menu_func_type;

#define MENU_FUNC(_id, _func, _flag) \
	menu_func_type _id = {.func=(void*)&_func, .flag=_flag}

extern  menu_item_type* menu_first;
extern  menu_item_type* menu_current;
extern  menu_item_type NONE;

#define MENU_COMMAND(_id, _name, _parent, _prev, _next , _func) \
	extern menu_item_type _parent; 	\
	extern menu_item_type _prev; 	\
	extern menu_item_type _next;    \
	menu_item_type _id = {.type = COMMAND_TYPE, .prev = (void*)&_prev, .next = (void*)&_next, .parent = (void*)&_parent, .func =(void*)&_func, .name = _name}

#define MENU_OPTION(_id, _name, _parent, _child, _prev, _next) \
	extern menu_item_type _parent; \
	extern menu_item_type _prev; 	 \
	extern menu_item_type _next;   \
	extern menu_item_type _child;   \
	menu_item_type _id = {.type = OPTION_TYPE, .prev=(void*)&_prev, .next=(void*)&_next, .func=NULL, .parent=(void*)&_parent, .child=(void*)&_child, .name=_name}

void init_menu(menu_item_type*);
void print_menu();
void print_menu_string();
void reload_menu();
void GPIO_handler();
void test2(uint8_t);

uint8_t menu_action(event_type);
uint8_t flag_handler(uint16_t);
uint8_t index_menu();
uint8_t command_recieve();

event_type input_type();
#endif /* INC_SHELL_H_ */
