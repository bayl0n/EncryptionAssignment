/*******************************************************************************
 * LIBRARIES
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * HEADER FILES
*******************************************************************************/
#include "login.h"
#include "vars.h"
#include "menu.h"
#include "menu_patient.h"
#include "encrypt.h"

/*******************************************************************************
 * LOGIN MENU
*******************************************************************************/
void menu_login(void) {
    help_login();
    char choice;
    while((choice = readChar("Choice [l/r/x] -> ")) != 'x') {
        switch(choice) {
            case 'l': login();
                break;
            case 'r': registerAccount();
                break;
            case 'x': exit(0);
                break;
            default : help_login();
                break;
        }
    }
}

/*******************************************************************************
 * DISPLAY LOGIN OPTIONS MENU
*******************************************************************************/
void help_login() {
    printf("Menu options: \n");
    printf("l = Login\n");
    printf("r = Register\n");
    printf("x = exit\n");
}

/*******************************************************************************
 * REGISTER NEW ACCOUNT
 *
 * This function registers a new account to the database
 * inputs:
 * - N/A
 * outputs:
 * - N/A
*******************************************************************************/
void registerAccount(){
    /* Substitute the file_path string
     * with full path of CSV file
     */
    FILE* database = fopen("auth.csv", "a+");
  
    char username[MAX_USERNAME_SIZE];
    char password[MAX_PASSWORD_SIZE];
  
    if(database == NULL) {
        /* Error in file opening */
        printf("Can't open file\n");
    } else {
        /* Asking user input for the new record to be added */
        printf("Enter Account Username\n");
        scanf("%s", username);
        printf("Enter Account Password\n");
        scanf("%s", password);
    
        /* Saving data in file */
        fprintf(database, "%s,%s\n", username, password);
    
        printf("New Account added!\n");
    }
    fclose(database);
}

/*******************************************************************************
 * LOGIN TO EXISTING ACCOUNT
 *
 * This function allows user to login to the system using an existing account
 * inputs:
 * - char[] username
 * - char[] password
 * outputs:
 * 0 - Unsuccessful login
 * 1 - Successful Doctor login
 * 2 - Successful Patient login
*******************************************************************************/
void login(){
    char username[MAX_USERNAME_SIZE];
    char password[MAX_PASSWORD_SIZE];
    
    /* Open csv file */
    FILE* database = fopen("auth.csv", "r");
    
    /* Handle case if database can't be read */
    if(database == NULL) {
        printf("Can't open file\n");
    } else {
        /* Reads user input: username */
        strncpy(username, readString("Username: "), MAX_USERNAME_SIZE - 1);
        username[strlen(username)] = '\0';

        /* Reads user input: password */
        strncpy(password, readString("Password: "), MAX_PASSWORD_SIZE - 1);
        password[strlen(password)] = '\0';

        /* Check if user inputs are valid */
        if(checkAccount(username, password) == 0){
            printf("Login Unsuccessful, Please try again\n");
        }

        /* Check if user is a Doctor */
        if(checkAccount(username, password) == 1) {
            printf("Login Successful, Welcome Dr. %s!\n", username);
            menu();
        }

        /* Check if user is a Patient */
        if(checkAccount(username, password) == 2) {
            printf("Login Successful, Welcome patient %s!\n", username);
            menu_patient();
        }
    }
    fclose(database);
}

/*******************************************************************************
 * LOGIN HELPER FUNCTION
 *
 * This function is called to check the user's username, password & account type
 * inputs:
 * - char[] username
 * - char[] password
 * outputs:
 * 0 - Unsuccessful login
 * 1 - Successful Doctor login
 * 2 - Successful Patient login
*******************************************************************************/
int checkAccount(const char usernameInput[], const char passwordInput[]){
    char username[MAX_USERNAME_SIZE];
    char password[MAX_PASSWORD_SIZE];
    char accType[10];

    /* Open csv file */
    FILE* database = fopen("auth.csv", "r");

    /* Handle case if database can't be read */
    if(database == NULL){
        printf("Read error\n");
    } else {
        /* Buffer to store each line */
        char buffer[MAX_BUFFER_SIZE];
        /* Token represents each string separated by strtok */
        char* token;

        /* Loop until no more lines can be read by fgets */
        while(fgets(buffer, MAX_BUFFER_SIZE, database)) {
            /* Delimit buffer by "\t" and set token to first string token */
            token = strtok(buffer,",");

            /* Store account details into account info */
            strcpy(username, token);
            strcpy(password, strtok(NULL, " ,"));
            strcpy(accType, strtok(NULL, " ,"));

            /* Check user inputs for validation */
            /* Check user account type */
            if(strcmp(username, usernameInput) == 0 && strcmp(password, passwordInput) == 0){
                if(strcmp("doctor\n", accType) == 0){
                    return 1;
                } else {
                    return 2;
                }
            }
            token = strtok(NULL, " ,");
        }
    }
    return 0;
    fclose(database);
}
