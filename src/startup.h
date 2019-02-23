/*******************************************************************************
* AUTHOR: Matthew Oldfield
* FILE NAME: startup
* PURPOSE: This file contains the main method of the program, and nothing else.
This decision was made specifically to de-couple my main function from my other
methods. This was done purely so that I could run a test harness on my methods
as I created them (the test harness needed a main function, and you can't have 
two instances of main in the same program)
* CREATED: 2018-10-13 
*******************************************************************************/

#ifndef STARTUP
#define STARTUP

#include "core.h"

/* Sends argc and argv off to nav function and receives an int representing an
error code in return. This error code will be returned to signify that the 
program has been executed successfully/unsuccessfully */
int main(int argc, char** argv);

#endif
