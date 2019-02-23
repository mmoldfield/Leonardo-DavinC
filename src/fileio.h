/*******************************************************************************
* AUTHOR: Matthew Oldfield
* FILE NAME: fileio
* PURPOSE: methods in this file are responsible for file reading and file 
validation. this includes things like ensuring the input file is in a valid
format, throwing error messages that provide useful feedback to the user,
and storing the commands read in from the file into a linked list that can be
called upon from other parts of the program
* CREATED: 2018-10-13
*******************************************************************************/

#ifndef FILEIO
#define FILEIO

#include "universal.h"
#include "linkedlist.h"
#include "execute.h"

/* constants that we can alter easily if the requirements of the program
change */
#define MAX_NAME_LENGTH 7 /* max length that a command name should be */
#define MAX_VAL_LENGTH 20 /* max length that a command value should be */
#define MAX_LINE_LENGTH (MAX_NAME_LENGTH + MAX_VAL_LENGTH)

/* different strings that we will output to the user to give them meaningful 
feedback */
#define ERR_BLANK_LINE "Incorrect line format. File cannot contain blank lines."
#define ERR_INV_LINE "Incorrect line format. Line should contain 1 command and \
1 command value (seperated by a single space)."
#define ERR_INV_NAME "Invalid command name. Valid command names include \
"MOVE", "DRAW", "ROTATE", "BG", "FG" and "PATTERN"."
#define ERR_LONG_LINE "The line input is too long."
#define ERR_INV_VAL "The value on this line is invalid."
#define ERR_MEM_AL "Your system doesn't have enough memory to run this program."
#define ERR_RD_ME "Please see the readme.txt for full instructions."

/* command names. storing these as constants allows for easy modification in
the future (for example, if we wanted to change the term ROTATE to TURN, we 
could just change the value here instead of all the instances that the term
appears */
#define NUM_NAMES 6
#define ROTATE "ROTATE"
#define MOVE "MOVE"
#define DRAW "DRAW"
#define FG "FG"
#define BG "BG"
#define PATTERN "PATTERN"

/* chars for identifying various commands */
#define R 'r' /* char representing rotate */
#define M 'm' /* move */
#define D 'd' /* draw */
#define F 'f' /* fg */
#define B 'b' /* bg */
#define P 'p' /* pattern */
#define I 'i' /* invalid command name */

/* these values are used for validing the input file */
#define TOL 0.001 /* for double comparison */
#define R_MIN -360.0 /* these limits are not technically required, but they make
the input files much more readable */
#define R_MAX 360.0
#define M_MIN -100.0
#define M_MAX 100.0
#define D_MIN M_MIN /* same as M_MIN */
#define D_MAX M_MAX /* same as M_MAX */
#define F_MIN 0 /* colours */
#define F_MAX 15 /* colours */
#define B_MIN 0 /* colours */
#define B_MAX 7 /* colours */
#define P_MIN 0 /* ascii */
#define P_MAX 127 /* ascii */

/* this is by far the longest and most important method in the program. overall,
its purpose is to import a file pointer and a linked list of commands, and then
iterate through the file, creating command pointers out of valid lines and then
storing them in this linked list. this process requires extensive validation
and plenty of feedback for the user to let them know if their input file has
something invalid in it. this method will return SUCCESS if the file has been
successfully read into a linkedlist, or FAILURE otherwise. in the case of 
failure, it will also free the memory that is no longer required */
int readFile(FILE* f, LinkedList* commands);

/* imports a char* representing the name of a command, and compares it to 
an array of macro definitions containing the names of valid commands. if the
command is valid, a character representing that command is returned, otherwise
the char 'i' is returned to signal that it is invalid. Note that this method
will not work with string literals (expect a seg fault) and all imported 
strings will be turned to upper case for the remainder of run time */
char validCmdName(char* name);

/* imports a char* representing a str, and converts any lower case letters to
upper case letters. it does this by manipulating ASCII values - especially the
fact that the uppercase value of a character is the same as the lowercase char
minus 32. NOTE: do NOT import string literals - behaviour is undefined!!! */
void stringToUpper(char* str);

/* this method impoprts a char that represents one of the 6 command names
associated with the program. each of these commands has a different set of 
minimum and maximum values associated to it, so this method will validate each
type of command uniquely using macro definitions defining boundaries. will
return SUCCESS if the value is valid and false otherwise */
int validCmdValue(char nameChar, char* tempCmdVal);

/* imports a string representing a double value, and compares it to the two
boundary values imported. this method is intelligent in the way that it can
determine whether values like '0.0' were intended to be input by the user or 
were returned from our string to double function (atof). returns SUCCESS if the
string represents a double that fits within the boundaries or FAILURE
otherwise */
int validStrDouble(char* strDouble, double min, double max);

/* imports a string representing an integer value, and compares it to the two
boundary values imported. this method is intelligent in the way that it can
determined whether values like 0 were intended to be input by the user or 
were returned from our string to int function (atoi). returns SUCCESS if the
string represents an int that fits within the boundaries or FAILURE otherwise */
int validStrInt(char* strInt, int min, int max);

/* imports a string representing a character value, and checks to see if it is
valid by comparing it to the macro defined boundaries. returns SUCCESS if the
string represents a char that fits within the boundaries or FAILURE otherwise */
int validPattern(char* strChar);

#endif
