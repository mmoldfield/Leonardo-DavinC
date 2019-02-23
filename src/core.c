/* See accompanying header file for documentation */

#include <stdio.h>
#include <stdlib.h>
#include "core.h"

/******************************************************************************/
int nav(int argc, char** argv)
{
    int code; /* error code */
    LinkedList* commands; 
    FILE* f;
    int c; /* we used this to check what the first char in the file is */

    code = FAILURE; /* assume that an error is thrown, will set to SUCCESS if
    otherwise */

    if (argc != 2) /* exec name + file name */
    {
        printf("You entered %d arguments (expected %d)\n", argc-1, NUM_ARGS);
        printf("File should be input in format %s\n", FORMAT);
    }
    else
    {
        f = fopen(argv[1], "r"); /* open the file for reading */

        if (f == NULL) /* file could not be opened */
        {
            perror(ERR_OPEN_FILE); /* tells us specifically what went wrong */
        }
        else
        {
            c = fgetc(f); /* reads first character of file */
            rewind(f); /* go back to start of stream */
            
            if (c == EOF) /* the file is empty */
            {
                printf("%s\n", ERR_EMP_FILE);
                code = FAILURE;
                fclose(f); /* cloes the file */
            }
            else 
            {
                commands = makeList(); /* make linked list of command structs */

                if (readFile(f, commands) == SUCCESS) 
                {
                    if (picasso(commands) == SUCCESS)
                    {
                        code = SUCCESS; /* woohoo! */
                    }
                }

                freeLinkedList(commands); /* free our linked list */
            }
        }
    }

    return code;
}
