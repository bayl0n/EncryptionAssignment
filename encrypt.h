#ifndef ENCRYPT_H
#define ENCRYPT_H

/*******************************************************************************
 * LIBRARIES
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*******************************************************************************
 * FUNCTION PROTOTYPES
*******************************************************************************/
char* decrypt(int, char*, int);
char* encrypt(int, char*, int);
void encryptFile(const char* fileName, int key);
void decryptFile(const char* fileName, int key);

#endif
