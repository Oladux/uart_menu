/*
 * app.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */
#include <menu.h>


/* Struct templates
 * MENU_COMMAND(id, name, parent, prev, next, func)
 * */
/*All options*/
MENU_COMMAND(MNav1,"GPIO", NONE, NONE,MNav2,GPIO);
MENU_COMMAND(MNav2,"TEST2", NONE, MNav1,MNav3,NULL_func);
MENU_COMMAND(MNav3,"TEST3", NONE, MNav2,NONE,NULL_func);

/*GPIO options*/
MENU_COMMAND(MGPIO1,"Choose GPIO pin",MNav1,NONE,MGPIO2,GPIO_pin_select);
MENU_COMMAND(MGPIO2,"Write GPIO",MNav1,MGPIO1,MGPIO3,GPIO_pin_write);
MENU_COMMAND(MGPIO3,"GPIO3",MNav1,MGPIO2,NONE,NULL_func);

/*The entry point to the program*/
void menu_app(){
	create_menu(&MNav1);
	while(1){
		menu_handler(menu_input_type());
	}
}
