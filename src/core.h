/*******************************************************************************
* AUTHOR: Matthew Oldfield
* FILE NAME: core
* PURPOSE: This file is responsible for controlling the overall flow
of the program. This includes making decisions about whether or not the program
should run or not, allocating memory and freeing it, error handling and evoking
other methods that lead the program to its final state.
* CREATED: 2018-10-13 
*******************************************************************************/

#ifndef CORE
#define CORE

#include "universal.h"
#include "linkedlist.h"
#include "fileio.h"
#include "execute.h"

#define NUM_ARGS 1 /* we only expect 1 cmd line arg in addition to file name */
#define FORMAT "./programname 'inputfile'" /* printed when user evokes
program in the wrong format */
#define ERR_OPEN_FILE "The file could not be opened."
#define ERR_EMP_FILE "The file is empty."

/* The purpose of this method is to act as a controller, deciding whether or 
not the program should continue running based on the responses it receives from
control structres and other methods. In addition, you will note that things 
like the program's linked list and file pointer are created here - this is so
that these items can be returned to a centralised spot for easy future program
modification */
int nav(int argc, char** argv);

#endif

