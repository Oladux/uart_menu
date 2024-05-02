/*
 * app.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Stepan
 */

#include <menu.h>
/*
 *  Struct templates
 * MENU_COMMAND(id, name, parent, prev, next, func)
*/
/*All options*/

#ifdef GPIO_MENU_MODULE_ENABLE
MENU_COMMAND(MNav1,"GPIO", NONE, NONE,MNav2,GPIO);
#endif

#ifndef GPIO_MENU_MODULE_ENABLE
MENU_COMMAND(MNav1,"NULL", NONE, NONE,MNav2,NULL_func);
#endif
MENU_COMMAND(MNav2,"NULL", NONE, MNav1,MNav3,NULL_func);
MENU_COMMAND(MNav3,"NULL", NONE, MNav2,NONE,NULL_func);

#ifdef GPIO_MENU_MODULE_ENABLE
/*GPIO options*/
MENU_COMMAND(MGPIO1,"Choose GPIO pin",MNav1,NONE,MGPIO2,GPIO_pin_select);
MENU_COMMAND(MGPIO2,"Write GPIO",MNav1,MGPIO1,MGPIO3,GPIO_pin_write);
MENU_COMMAND(MGPIO3,"GPIO pin init",MNav1,MGPIO2,MGPIO4,GPIO_pin_init);
MENU_COMMAND(MGPIO4,"GPIO pin speed",MNav1,MGPIO3,NONE,GPIO_pin_speed);
#endif

/*The entry point to the program*/
void menu_app(){
	create_menu(&MNav1);
	while(1){
		menu_handler(menu_input_type());
	}
}
