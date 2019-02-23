/* See accompanying header file for documentation */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "execute.h"
#include "fileio.h"

/******************************************************************************/
int picasso(LinkedList* commands)
{
    Status* current; /* current location, angle, colours and pattern */
    Command* cmd;
    int code;
    FILE* f;

    code = SUCCESS; /* base case: assume everything goes to plan */

    f = fopen(LOG_FILE_NAME, "a"); /* open file to append */

    if (f == NULL) /* could not open log file */
    {
        perror(ERR_OPEN_LOG);
        code = FAILURE;
    }
    else
    {
        /* allocate space for a Status struct */
        current = (Status*)malloc(sizeof(Status));

        /* initialising variables in current */
        current->curX = 0.0;
        current->curY = 0.0;
        current->curA = 0.0;
        current->curF = 7; /* white */
        current->curB = 0; /* black */
        current->curP = '+';

        #ifdef SIMPLE /* white background with black foreground */
            current->curF = 0; /* black */
            current->curB = 7; /* white */
            setFgColour(0);
            setBgColour(7);
        #endif

        clearScreen(); /* clear terminal screen for printing */
        
        while ((commands->count > 0) && code == SUCCESS)
        {
            cmd = removeFirst(commands); /* pull command out */

            if (cmd->job(current, cmd->value, f) != SUCCESS)
            {
                /* if execution fails */
                penDown(); /* move cursor to bottom of screen */
                printf("%s\n", ERR_INV_EX);
                code = FAILURE;
            }
            /* clean up... */
            free(cmd->value);
            free(cmd);
        }
        
        fclose(f); /* close the file */
        free(current);

        penDown(); /* move cursor to bottom of screen */
        setFgColour(7); /* white, back to default */
        setBgColour(0); /* black, back to default */
    }

    return code;
}

/******************************************************************************/
int rotateFunc(Status* current, void* data, FILE* f)
{
    current->curA += *((double*)data); /* updates current angle by adding the
    value of data to it */

    return SUCCESS;
}

/******************************************************************************/
int moveFunc(Status* current, void* data, FILE* f)
{
    int code;
    double x1, x2, y1, y2;

    code = SUCCESS; /* base case: assume everything works */

    /* make copies of the current values for printing */
    x1 = current->curX;
    y1 = current->curY;

    updateXY(current, *(double*)data);

    x2 = current->curX;
    y2 = current->curY;

    if (logPrinter(x1, y1, x2, y2, MOVE_STRING, f) != SUCCESS)
    {
        code = FAILURE;
    }
    
    return code;
}

/******************************************************************************/
int drawFunc(Status* current, void* data, FILE* f)
{
    int code;
    double x1, x2, y1, y2;
    PlotFunc pen;
    double* dPtr;

    code = SUCCESS; /* base case: assume everything goes to plan */
    pen = &plotter; /* func ptr now points to plotter */
    dPtr = (double*)data;

    /* making copies for later printing */
    x1 = current->curX; 
    y1 = current->curY;

    /* incriments of 90 do not require the -1 fix to stop double printing. I 
    worked this out by realising that i could print the diamond file pre fix,
    but not after the fix. I then noticed a pattern in the charizard file, in
    that it was all multiples of 90, and hacked together this fix. To be honest,
    I don't know WHY it works... I just know that it works. */
    if (round(current->curA) % 90 == 0)
    {
        updateXY(current, *dPtr-1.0); /* decrease distance by 1 */
    }
    else
    {
        updateXY(current, *dPtr); /* decrease distance by 1 */
    }
    
    x2 = current->curX;
    y2 = current->curY;

    line(round(x1), round(y1), round(x2), round(y2), pen, &current->curP);

    if (round(current->curA) % 90 == 0)
    {
        updateXY(current, 1.0); /* move cursor along */
        x2 = current->curX;
        y2 = current->curY;
    }

    /* time to print */ 
    if (logPrinter(x1, y1, x2, y2, DRAW_STRING, f) != SUCCESS)
    {
        code = FAILURE;
    }

    return code;
}

/******************************************************************************/
int fgFunc(Status* current, void* data, FILE* f)
{
    /* ignore the colour change when in simple mode */
    #ifndef SIMPLE
        current->curF = *(int*)data; /* update status */
        setFgColour(current->curF);
    #endif

    return SUCCESS;
}

/******************************************************************************/
int bgFunc(Status* current, void* data, FILE* f)
{
    /* ignore the colour change when in simple mode */
    #ifndef SIMPLE
        current->curB = *(int*)data; /* update status */
        setBgColour(current->curB);
    #endif

    return SUCCESS;
}

/******************************************************************************/
int patternFunc(Status* current, void* data, FILE* f)
{
    current->curP = *(char*)data; /* update status */

    return SUCCESS;
}

/******************************************************************************/
void plotter(void* plotData)
{
    char* pattern;

    pattern = (char*)plotData; /* plotdata should always point to a char */

    printf("%c", *pattern);
}

/******************************************************************************/
void updateXY(Status* current, double distance)
{
    double rad;

    rad = current->curA * PI / 180.0; /* standard maths formula */

    /* find the real movement values based on the current angle */
    current->curX = current->curX + (distance * cos(rad));
    current->curY = current->curY - (distance * sin(rad));
}

/******************************************************************************/
int round(double value)
{
    int rounded;

    rounded = (int)(value + 0.5); /* simple rounding hack */

    return rounded;
}

/******************************************************************************/
int logPrinter(double x1, double y1, double x2, double y2, char* job, FILE* f)
{
    int code;
    static int printCount = 0; /* lasts through method evocations */

    code = SUCCESS; /* base case: assume it works */

    if (printCount == 0) /* the first print in this execution */
    {
        fprintf(f, "%s\n", NEW_LINE_IND);
    }

    /* this format matches that in the program requirements */
    fprintf(f, "%s (%7.3f,%7.3f)-(%7.3f,%7.3f)\n", job, x1, y1, x2, y2);

    /* prunt to stderr if debug is defined */
    #ifdef DEBUG
        fprintf(stderr, "%s (%7.3f, %7.3f)-(%7.3f, %7.3f)\n", job, x1, y1,
        x2, y2);
    #endif

    printCount++; /* so we know not to print the divided again */

    return code;
}
