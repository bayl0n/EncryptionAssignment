/*******************************************************************************
 * LIBRARIES
*******************************************************************************/
#include "menu.h"
#include "menu_import.h"
#include "vars.h"
#include "encrypt.h"
#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * MENU
*******************************************************************************/
void menu(void) {
    /* account_t accounts[MAX_USERS]; */
    Node_t* root = malloc(sizeof(Node_t));
    
    /* Stores the current file */
    char fileName[MAX_FILE_SIZE];
    intro();
    help();
    char choice;
    while((choice = readChar("Choice [a/d/e/v/s/c/p/i/x] -> ")) != 'x') {
        switch(choice) {
            case 'a':
                addRecord(&root);
                break;
            case 'd':
                helpPinWarning();
                decryptFile(readString("Enter the file to be decrypted>"), readPin());
                break;
            case 'e':
                helpPin();
                encryptFile(readString("Enter the file to be encrypted>"), readPin());
                break;
            case 'v': 
                displayList(root);
                break;
            case 's':
                saveRecord(root, readString("Enter the file name to be saved>"));
                break;
            case 'c':
                clearList(&root);
                break;
            case 'i':
                menu_import(&root, fileName);
                break;
            case 'p':
                deleteByPosition(&root, readNumber("Enter # of record>"));
                break;
            default: help();
                break;
        }
    }
}

/*******************************************************************************
 * Pin Help Menu
*******************************************************************************/
void helpPin() {
    printf("Input Pin: (MUST BE 4 NUMBERS IN LENGTH)\n");
}

/*******************************************************************************
 * Pin Help Menu
*******************************************************************************/
void helpPinWarning() {
    printf("WARNING: Entering the incorrect pin will your file.\n");
}


/*******************************************************************************
 * Read pin
*******************************************************************************/
int readPin() {
    int pin;

    while(1){
        pin = (int)readNumber("pin>");
        if((pin >= 1111) && (pin <= 9999)){
            return pin;
            break;
        } else {
            printf("Invalid pin. ");
        }
    }
}

/*******************************************************************************
 * readNumber
 * ----------
 * Provides an input prompt that scans a double from the user and returns it.
 * inputs:
 * - str        - the prompt string (READ-ONLY)
 * outputs:
 * - value      - the double value the user enters
*******************************************************************************/
double readNumber(const char str[]){
    double value;
    printf("%s", str);
    scanf("%lf", &value);

    /* Gets rid of input buffer in stdin (i.e. char input) */
    while(getchar() != '\n');
    return value;
}

/*******************************************************************************
 * READ CHARACTER INPUT
*******************************************************************************/
char readChar(char s[]) {
    char c;
    printf("%s", s);
    scanf("%c", &c);
    getchar();
    return c;
}

/*******************************************************************************
 * READ STRING INPUT
*******************************************************************************/
char* readString(const char str[]){
    char* value = malloc(sizeof(char)*MAX_BUFFER_SIZE);
    printf("%s", str);
    scanf("%s", value);

    /* Get rid of input buffer if MAX_BUFFER_SIZE is exceeded */
    while(getchar() != '\n');
    value[strlen(value)] = '\0';
    return value;
}

/*******************************************************************************
 * READ STRING INPUT INCLUDING SPACES AND AFTER
*******************************************************************************/
char* readStringWithSpaces(const char str[]){
    char* value = malloc(sizeof(char)*MAX_BUFFER_SIZE);
    printf("%s", str);
    scanf(" %[^\n]s", value);

    /* Get rid of input buffer if MAX_BUFFER_SIZE is exceeded */
    while(getchar() != '\n');
    value[strlen(value)] = '\0';
    return value;
}

/*******************************************************************************
 * Add record to database
*******************************************************************************/
void addRecord(Node_t** head) {
    char newRecord[MAX_BUFFER_SIZE];

    strcpy(newRecord, readStringWithSpaces("Doctor name>"));
    strcat(newRecord, ",");
    strcat(newRecord, readStringWithSpaces("Patient name>"));
    strcat(newRecord, ",");
    strcat(newRecord, readDOB());
    strcat(newRecord, ",");
    strcat(newRecord, readStringWithSpaces("Phone number>"));
    strcat(newRecord, ",");
    strcat(newRecord, readStringWithSpaces("Email>"));
    strcat(newRecord, ",");
    strcat(newRecord, readStringWithSpaces("Reason for admission>"));

    add(head, newRecord);
}

