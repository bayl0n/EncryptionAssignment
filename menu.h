#ifndef MENU_H
#define MENU_H

/*******************************************************************************
 * LIBRARIES
*******************************************************************************/
#include <stdio.h>

/*******************************************************************************
 * HEADER FILES
*******************************************************************************/
#include "linkedlist.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES
*******************************************************************************/
double readNumber(const char str[]);
char readChar(char[]);
char* readString(const char[]);
char* readStringWithSpaces(const char str[]);
void menu(void);
void help(void);
void addRecord(Node_t** head);
void saveRecord(Node_t* current, const char* fileName);
void readFileMenu(Node_t** head, const char* dbFileName);
void importDoctorRecords(Node_t** head, const char* dbFileName, const char* name);
void importPatientRecords(Node_t** head, const char* dbFileName, const char* name);

/*******************************************************************************
 * HELPER FUNCTIONS
*******************************************************************************/
char* readDOB();
int readDay();
int readMonth();
int readYear();
void intro();
int readPin();
void helpPin();
void helpPinWarning();

#endif
