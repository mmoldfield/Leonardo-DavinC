/* See accompanying header file for documentation */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"

/******************************************************************************/
int readFile(FILE* f, LinkedList* commands)
{
    int lineNo; /* allows errors to tell the user which line is broken */
    int code; 
    char nameChar; /* char representation of a command name */
    char* tempCmdName;
    char* tempCmdVal;
    char* tempLine;
    char* cPtr;
    double* dPtr;
    int* iPtr;
    void* dataPtr;
    Command* cmdPtr;
    xFunc func;

    lineNo = 1; /* first line of the file */
    code = SUCCESS; /* assume everything runs smoothly */

    /* allocate memory for storing fscanf elements temporarily */
    tempLine = (char*)malloc(sizeof(char) * (MAX_LINE_LENGTH));
    tempCmdName = (char*)malloc(sizeof(char) * (MAX_NAME_LENGTH + 1));
    tempCmdVal = (char*)malloc(sizeof(char) * (MAX_VAL_LENGTH + 1));

    if (tempCmdName == NULL || tempCmdVal == NULL) /* mem allocation fail */
    {
        printf("%s\n", ERR_MEM_AL);
        code = FAILURE;
    }

    /* this loop is long and thorough... sorry if you're marking this :( */
    while (!feof(f) && code == SUCCESS)
    {
        code = FAILURE; /* base case - failure unless proven true */

        fgets(tempLine, MAX_LINE_LENGTH, f); /* read line into buffer */

        if (strncmp(tempLine, "\n", 1) == 0)
        {
            /* the line being read is blank */
            printf("Line %d: %s\n", lineNo, ERR_BLANK_LINE);
            printf("%s\n", ERR_RD_ME);
        }
        else
        {
            if(sscanf(tempLine, "%7s %20s", tempCmdName, tempCmdVal) != 2)
            {
                /* scanf didn't read the expected number of args... FAIL */
                printf("Line %d: %s\n", lineNo, ERR_INV_LINE);
                printf("%s\n", ERR_RD_ME);
            }
            else /* scanf worked */
            {
                /* validate the name and get a char representing it */
                nameChar = validCmdName(tempCmdName);

                if (nameChar == I) /* the command name is INVALID */
                {
                    printf("Line %d: you entered %s. %s\n", lineNo, tempCmdName,
                    ERR_INV_NAME);
                    printf("%s\n", ERR_RD_ME);
                }
                else /* the command name is VALID */
                {
                    /* validate the value on the right side of the name */
                    if (validCmdValue(nameChar, tempCmdVal) == FAILURE)
                    {
                        /* tell the user their command name is wrong */
                        printf("Line %d: you entered the command name %s. %s\n",
                        lineNo, tempCmdVal, ERR_INV_VAL);

                        printf("%s\n", ERR_RD_ME);
                    }
                    else /* value is valid */
                    {
                        /* rotate, move or draw */
                        if (nameChar == R || nameChar == M || nameChar == D)
                        {
                            /* create heap space for one double */
                            dPtr = (double*)malloc(sizeof(double));

                            if (dPtr == NULL)
                            {
                                dataPtr = NULL; /* error msg after switch */
                            }
                            else
                            {
                                *dPtr = atof(tempCmdVal); /* str to real */
                                dataPtr = dPtr; 
                                /* points void pointer to the double ptr */

                                if (nameChar == R) /* rotate */
                                {
                                    func = &rotateFunc;
                                }
                                else if (nameChar == M) /* move */
                                {
                                    func = &moveFunc;
                                }
                                else /* draw */
                                {
                                    func = &drawFunc;
                                }
                            }
                        }
                        /* foreground or background */
                        else if (nameChar == F || nameChar == B)
                        {
                            /* create heap space for one int */
                            iPtr = (int*)malloc(sizeof(int));

                            if (iPtr == NULL)
                            {
                                dataPtr = NULL; /* error msg after switch */
                            }
                            else
                            {
                                *iPtr = atoi(tempCmdVal); /* str to int */
                                dataPtr = iPtr;
                                /* points void pointer to int ptr */
                                
                                if (nameChar == F) /* foreground */
                                {
                                    func = &fgFunc;
                                }
                                else
                                {
                                    func = &bgFunc;
                                }
                            }
                        }
                        else
                        {
                            /* create heap space for one char */
                            cPtr = (char*)malloc(sizeof(char));

                            if (cPtr == NULL)
                            {
                                dataPtr = NULL; /* error msg after switch */
                            }
                            else
                            {
                                *cPtr = tempCmdVal[0]; /* str to char */
                                dataPtr = cPtr;
                                /* points void pointer to char pointer */

                                func = &patternFunc;
                            }
                        }
                        /* end of if else checks */

                        if (dataPtr == NULL) /* mem allocation failed above */
                        {
                            printf("Line %d: %s\n", lineNo, ERR_MEM_AL);
                        }
                        else
                        {
                            cmdPtr = (Command*)malloc(sizeof(Command));

                            if (cmdPtr == NULL) /* mem allocation failed */
                            {
                                /* memory allocation failed */
                                printf("Line %d: %s\n", lineNo, ERR_MEM_AL);

                                free(dataPtr);
                                /* free the malloc from above */
                            }
                            else /* designate values to our struct */
                            {
                                cmdPtr->job = func;
                                cmdPtr->value = dataPtr;
                                
                                if (insertLast(commands, cmdPtr) == SUCCESS)
                                {
                                    code = SUCCESS; 
                                }
                                else /* mem allocation for list node failed */
                                {
                                    free(cmdPtr); /* free malloc from above */
                                    free(dataPtr); /* free malloc from above */
                                    printf("Line %d: %s\n", lineNo, ERR_MEM_AL);
                                }
                            }
                        }
                    }
                }
            }
        }


        lineNo++; /* incriment lineNo so we can provide useful err messages */

        /* reset our strings before the next iteration */
        strncpy(tempLine, "", MAX_LINE_LENGTH);
        strncpy(tempCmdName, "", MAX_NAME_LENGTH); 
        strncpy(tempCmdVal, "", MAX_VAL_LENGTH);
    }
    /* end of hideously long while loop */

    /* free our buffers */
    free(tempLine);
    free(tempCmdName); 
    free(tempCmdVal);
    fclose(f); /* close the file */

    return code;
}

