/*
 * is_background.c :  check for & at end
 */

#include <stdio.h>
#include "shell.h"

int is_background(char ** myArgv)
{
    if (*myArgv == NULL)
        return 0;
    /* Look for "&" in myArgv, and process it.
     *
     *	- Return TRUE if found.
     *	- Return FALSE if not found.
     *
     * Fill in code.
     */
    int numa=0;
    while(myArgv[numa]!=0)
    {
        if(strcmp("&",myArgv[numa])==0)
        {
            return 1;
            break;
        }
        numa++;
    }
    return 0;
}
