/*
 * app.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */
#include <menu.h>


/* Structs templates
 * MENU_OPTION(id, name, parent, child, prev, next)
 * MENU_COMMAND(id, name, parent, prev, next, func)
 * */
/*All options*/
MENU_COMMAND(MNav1,"GPIO", NONE, NONE,MNav2,GPIO);
MENU_OPTION(MNav2,"TEST2",NONE,MNav12,MNav1, MNav3);
MENU_OPTION(MNav3,"TEST3",NONE,MNav13,MNav2,NONE);
//MENU_COMMAND(MNav11,"GPIO", MNav1, NONE,NONE,GPIO);
//MENU_OPTION(mo11,"TEST4",mo1,NONE,NONE,NONE);
MENU_COMMAND(MNav12,"TEST5", MNav2, NONE,NONE,NONE);
MENU_OPTION(MNav13,"TEST6",MNav3,NONE,NONE,NONE);

/*GPIO options*/
MENU_COMMAND(MGPIO1,"Choose GPIO pin",NONE,NONE,MGPIO2,GPIO_pin_select);
MENU_OPTION(MGPIO2,"Choose GPIO mode",NONE,NONE,MGPIO1,MGPIO3);
MENU_OPTION(MGPIO3,"GPIO3",NONE,NONE,MGPIO2,NONE);

/*The entry point to the program*/
void menu_app(){
	create_menu(&MNav1);
	while(1){
		menu_handler(menu_input_type());
	}
}
