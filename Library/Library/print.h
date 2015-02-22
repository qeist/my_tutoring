#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include <stdlib.h>

void print_init_menu(void);
void print_user_menu(void);
void print_admin_menu(void);
void print_login_error(void);
void print_quit(void);
void print_menu_error(void);

void print_user_submenu(void);
void print_admin_submenu(void);
#endif