/*******************************************************************************
* AUTHOR: Matthew Oldfield
* FILE NAME: universal
* PURPOSE: This header file provides macro declarations that are likely to be
used by multiple files in the program. This means that the same declarations 
aren't being repeated in multiple files, and it means that files that want to
use a simple macro from another file don't need to include all of that file's
methods
* CREATED: 2018-10-13 
*******************************************************************************/

#ifndef UNIVERSAL
#define UNIVERSAL

#include <stdio.h> /* needed to use FILE* in struct */
    
/* these declarations improve readability by giving more context to the 
integer error codes used throughout the program */
#define FAILURE (-1)
#define SUCCESS (0)

/* standard boolean declarations */
#define FALSE (0)
#define TRUE (!FALSE)

/* simple struct for a singly-linked linked list node */
typedef struct Status
{
    double curX; /* current x value */
    double curY; /* current y value */
    double curA; /* current angle */
    int curF; /* current foreground colour */
    int curB; /* current background colour */
    char curP; /* current pattern */
} Status;

/* this definition will be used extensively - it allows us to assign our
commands a different function so that they can perform their own unique jobs
when we pull them from the linked list */
typedef int (*xFunc)(Status* current, void* data, FILE* f);

/* struct for our Command */
typedef struct Command
{
    xFunc job; /* function pointer */
    void* value; /* pointer to an int, double or char */
} Command;

#endif
