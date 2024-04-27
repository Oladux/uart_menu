/*
 * shell.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_
#include "main.h"
#include "menu_conf.h"


/*The type of functions called from the menu */
typedef uint8_t (*func_type)(void* p);


typedef enum{
	NAVIGATION_MENU_TYPE,
	GPIO_MENU_TYPE
} Menu_Type_t;

typedef enum{
	NONE_MENU_EVENT,
	ENTER_MENU_EVENT,
	ESCAPE_MENU_EVENT,
	NEXT_MENU_EVENT,
	PREV_MENU_EVENT,
} Event_Type_t;

enum ASCII_TO_INT{
	A = 17,
	B = 18,
	C = 19,
	D = 20,
	E = 21,
	H = 54,

	LEFT = 28,
	RIGHT = 29,
	UP = 30,
	DOWN = 31
};

typedef const struct menu_item{
	struct menu_item *prev;
	struct menu_item *next;
	struct menu_item *parent;
	struct menu_item *child;
	func_type  func;
	const char name[];
} Menu_Item_t;


extern  Menu_Item_t* Menu_first;
extern  Menu_Item_t* Current_menu;
extern  Menu_Item_t  NONE;
extern  Menu_Type_t  Menu_type;
/* A macro for creating a menu item containing a function */
#define MENU_COMMAND(_id, _name, _parent, _prev, _next , _func) \
	extern Menu_Item_t _parent;  \
	extern Menu_Item_t _prev; 	 \
	extern Menu_Item_t _next;    \
	Menu_Item_t _id = {.prev = (void*)&_prev, .next = (void*)&_next, .parent = (void*)&_parent, .func =(void*)&_func, .name = _name}

//Functions prototypes
void NULL_func();

void create_menu(Menu_Item_t*);

void print_menu_string();
void Print_input_message(const char*);

void Debug_output(int16_t);

void Print_menu();
void Reload_menu();
void Back_menu();

void int_to_str(int16_t);


void GPIO();
void GPIO_pin_select();
void GPIO_pin_write();

uint8_t command_recieve();

uint8_t Index_menu();
uint8_t Lenstr(const char*);

uint8_t menu_handler(Event_Type_t);
uint8_t flag_handler(uint16_t);

Event_Type_t menu_input_type();
#endif /* INC_MENU_H_ */
