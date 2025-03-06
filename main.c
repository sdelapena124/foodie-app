#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

#include "mpfxn.c"

int
main()
{
	User profile = verifyProfile();
	
    sleep(1);
	system("cls");
   	
   	int loginSuccessful = verifyUser(profile);

    if (loginSuccessful)
    {
        printf("MENU\n");
 
    }
    else
    {
        // Login failed after maximum attempts.
        printf("Program terminated due to failed login.\n");
    }

    










    return 0;
}