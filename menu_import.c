/*******************************************************************************
 * HEADER FILES
*******************************************************************************/
#include "menu_import.h"
#include "menu_patient.h"

/*******************************************************************************
 * IMPORT MENU
*******************************************************************************/
void menu_import(Node_t** head, const char* dbFileName) {
    help_import();
    char choice;
    while((choice = readChar("Import menu: Choice [a/x] -> ")) != 'x') {
        switch(choice) {
            case 'a':
                readFileMenu(head, readString("Enter the file to be imported>"));
                break;
/*             case 'p':
                searchPatient(readString("Enter the file to be imported>"), readString("Enter the selected patients's full name>"));
                break;
            case 'd':
                importDoctorRecords(head, readString("Enter the file to be imported>"), readString("Enter the selected doctor's full name>"));
                break; */
            default: help_import();
                break;
        }
    }
    printf("Leaving import menu...\n\n");
}

/*******************************************************************************
 * IMPORT MENU HELPER
*******************************************************************************/
void help_import() {
    printf("Import Menu options: \n");
    printf("a = Import all records\n");
    printf("x = exit\n");
}
