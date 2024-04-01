/*
 * shell.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_
#include "main.h"
#include  "math.h"

/*The type of functions called from the menu */
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

enum ASCII_TO_INT{
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	H = 72,

	LEFT = 28,
	RIGHT = 29,
	UP = 30,
	DOWN = 31
};

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

extern  menu_item_type* menu_first;
extern  menu_item_type* menu_current;
extern  menu_item_type NONE;

/* A macro for creating a menu item containing a function */
#define MENU_COMMAND(_id, _name, _parent, _prev, _next , _func) \
	extern menu_item_type _parent; 	\
	extern menu_item_type _prev; 	\
	extern menu_item_type _next;    \
	menu_item_type _id = {.type = COMMAND_TYPE, .prev = (void*)&_prev, .next = (void*)&_next, .parent = (void*)&_parent, .func =(void*)&_func, .name = _name}

/* A macro for creating a menu item that does not contain a function*/
#define MENU_OPTION(_id, _name, _parent, _child, _prev, _next) \
	extern menu_item_type _parent; \
	extern menu_item_type _prev; 	 \
	extern menu_item_type _next;   \
	extern menu_item_type _child;   \
	menu_item_type _id = {.type = OPTION_TYPE, .prev=(void*)&_prev, .next=(void*)&_next, .func=NULL, .parent=(void*)&_parent, .child=(void*)&_child, .name=_name}

//Functions prototypes
void init_menu(menu_item_type*);
void print_menu();
void print_menu_string();
void reload_menu();


uint8_t menu_handler(event_type);
uint8_t flag_handler(uint16_t);
uint8_t index_menu();
uint8_t command_recieve();
uint8_t strlen(const char*);

event_type input_type();

void GPIO();
#endif /* INC_MENU_H_ */