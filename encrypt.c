/*******************************************************************************
 * HEADER FILES
*******************************************************************************/
#include "encrypt.h"

/*******************************************************************************
 * DECRYPT 
 *
 * This function decrypts the file assigned to the current logged in doctor
 * inputs:
 * - filename
 * outputs:
 * - 1: When decryption fails
 * - 0: When decryption succeeds
*******************************************************************************/
char* decrypt(int key, char* arr, int size){
    char* text = (char*) malloc(sizeof(char) * size);

    int i;
    for(i = 0; i < size; i++) {
        arr[i] -= key;
    }
    strcpy(text, arr);
    return text;
}

/*******************************************************************************
 * ENCRYPT
 *
 * This function encrypts the file assigned to the current logged in doctor
 * inputs:
 * - filename
 * outputs:
 * - 1: When encryption fails
 * - 0: When encryption succeeds
*******************************************************************************/
char* encrypt(int key, char* arr, int size){
    char* cipher = (char*) malloc(sizeof(char) * size);

    int i;
    for(i = 0; i < size; i++) {
        arr[i] += key;
    }
    strcpy(cipher, arr);
    return cipher;
}

/*******************************************************************************
 * ENCRYPT FILE
 *
 * This function encrypts the file assigned to the current logged in doctor
 * inputs:
 * - filename
 * outputs:
 * - 1: When encryption fails
 * - 0: When encryption succeeds
*******************************************************************************/
void encryptFile(const char* fileName, int key) {
    FILE* database = fopen(fileName, "r");
    if(database == NULL) {
        printf("Couldn't not find requested file.\n");
        return;
    }
    
    FILE* databaseEncr = fopen("encrypted.csv", "w");

    int byte;

    while((byte = fgetc(database)) != EOF) {
        fputc(byte+key, databaseEncr);
    }

    fclose(database);
    fclose(databaseEncr);

    /* Make fileName the encrypted file */
    remove(fileName);
    rename("encrypted.csv", fileName);
}

/*******************************************************************************
 * DECRYPT FILE
 *
 * This function encrypts the file assigned to the current logged in doctor
 * inputs:
 * - filename
 * outputs:
 * - 1: When encryption fails
 * - 0: When encryption succeeds
*******************************************************************************/
void decryptFile(const char* fileName, int key) {
    FILE* database = fopen(fileName, "r");
    if(database == NULL) {
        printf("Couldn't not find requested file.\n");
        return;
    }
    FILE* databaseEncr = fopen("decrypted.csv", "w");

    int byte;

    while((byte = fgetc(database)) != EOF) {
        fputc(byte-key, databaseEncr);
    }
    
    fclose(database);
    fclose(databaseEncr);

    /* Make fileName the decrypted file */
    remove(fileName);
    rename("decrypted.csv", fileName);
}