/*******************************************************************************
 * Read date of birth
*******************************************************************************/
char* readDOB() {
    char* date = malloc(sizeof(char)*MAX_DATE_SIZE);
    printf("Enter date of birth:\n");
    sprintf(date, "%02d/%02d/%d", readDay(), readMonth(), readYear());
    return date;
}

/*******************************************************************************
 * Read day
*******************************************************************************/
int readDay() {
    int day;

    while(1){
        day = (int)readNumber("day>");
        if((day >= MIN_DAY_SIZE) && (day <= MAX_DAY_SIZE)){
            return day;
            break;
        } else {
            printf("Invalid day. ");
        }
    }
}

/*******************************************************************************
 * Read Month
*******************************************************************************/
int readMonth() {
    int month;

    while(1){
        month = (int)readNumber("month>");
        if((month >= MIN_MONTH_SIZE) && (month <= MAX_MONTH_SIZE)){
            return month;
            break;
        } else {
            printf("Invalid month. ");
        }
    }
}

/*******************************************************************************
 * Read Year
*******************************************************************************/
int readYear() {
    int year;

    while(1){
        year = (int)readNumber("year>");
        if((year >= MIN_YEAR_SIZE) && (year <= MAX_YEAR_SIZE)){
            return year;
            break;
        } else {
            printf("Invalid year. ");
        }
    }
}

/*******************************************************************************
 * Save record to database
*******************************************************************************/
void saveRecord(Node_t* current, const char* fileName) {
    if(current == NULL) {
        printf("\n\nNo patient records added to list!\n\n");
        return;
    }

    FILE* database = fopen(fileName, "w");

    if(database == NULL) {
        printf("\n\nError: Could not find file. \n\n");
        return;
    }

    while(current->next != NULL) {
        fputs(current->text, database);
        if(current->next != NULL) {
            fputs("\n", database);
        }
        current = current->next;
    }

    fclose(database);
}

/*******************************************************************************
 * STORES CSV FILE TEXT ONTO A VARIABLE
 * 
 *
 * 
 * Inputs:
 * - 
 * Outputs: 
 * -
*******************************************************************************/
void readFileMenu(Node_t** head, const char* dbFileName){
    /* Open the database with read privileges */
    FILE* database = fopen(dbFileName, "r");

    /* Handle case if database can't be read */
    if(database == NULL){
        printf("Read error\n");
    } else {
        /* Buffer to store each line */
        char buffer[MAX_BUFFER_SIZE];
        /* Token represents each string separated by strtok */
        char* token;

        /* Loop until no more lines can be read by fgets */
        while(fgets(buffer, MAX_BUFFER_SIZE, database)){
            /* Count to keep track of employee details */
            int detailCount = 0;

            /* Delimit buffer by "," and set token to first string token */
            token = strtok(buffer, ",");

            char* newString = malloc(sizeof(char) * MAX_BUFFER_SIZE);
            while(token){
                /* Manage token cases based on detailCount */
                switch(detailCount) {
                    /* username */
                    case 0:
                        strcpy(newString, token);
                        break;
                    /* password */
                    case 1:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 2:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 3:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 4:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 5:
                        strcat(newString, ",");
                        strcat(newString, token);
                        newString[strlen(newString) - 1] = '\0';
                        break;
                    default:
                        break;
                }
                /* Iterate detailCount to look at the next case */
                detailCount++;
                token = strtok(NULL, ",");
                
            }
            add(head, newString);
        }
        printf("Records have been added successfully!\n");
        fclose(database);
    }
}

