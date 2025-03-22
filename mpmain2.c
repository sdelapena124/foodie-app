#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

#include "mpfxn2.c"

int
main()
{
	User profile;
	int choice;
	
    FILE *userFile = fopen("user.dat", "r");

    if (userFile != NULL) 
    {
        fclose(userFile);  // Close file after confirming existence
        profile = verifyProfile();  // Load existing user profile
        int loginSuccessful = verifyUser(&profile);
        
        if (loginSuccessful)
        {
        	do 
			{
		        // Display menu
		        choice = displayMenu();

		        // Process user choice
		        switch (choice) 
				{
		            case 1:
		                addFoodLog();
		                break;
		            case 2:
		                addRecipe();
		                break;
		            case 3:
		            	modifyFoodLog();
		                break;
		            case 4:
                        modifyRecipe();
                        break;
                    case 5:
                        deleteFoodLog();
                        break;
                    case 6:
                        deleteRecipe();
                        break;
                    case 7:
                        displayUser(&profile);
                        break;
                    case 8:
                        displayAllByUsername(&profile);
                        break;
                    case 9:
                        
                        break;
                    case 10:
                        
                        break;
		            case 11:
		                
		                break;
		            case 12:
		                
		                break;
		            case 13:
		                
		                break;
		            case 14:
		                
		                break;
		            case 15:
		                
		                printf("Exiting program...\n");
		                break;
		            default:
		                printf("Invalid choice. Please try again.\n");
        		}
    		} while (choice != 15);
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
        int loginSuccessful = verifyUser(&profile);

        if (loginSuccessful)
        {
        	do 
			{
		        // Display menu
		        choice = displayMenu();

		        // Process user choice
		        switch (choice) 
				{
		            case 1:
		                addFoodLog();
		                break;
		            case 2:
		                addRecipe();
		                break;
		            case 3:
		            	modifyFoodLog();
		                break;
		            case 4:
                        modifyRecipe();
                        break;
                    case 5:
                        deleteFoodLog();
                        break;
                    case 6:
                        deleteRecipe();
                        break;
                    case 7:
                        displayUser(&profile);
                        break;
                    case 8:
                        displayAllByUsername(&profile);
                        break;
		            case 9:
		                
		                break;
		            case 10:
		                
		                break;
		            case 11:
		                
		                break;
		            case 12:
		                
		                break;
		            case 13:
		                
		                break;
		            case 14:
		                
		                break;
		            case 15:
		                
		                printf("Exiting program...\n");
		                break;
		            default:
		                printf("Invalid choice. Please try again.\n");
        		}
    		} while (choice != 15);
        }
        else
        {
            printf("Program terminated due to failed login.\n");
        }
    }

    return 0;
}