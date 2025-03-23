#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

#include "mpfxn2.c"

int main() 
{
    User profile;
    int choice;
    char filename[MAX_FILENAME + 1];
    int loginSuccessful = 0;
    int nOption;
    
    while (1) 
	{
		printf("\t\t----------------------------------------------------------------------------\n");
    	printf("\t\t|                                                                          |\n");
    	printf("\t\t|                              [1] Login               	                   |\n");
    	printf("\t\t|                              [2] Register           	                   |\n");
    	printf("\t\t|                              [3] Exit               	                   |\n");
    	printf("\t\t|                                                                          |\n");
    	printf("\t\t----------------------------------------------------------------------------\n");
        printf("\t\t\tEnter option number: ");
        
        if (scanf("%d", &nOption) != 1) 
        {
            printf("Invalid input. Please enter a number between 1-3.\n");

            // Clear input buffer
            while (getchar() != '\n');

            system("pause");
            system("cls");
        }
        
        else
        {

	        if (nOption == 1) 
			{
	            FILE *userFile = fopen("profiles.dat", "r");
	            if (userFile != NULL) 
				{
	                fclose(userFile);
	                loginSuccessful = verifyUser(&profile);
	            } 
				else 
				{
	                printf("\nNo user profile found. Please register first.\n");
	            	system("pause");
	            	system("cls");
	            }
	        } 
			else if (nOption == 2) 
			{
	            profile = verifyProfile();
	            system("pause");
	        } 
			else if (nOption == 3) 
			{
	            printf("Exiting program...\n");
	            return 0;
	        } 
			else 
			{
	            printf("Invalid choice. Please try again.\n");
	            system("pause");
	            system("cls");
	        }
		}
		
        if (loginSuccessful) 
		{
            showLoadingBar();
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
                        displayAllFoodLogs();
                        break;
                    case 10:
                        displayAllRecipes();
                        break;
                    case 11:
                        searchFoodLog();
                        break;
                    case 12:
                        searchRecipe();
                        break;
                    case 13:
                        break;
                    case 14:
                        break;
                    case 15:
                        printf("Exiting program...\n");
                        return 0;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (choice != 15 && loginSuccessful);
        } 
//		else 
//		{
//            printf("Program terminated due to failed login.\n");
//        }
    }
    return 0;
}