/*******************************************************************************
 * importDoctorRecords
 * -------------------
 * 
*******************************************************************************/
void importDoctorRecords(Node_t** head, const char* dbFileName, const char* name){
    /* Open the database with read privileges */
    FILE* database = fopen(dbFileName, "r");

    /* Handle case if database can't be read */
    if(database == NULL){
        printf("Read error\n");
    } else {
        /* Buffer to store each line */
        char buffer[MAX_BUFFER_SIZE];
        /* Variable to store current name*/
        char currentName[MAX_NAME_SIZE];
        /* Token represents each string separated by strtok */
        char* token;

        /* Loop until no more lines can be read by fgets */
        while(fgets(buffer, MAX_BUFFER_SIZE, database)){
            /* Count to keep track of employee details */
            int detailCount = 0;

            /* Delimit buffer by "," and set token to first string token */
            token = strtok(buffer, ",");

            char* newString = malloc(sizeof(char) * MAX_BUFFER_SIZE);
            while(token){
                /* Manage token cases based on detailCount */
                switch(detailCount) {
                    /* username */
                    case 0:
                        strcpy(newString, token);
                        strcpy(currentName, token);
                        break;
                    /* password */
                    case 1:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 2:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 3:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 4:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 5:
                        strcat(newString, ",");
                        strcat(newString, token);
                        newString[strlen(newString) - 1] = '\0';
                        break;
                    default:
                        break;
                }
                /* Iterate detailCount to look at the next case */
                detailCount++;
                token = strtok(NULL, ",");
            }
            /* If the doctor name is the one that is being searched for */
            if(!strcmp(currentName, name)) {
                printf("%s matches with %s\n", currentName, name);
                add(head, newString);
            }
        }
        if(head != NULL) {
            printf("Records of doctor %s have been added successfully!\n", name);
        } else {
            printf("No records for doctor %s found.\n", name);
        }
        fclose(database);
    }
}

/*******************************************************************************
 * importPatientRecords
 * --------------------
 * 
 *
*******************************************************************************/
void importPatientRecords(Node_t** head, const char* dbFileName, const char* name){
    /* Open the database with read privileges */
    FILE* database = fopen(dbFileName, "r");

    /* Handle case if database can't be read */
    if(database == NULL){
        printf("Read error\n");
    } else {
        /* Buffer to store each line */
        char buffer[MAX_BUFFER_SIZE];
        /* Variable to store current name*/
        char currentName[MAX_NAME_SIZE];
        /* Token represents each string separated by strtok */
        char* token;

        /* Loop until no more lines can be read by fgets */
        while(fgets(buffer, MAX_BUFFER_SIZE, database)){
            /* Count to keep track of employee details */
            int detailCount = 0;

            /* Delimit buffer by "," and set token to first string token */
            token = strtok(buffer, ",");

            char* newString = malloc(sizeof(char) * MAX_BUFFER_SIZE);
            while(token){
                /* Manage token cases based on detailCount */
                switch(detailCount) {
                    case 0:
                        strcpy(newString, token);
                        break;
                    case 1:
                        /* Store the patient name in currentName */ 
                        strcpy(currentName, token);

                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 2:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 3:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 4:
                        strcat(newString, ",");
                        strcat(newString, token);
                        break;
                    case 5:
                        strcat(newString, ",");
                        strcat(newString, token);
                        newString[strlen(newString) - 1] = '\0';
                        break;
                    default:
                        break;
                }
                /* Iterate detailCount to look at the next case */
                detailCount++;
                token = strtok(NULL, ",");
            }
            /* If the doctor name is the one that is being searched for */
            if(!strcmp(currentName, name)) {
                printf("%s matches with %s\n", currentName, name);
                add(head, newString);
            }
        }
        if(head != NULL) {
            printf("Records of doctor %s have been added successfully!\n", name);
        } else {
            printf("No records for doctor %s found.\n", name);
        }
        fclose(database);
    }
}

/*******************************************************************************
 * DISPLAY OPTIONS MENU
*******************************************************************************/
void help() {
    printf("Menu options: \n");
    printf("a = Add a record\n");
    printf("d = Decrypt a file\n");
    printf("e = Encrypt a file\n");
    printf("v = View records\n");
    printf("s = Save records\n");
    printf("c = Clear records\n");
    printf("p = Delete by position\n");
    printf("i = Import...\n");
    printf("x = exit\n");
}

/*******************************************************************************
 * INTRO TO PROGRAM
*******************************************************************************/
void intro() {
    printf("Welcome to the Encrypted Hospital Database System!\n");
    printf("--------------------------------------------------\n");
    printf("To get started, select one of the menu options below.\n");
    printf("Press any other key to get the help menu.\n\n");
}
