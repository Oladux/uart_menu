/*
 * shell.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_
#include "main.h"
#include "math.h"


/*The type of functions called from the menu */
typedef uint8_t (*func_type)(void* p);

typedef enum {
	COMMAND_TYPE,
	OPTION_TYPE
} Item_Type_t;

typedef enum{
	NAVIGATION_MENU_STATE,
	INPUT_MENU_STATE
} Menu_State_t;

typedef enum{
	NAVIGATION_MENU_TYPE,
	GPIO_MENU_TYPE
} Menu_Type_t;

typedef enum{
	NONE_EVENT,
	ENTER_EVENT,
	ESCAPE_EVENT,
	NEXT_EVENT,
	PREV_EVENT,
//	INC_EVENT,
//	DEC_EVENT
} Event_Type_t;

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
} Menu_Item_t;


extern  Menu_Item_t* Menu_first;
extern  Menu_Item_t* Current_menu;
extern  Menu_Item_t  NONE;
extern  Menu_State_t    Menu_state;

/* A macro for creating a menu item containing a function */
#define MENU_COMMAND(_id, _name, _parent, _prev, _next , _func) \
	extern Menu_Item_t _parent; 	\
	extern Menu_Item_t _prev; 	\
	extern Menu_Item_t _next;    \
	Menu_Item_t _id = {.type = COMMAND_TYPE, .prev = (void*)&_prev, .next = (void*)&_next, .parent = (void*)&_parent, .func =(void*)&_func, .name = _name}

/* A macro for creating a menu item that does not contain a function*/
#define MENU_OPTION(_id, _name, _parent, _child, _prev, _next) \
	extern Menu_Item_t _parent; \
	extern Menu_Item_t _prev; 	 \
	extern Menu_Item_t _next;   \
	extern Menu_Item_t _child;   \
	Menu_Item_t _id = {.type = OPTION_TYPE, .prev=(void*)&_prev, .next=(void*)&_next, .func=NULL, .parent=(void*)&_parent, .child=(void*)&_child, .name=_name}

//Functions prototypes
void create_menu(Menu_Item_t*);
void print_menu();
void print_menu_string();
void print_input_message(const char*);
void reload_menu();


uint8_t menu_handler(Event_Type_t);
uint8_t flag_handler(uint16_t);
uint8_t index_menu();
uint8_t command_recieve();
uint8_t lenstr(const char*);

Event_Type_t menu_input_type();

void GPIO();
void GPIO_pin_select();
#endif /* INC_MENU_H_ */
