/*
 * app.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */
#include "shell.h"
uint8_t test1(uint8_t a){
	return a;
}
uint8_t test2(uint8_t a){
	return a;
}
uint8_t test3(uint8_t a){
	return a;
}
/* Structs templates
 * MENU_OPTION(id, name, parent, child, prev, next)
 * MENU_COMMAND(id, name, parent, prev, next, func)
 * */
MENU_OPTION(mo1,"TEST1",NONE,mo11,NONE,mo2);
MENU_OPTION(mo2,"TEST2",NONE,mo12,mo1, mo3);
MENU_OPTION(mo3,"TEST3",NONE,mo13,mo2,NONE);
MENU_OPTION(mo11,"TEST4",mo1,NONE,NONE,NONE);
MENU_OPTION(mo12,"TEST5",mo2,NONE,NONE,NONE);
MENU_OPTION(mo13,"TEST6",mo3,NONE,NONE,NONE);

void shell_app(){
	init_menu(&mo1);
	while(1){
		menu_action(input_type());
	}
}