/******************************************************************************/
char validCmdName(char* name)
{
    int ii;
    int code;
    char returnChar; /* identifies what type of command it is */
    char* names[NUM_NAMES] = { ROTATE, MOVE, DRAW, FG, BG, PATTERN };
    char nameChars[NUM_NAMES] = { R, M, D, F, B, P };

    returnChar = I; /* invalid */ 
    code = FAILURE; /* assume the name is invalid */

    stringToUpper(name); /* converts name to all caps */

    ii = 0;
    while (code == FAILURE && ii < NUM_NAMES)
    {
        if (strncmp(name, names[ii], MAX_NAME_LENGTH) == 0) /* name matches */
        {
            code = SUCCESS;
            returnChar = nameChars[ii]; 
        }
        ii++;
    }

    /* if no match was found in the loop, I will be returned */
    return returnChar;
}

/******************************************************************************/
void stringToUpper(char* str)
{
    int ii;

    for (ii = 0; ii < strlen(str); ii++)
    {
        if (str[ii] >= 'a' && str[ii] <= 'z') /* valid alphabet char */
        {
            str[ii] = str[ii] - 32; /* convert to upper */
        }
    }
}

/******************************************************************************/
int validCmdValue(char nameChar, char* tempCmdVal)
{
    int valid;

    valid = FAILURE; /* default case */

    switch (nameChar) /* validate the value */
    {
        case R : /* rotate */
            valid = validStrDouble(tempCmdVal, R_MIN, R_MAX);
            break;
        case M : /* move */
            valid = validStrDouble(tempCmdVal, M_MIN, M_MAX);
            break;
        case D : /* draw */
            valid = validStrDouble(tempCmdVal, D_MIN, D_MAX);
            break;
        case F : /* fg */
            valid = validStrInt(tempCmdVal, F_MIN, F_MAX);
            break;
        case B : /* bg */
            valid = validStrInt(tempCmdVal, B_MIN, B_MAX);
            break;
        case P : /* pattern */
            valid = validPattern(tempCmdVal);
    }

    return valid;
}
/******************************************************************************/
int validStrDouble(char* strDouble, double min, double max)
{
    int code;
    double temp;

    temp = atof(strDouble); /* convert string to double */

    code = SUCCESS; /* assume that the value imported is valid */

    /* atof returns 0.0 if it is unsuccessful. However, 0.0 is also a
    valid real number - we use strcmp to make sure the user didn't
    intend to input 0.0 */

    if (temp == 0.0 && strncmp(strDouble, "0.0", MAX_VAL_LENGTH) != 0)
    {
        code = FAILURE;
    }
    else
    {
        if (temp < min || temp > max)
        {
            code = FAILURE; /* outside bounds */
        }
    }

    return code;
}

/******************************************************************************/
int validStrInt(char* strInt, int min, int max)
{
    int code;
    int temp;

    temp = atoi(strInt); /* convert string to int */

    code = SUCCESS; /* assume that the value imported is valid */

    /* atoi returns 0 if it is unsuccessful. However, 0 is also a
    valid integer - we use strcmp to make sure the user didn't intend to
    input 0 */
    if (temp == 0 && strncmp(strInt, "0", MAX_VAL_LENGTH) != 0)
    {
        code = FAILURE;
    }
    else
    {
        if (temp < min || temp > max)
        {
            code = FAILURE; /* outside bounds */
        }
    }

    return code;
}

/******************************************************************************/
int validPattern(char* strChar)
{
    char temp;
    int code;

    code = SUCCESS; /* assume everything goes to plan */

    if (strlen(strChar) == 1)
    {
        temp = strChar[0]; /* first char */

        if (temp < P_MIN || temp > P_MAX)
        {
            code = FAILURE; /* outside bounds */
        }
    }
    else
    {
        code = FAILURE;
    }

    return code;
}