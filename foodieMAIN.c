#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

#include "foodieHEADER.h"
#include "foodieFXN.c"

int main() 
{
    User profile;
    int choice;
    int loginSuccessful = 0;
    int nOption;
    
    while (1) 
	{
		system("cls");
		printf("=============================================\n");
        printf("|            WELCOME TO FOODIE APP          |\n");
        printf("=============================================\n");
        printf("| [1] + Login                               |\n");
        printf("| [2] + Register                            |\n");
        printf("| [3] + Exit                                |\n");
        printf("=============================================\n");
        printf("Enter option number: ");
        
        if (scanf("%d", &nOption) != 1) 
        {
            printf("Invalid input. Please enter a number between 1-3.\n");

            // Clear input buffer
            while (getchar() != '\n');

            system("pause");
            system("cls");
        }
        
        switch (nOption) 
        {
            case 1:
                {
                    FILE *userFile = fopen("profiles.dat", "r");
                    if (userFile != NULL) 
                    {
                        fclose(userFile);
                        loginSuccessful = verifyUser(&profile);

                        if (!loginSuccessful) 
                        {
                            while (getchar() != '\n');
                            return 0;
                        }
                    } 
                    else 
                    {
                        printf("\nNo user profile found. Please register first.\n");
                        system("pause");
                    }
                }
                break;

            case 2:
                profile = verifyProfile();
                system("pause");
                break;

            case 3:
                printf("Exiting program...\n");
                return 0;

            default:
                break;
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
                    	system("cls");
                        addFoodLog(&profile);
                        break;
                    case 2:
                    	system("cls");
                        addRecipe(&profile);
                        break;
                    case 3:
                    	system("cls");
                        modifyFoodLog(&profile);
                        break;
                    case 4:
                    	system("cls");
                        modifyRecipe(&profile);
                        break;
                    case 5:
                    	system("cls");
                        deleteFoodLog(&profile);
                        break;
                    case 6:
                    	system("cls");
                        deleteRecipe(&profile);
                        break;
                    case 7:
                    	system("cls");
                        displayUser(&profile);
                        break;
                    case 8:
                    	system("cls");
                        displayAllByUsername(&profile);
                        break;
                    case 9:
                    	system("cls");
                        displayAllFoodLogs();
                        break;
                    case 10:
                    	system("cls");
                        displayAllRecipes();
                        break;
                    case 11:
                    	system("cls");
                        searchFoodLog();
                        break;
                    case 12:
                    	system("cls");
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
        loginSuccessful = 0;
    }
    return 0;
}
