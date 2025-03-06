#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

#include "mpfxn.c"

int
main()
{
    User profile = verifyProfile();
    

    verifyUser(profile);

    printf("MENU");










    return 0;
}