/*******************************************************************************
* AUTHOR: Matthew Oldfield
* FILE NAME: execute
* PURPOSE: the functions in this file are dedicated to the execution of the 
program - that is, taking the values from the linked list of commands and using
them to do things like rotate, move, draw and set the fg, bg and pattern of 
the drawing functions. also included is the logprinter function which prints
cordinates to the terminal or log file based (depending on which execution the
user has chosen to run)
* CREATED: 2018-10-15
*******************************************************************************/

#ifndef EXECUTE
#define EXECUTE

#include "universal.h"
#include "linkedlist.h"
#include "effects.h"

#define PI 3.14159265359 /* mmmmmm..... pie...... */
#define ERR_INV_EX "Command execution failed. Please consult the developer"
#define LOG_FILE_NAME "graphics.log"
#define ERR_OPEN_LOG "The log file could not be opened."

/* these definitions are for log printing */
#define MOVE_STRING "MOVE"
#define DRAW_STRING "DRAW"
#define NEW_LINE_IND "---"

/* this method is responsible for the artistic part of the program - it reads
the commands from the linked list, and then sends them off the the functions
defined by the pointers stored in the command struct. it also provides useful
feedback to the user if the execution fails, and cleans up memory when required
*/
int picasso(LinkedList* commands);

/* this method simply updates the current angle to be equal to itself plus
whatever double the void* data points to. this method doesn't use the imported
FILE* - obviously it is not good to import variables you don't need, but this
trade off was made so that all of the different command functions could be
typedef'd to something consistent */
int rotateFunc(Status* status, void* data, FILE* f);

/* this method updates the current x and y coordinates to reflect the change
in location defined by the value that data points to. it does this by calling
the updateXY commands which uses trigonometry to determined the new coordinates.
it will also call the logPrinter function so that this change can be included
in the log file */
int moveFunc(Status* status, void* data, FILE* f);

/* this method updates the current x and y coordinates to reflect the change
in location defined by the value that data points to. it does this by calling
the updateXY commands which uses trigonometry to determined the new coordinates.
most importantly, it then calls the line function which essentially tells the
program to draw from one location to another. it will also call the logPrinter
function so that this change can be included in the log file */
int drawFunc(Status* status, void* data, FILE* f);

/* this method simply updates the current foreground colour - however, if the 
'SIMPLE' has been defined by the preprocessor, this change will be ignored. this
method will always return SUCCESS because there is no way that it can fail 
within the scope of this program */
int fgFunc(Status* status, void* data, FILE* f);

/* this method simply updates the current background colour - however, if the 
'SIMPLE' has been defined by the preprocessor, this change will be ignored. this
method will always return SUCCESS because there is no way that it can fail
within the scope of this program */
int bgFunc(Status* status, void* data, FILE* f);

/* this method simply updates the current pattern character based on the 
data imported. this method will always return SUCCESS because there is no way
that it can fail within the scope of the program */
int patternFunc(Status* status, void* data, FILE* f);

/* this method is essentially a wrapper for printf. it takes in a void* that
we can expect points to a char, converts it to a char* and then prints the 
deferenced value to the terminal */
void plotter(void* plotData);

/* this method uses trigonometry to work out how far along the x and y axis
our current position should be moved. it calculates this by converting the 
current angle to radians (rad = angle * PI / 180), and then calculating the 
distance travelled and appending it to the current x and y values */
void updateXY(Status* current, double distance);

/* this method is super simple - typecasting a double to int will always result
in the number being rounded down (for example (int)4.9 becomes 4) we can use
the simple trick of adding 0.5 to the double value, and THEN casting to an int.
this will always give us an accurate round to the nearest integer. because there
is no way that this function can fail in the scope of the program, it will 
always return SUCCESS */
int round (double value);

/* this method is responsible for appending the log file whenever a move or a
distance command is evoked. this includes the name of the commands, followed by 
the to and from locations. if the preprocessor macro DEBUG has been defined,
it will also print this to stderr as requested in the program requirements */
int logPrinter(double x1, double y1, double x2, double y2, char* job, FILE* f);

#endif

