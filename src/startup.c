/* See accompanying header file for documentation */

#include <stdio.h>
#include "startup.h"

/******************************************************************************/
int main(int argc, char** argv)
{
    int err;

    err = nav(argc, argv);

    return err; /* expecting 0 or -1 (SUCCESS or FAILURE) */
}

