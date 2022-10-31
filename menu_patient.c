/*******************************************************************************
 * LIBRARIES
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * HEADER FILES
*******************************************************************************/
#include "menu.h"
#include "menu_patient.h"
#include "vars.h"
#include "encrypt.h"

/*******************************************************************************
 * MENU
*******************************************************************************/
void menu_patient(void) {
    help_patient();
    char choice;
    while((choice = readChar("Choice [p/x] -> ")) != 'x') {
        switch(choice) {
            case 'p': searchPatient(readString("Enter the file to be imported>"), 
                         readString("Enter the selected patients's full name>"));
                break;
            default : help_patient();
                break;
        }
    }
}

/*******************************************************************************
 * SEARCHES CSV FOR INDIVIDUAL PATIENT
*******************************************************************************/
void searchPatient(const char dbFileName[], const char patientName[]){
    char doctor[MAX_NAME_SIZE];
    char name[MAX_NAME_SIZE];
    char dob[MAX_DATE_SIZE];
    char phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
    char reason[MAX_REASON_SIZE];

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
            /* Delimit buffer by "\t" and set token to first string token */
            token = strtok(buffer, ",");

            /* Store patient details into corresponding variable */
            strcpy(doctor, token);
            strcpy(name, strtok(NULL, ","));
            strcpy(dob, strtok(NULL, ","));
            strcpy(phone, strtok(NULL, ","));
            strcpy(email, strtok(NULL, ","));
            strcpy(reason, strtok(NULL, ","));
            
            if(strcmp(name, patientName) == 0){
                printf("Doctor: %s\n",doctor);
                printf("Patient: %s\n",name);
                printf("Date of Birth: %s\n",dob);
                printf("Phone Number: %s\n",phone);
                printf("Email: %s\n",email);
                printf("Reason of Admission: %s\n",reason);
            }
            token = strtok(NULL, ",");
        }
    }
        fclose(database);
        return;
}

/*******************************************************************************
 * DISPLAY OPTIONS MENU
*******************************************************************************/
void help_patient() {
    printf("Menu options: \n");
    printf("p = Print information\n");
    printf("x = exit\n");
}
