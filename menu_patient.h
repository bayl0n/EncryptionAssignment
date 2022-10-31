#ifndef MENU_PATIENT_H
#define MENU_PATIENT_H

/*******************************************************************************
 * HEADER FILES
*******************************************************************************/
#include <stdio.h>

/*******************************************************************************
 * FUNCTION PROTOTYPES
*******************************************************************************/
char readChar(char[]);
char* readString(const char[]);
void menu_patient(void);
void help_patient(void);
void encryptFile();
void decryptFile();
void printSinglePatient();
void searchPatient(const char dbFileName[], const char patientName[]);

#endif
