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
		        system("cls");
		        printf("\nFoodie App Menu\n");
		        printf("[1] Add Food Log\n");
		        printf("[2] Add Recipe\n");
		        printf("[3] Modify Food Log\n");
		        printf("[4] Modify Recipe\n");
		        printf("[5] Delete Food Log\n");
		        printf("[6] Delete Recipe\n");
		        printf("[7] Display User\n");
		        printf("[8] Display All Food Log and Recipe by Username\n");
		        printf("[9] Display All Food Log\n");
		        printf("[10] Display All Recipe\n");
		        printf("[11] Search Food Log\n");
		        printf("[12] Search Recipe\n");
		        printf("[13] Export Data\n");
		        printf("[14] Import Data\n");
		        printf("[15] Exit\n");
		        printf("Enter your choice: ");
		        scanf("%d", &choice);

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
		                
		                break;
		            case 4:
		                
		                break;
		            case 5:
		                
		                break;
		            case 6:
		                
		                break;
		            case 7:
		                
		                break;
		            case 8:
		                
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
		        system("cls");
		        printf("\nFoodie App Menu\n");
		        printf("[1] Add Food Log\n");
		        printf("[2] Add Recipe\n");
		        printf("[3] Modify Food Log\n");
		        printf("[4] Modify Recipe\n");
		        printf("[5] Delete Food Log\n");
		        printf("[6] Delete Recipe\n");
		        printf("[7] Display User\n");
		        printf("[8] Display All Food Log and Recipe by Username\n");
		        printf("[9] Display All Food Log\n");
		        printf("[10] Display All Recipe\n");
		        printf("[11] Search Food Log\n");
		        printf("[12] Search Recipe\n");
		        printf("[13] Export Data\n");
		        printf("[14] Import Data\n");
		        printf("[15] Exit\n");
		        printf("Enter your choice: ");
		        scanf("%d", &choice);

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
		                
		                break;
		            case 4:
		                
		                break;
		            case 5:
		                
		                break;
		            case 6:
		                
		                break;
		            case 7:
		                
		                break;
		            case 8:
		                
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