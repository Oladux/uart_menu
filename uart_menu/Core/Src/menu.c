/*
 * shell.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */
#include <menu.h>

extern Menu_Item_t MNav1;
extern Menu_Item_t MGPIO1;

// Variables
char input_command[1]={" "};

Menu_Item_t NONE = {0};
Menu_Item_t* first_menu;
Menu_Item_t* Current_menu = &NONE;

uint8_t menu_select_index = 1;
Menu_Type_t Menu_type = NAVIGATION_MENU_TYPE;
// Menu functions
void create_menu(Menu_Item_t* menu)
{
	Current_menu=menu;
	first_menu=&NONE;
	Print_menu();
}
/*Receive type of event and handle it */
uint8_t menu_handler(Event_Type_t ev_type){
	if((Current_menu==NULL)||(Current_menu == &NONE)) return 0;
	else{
		switch(ev_type){
			case ENTER_EVENT:
				switch (Current_menu->type) {
					case (COMMAND_TYPE):
							menu_select_index=1;
							return Current_menu->func(0);
					case (OPTION_TYPE):
							if(((Current_menu->child)!=&NONE)){
								Current_menu=Current_menu->child;
								first_menu=&NONE;
								menu_select_index=1;
								Print_menu();
								break;
								}
							else{
								Print_menu();
								break;
							}
					break;
			}
				break;
			case ESCAPE_EVENT:
				if(Current_menu->parent==&NONE) return 0;
				else{
					menu_select_index=1;
					Current_menu=Current_menu->parent;
					reload_menu();
					Print_menu();
				}
				break;
			case NEXT_EVENT:
				if (Current_menu->next==&NONE) return 0;
				else{
					menu_select_index++;
					Current_menu=Current_menu->next;
					Print_menu();
				}
				break;
			case PREV_EVENT:
				if (Current_menu->prev==&NONE) return 0;
				else{
					menu_select_index--;
					Current_menu=Current_menu->prev;
					Print_menu();
				}
				break;
			case NONE_EVENT:
			default:
				break;
		}
				return 1;
	}
}
Event_Type_t menu_input_type(){
	Event_Type_t event=0;
	uint8_t command=command_recieve();
	switch (command) {
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
//Menu print functions

//Common use functions
/* Returns the index of the selected menu item */
uint8_t index_menu(){
	Menu_Item_t* buf_menu=Current_menu;
	uint8_t index=1;
	while(buf_menu->prev!=&NONE){
		buf_menu=buf_menu->prev;
		index++;
	}
	return index;
}
/* Reset the selected menu item index to the first one */
void reload_menu(){
	while(Current_menu->prev!=&NONE){
		Current_menu=Current_menu->prev;
	}
}

uint8_t lenstr(const char* str)
{
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}





