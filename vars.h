#ifndef VARS_FUNC
#define VARS_FUNC

/*******************************************************************************
 * LIBRARIES
*******************************************************************************/
#include<stdlib.h>
#include<string.h>

/*******************************************************************************
 * CONSTANTS
*******************************************************************************/
#define SYS_KEY 671203
#define MIN 100000
#define MAX 999999
#define MAX_BUFFER_SIZE 2048
#define MAX_USER_SIZE 1024
#define MAX_NAME_SIZE 32
#define MAX_USERNAME_SIZE 25
#define MAX_PASSWORD_SIZE 32
#define MAX_PHONE_SIZE 13
#define MAX_REASON_SIZE 2048
#define MAX_DATE_SIZE 11
#define MAX_FILE_SIZE 20
#define MAX_EMAIL_SIZE 30

/* DAY
 * - between 1 and 31
 */
#define MIN_DAY_SIZE 1
#define MAX_DAY_SIZE 31

/* Month
 * - between 1 and 12
 */
#define MIN_MONTH_SIZE 1
#define MAX_MONTH_SIZE 12

/* YEAR
 * - between 1800 and 2020
 */
#define MIN_YEAR_SIZE 1800
#define MAX_YEAR_SIZE 2020


/*******************************************************************************
 * MACROS
*******************************************************************************/
#define U_ON printf("\n\033[4m")
#define U_OFF printf("\033[0m ")
#define random(min, max) ((rand()%(int)(((max) + 1)-(min)))+ (min))

#endif
