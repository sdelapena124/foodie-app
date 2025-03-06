#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

#include "mpfxn.c"

int
main()
{
	User profile;
    FILE *userFile = fopen("user.txt", "r");

    if (userFile != NULL) 
    {
        fclose(userFile);  // Close file after confirming existence
        profile = verifyProfile();  // Load existing user profile
        int loginSuccessful = verifyUser(profile);
        
        if (loginSuccessful)
        {
            printf("MENU\n");
        }
        else
        {
            printf("Program terminated due to failed login.\n");
        }
    }
    else
    {
        profile = verifyProfile();  // Register a new user if file does not exist
        sleep(1);
        system("cls");
        int loginSuccessful = verifyUser(profile);

        if (loginSuccessful)
        {
            printf("MENU\n");
        }
        else
        {
            printf("Program terminated due to failed login.\n");
        }
    }

    return 0;
}