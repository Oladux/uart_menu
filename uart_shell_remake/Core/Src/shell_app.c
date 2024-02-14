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
MENU_COMMAND(m1,"TEST1",NONE,NONE,m2,test1);
MENU_COMMAND(m2,"TEST2",NONE,m1,m3,test2);
MENU_COMMAND(m3,"TEST3",NONE,m2,NONE,test3);
void shell_app(){
	init_menu(&m1);
	while(1){
		menu_action(input_type());
	}
	print_menu();
}
