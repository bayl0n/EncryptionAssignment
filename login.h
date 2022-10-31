#ifndef LOGIN_H
#define LOGIN_H

/*******************************************************************************
 * HEADER FILES
*******************************************************************************/
#include "vars.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES
*******************************************************************************/
void menu_login(void);
void help_login(void);

void registerAccount();
void login();
int checkAccount(const char[], const char[]);

#endif
