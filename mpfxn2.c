#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_INGREDIENTS 20
#define MAX_INSTRUCTIONS 20
#define MAX_USERNAME_LENGTH 51
#define MAX_FILENAME 30

/* FOOD LOG STRUCT */
typedef struct 
{
    char name[51];
    char type;
    int timesEaten;
    char ftDate[11];
    char ftPlace[31];
    char desc[301];    
} foodLog;

/* RECIPE STRUCT */
typedef struct 
{
    char name[51];
    char desc[161];
    int prepTime;
    int cookTime;
    int numIng;
    char ingredients[MAX_INGREDIENTS][81];
    int numInstructions;
    char instructions[MAX_INSTRUCTIONS][101];
} Recipe;

/* USER STRUCT */
typedef struct
{
    char username[51];
    char pass[21];
    char name[81];
    char email[31];
    char number[12];
} User;

//Divider
void displayDivider ()
{
	printf("\n\n====================================\n");
}

/* func to check if string is alphanumeric*/
int
isAlphanumeric(char *str)
{
    int i;
    int num; //number of non alphanumeric char
    int len = strlen(str);

    for(i = 0; i < len; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= '0' && str[i] <= '9'))) 
        {
            return 0;
        }
    }

    return 1;
}

/* func to check if string is alphabetic */
int
isAlphabetic(char *str)
{
    int i;
    int len = strlen(str);

    for(i = 0; i < len; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z'))
			  && (str[i] != ' ')) 
        {
            return 0;
        }
    }

    return 1;

}

//for clearing input buffer for scanf
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* func to check if string is in bounds */
int
withinBounds(char *str, int lowerLimit, int upperLimit)
{
    int len = strlen(str);

    if (strlen(str) < lowerLimit || strlen(str) > upperLimit)
    {
        return 0;
    }

    return 1;
}


/* func to check if password is valid */
int
verifyPass(char *str)
{
    int i;
    int lower = 0;
	int upper = 0;
	int special = 0; 
	int num = 0;
    int len = strlen(str);

    for(i = 0; i < len; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            upper = 1;
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            lower = 1;
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            num = 1;
        }
        else if (str[i] == '!' || 
           str[i] == '@' ||
           str[i] == '$' ||
           str[i] == '%' ||
           str[i] == '&' ||
           str[i] == '*' ||
           str[i] == '.')
        {
            special = 1; 
        }
    }

    return (special && lower && upper && num);
}

/* func to check phone number*/
int
verifyNumber(char *str)
{
    int i;
    
    if (strlen(str) != 11)
    {
    	return 0;
	}
	
    if (str[0] != '0') 
    {
        return 2; 
    }

    for (i = 1; i < 11; i++)
    {
		if (str[i] < '0' || str[i] > '9')
        {
            return 0;
        }
	}
        
    return 1;
}

int verifyEmail (char *str)
{
	int length;
	int i;
	int atIndex = -1;
	int dotIndex = -1;
	int atCount = 0;
	
	length = strlen(str);
	
	if (length == 0) 
	{
        return 3;  // empty string
    }
    if (length > 30) 
	{
        return 2;  // exceeds max length
    }

    for (int i = 0; i < length; i++) 
	{
        if (str[i] == '@') 
		{
            atCount++;
            atIndex = i;
        } else if (str[i] == '.') 
		{
            dotIndex = i;
        }
    }

    if (atCount != 1) 
	{
        return 0;  //must have exactly one @
    }
    if (dotIndex == -1 || atIndex > dotIndex) 
	{
        return 0;  // must have a '.' after '@'
    }
    if (atIndex == 0 || dotIndex == length - 1) 
	{
        return 0;  // '@' must not be first, '.' must not be last
    }
    if (dotIndex - atIndex == 1) 
	{
        return 0;  // no domain name between '@' and '.'
    }

    return 1;  
}

int isLeapYear(int year) 
{
    // Leap year: divisible by 4 AND (not divisible by 100 OR divisible by 400)
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int isValidDate (char *str)
{
	int i;
	int length = strlen(str);
	int maxDays;
	
	if (length != 10)
	{
		return 0;
	}
	
	for (i = 0; i < length; i++)
	{
		if (str[2] != '/' && str[5] != '/')
		{
			return 0;
		}
		else if (i != 2 && i != 5) 
		{
            if (str[i] < '0' || str[i] > '9') 
			{
                return 0; 
            }		
		}
	}
	
	int month = (str[0] - '0') * 10 + (str[1] - '0');
    int day = (str[3] - '0') * 10 + (str[4] - '0');
    int year = (str[6] - '0') * 1000 + (str[7] - '0') * 100 + (str[8] - '0') * 10 + (str[9] - '0');

    //month checking
    if (month < 1 || month > 12)
    {
		return 3;
	}

    //year checking
    if (year < 1900 || year > 2099) 
	{
		return 3;
	}

    //day checking
    
    if (month == 2) //Feb
	{
        maxDays = isLeapYear(year) ? 29 : 28;
    } 
	else if (month == 4 || month == 6 || month == 9 || month == 11) // Apr, Jun, Sep, Nov
	{ 
        maxDays = 30;
    } 
	else // Jan, Mar, May, Jul, Aug, Oct, Dec
	{
        maxDays = 31;
    }

    if (day < 1 || day > maxDays) 
	{
		return 3;
	}

    return 1;	
}


/* func for taking input and storing user info in the struct*/
// ADD UI 
User
verifyProfile()
{
    User p;
    char passwordConfirm[21];
    FILE *userFile = fopen("profiles.dat", "r");
    int validPassword = 0;

    do
    {
        printf("Enter Username: ");
        scanf("%50s", p.username);

        if (!(isAlphanumeric(p.username) && strlen(p.username) >= 8 && strlen(p.username) <= 50))
        {
            printf("Username must contain 8-50 alphanumeric characters!\n");
        }

    } while (!(isAlphanumeric(p.username) && strlen(p.username) >= 8 && strlen(p.username) <= 50));

    // Password input
    do
    {
    	do 
		{
	        printf("Enter Password: ");
	        scanf("%20s", p.pass);
	        
	        if (verifyPass(p.pass) && withinBounds(p.pass, 8, 20))
	        {
	            validPassword = 1;
	        }
	        else
	        {
	            printf("Password must be 8-20 characters and include at least 1 uppercase, 1 lowercase, 1 number, and 1 special character (!, @, #, $, %, &, *, .).\n");
	        }
    	} while (!validPassword);

        printf("Confirm Password: ");
        scanf("%20s", passwordConfirm);

        if (strcmp(p.pass, passwordConfirm) != 0)
        {
            printf("Passwords do not match. Try again.\n");
        }

    } while (strcmp(p.pass, passwordConfirm) != 0 || !(verifyPass(p.pass) && withinBounds(p.pass, 8, 20)));

    // Full Name input
    do
    {
        printf("Enter full name: ");
        scanf(" %[^\n]s", p.name);

        if (!(isAlphabetic(p.name) && withinBounds(p.name, 5, 80)))
        {
            printf("Full name must be 5-80 alphabetic characters.\n");
        }

    } while (!(isAlphabetic(p.name) && withinBounds(p.name, 5, 80)));

    // Email input
    do
    {
        printf("Enter email address: ");
        scanf("%30s", p.email);

        if (!verifyEmail(p.email))
        {
            printf("Invalid email address. Try again.\n");
        }

    } while (!verifyEmail(p.email));

    // Mobile number input
    do
    {
        printf("Enter phone number (11 digits, no spaces): ");
        scanf("%11s", p.number);

        int validation = verifyNumber(p.number);

	    if (validation == 0)
	    {
	        printf("Phone number must be exactly 11 digits and contain only numbers!\n");
	    }
	    else if (validation == 2)
	    {
	        printf("Phone number must start with '0'!\n");
	    }

	} while (verifyNumber(p.number) != 1);

    printf("Successful account creation!\n");

    // APPEND
    userFile = fopen("profiles.dat", "a");
    if (userFile != NULL)
    {
        fprintf(userFile, "%s\n%s\n%s\n%s\n%s\n", p.username, p.pass, p.name, p.email, p.number);
        fclose(userFile);
    }
    else
    {
        printf("Error saving user data.\n");
    }

    return p;
}


//User log-in once registration is done
int
verifyUser(User *p)
{
    char inputUser[51], inputPass[21];
    char storedUser[51], storedPass[21], storedName[81], storedEmail[31], storedNumber[12];
    int success = 0, attempts = 0;
    
    FILE *userFile = fopen("profiles.dat", "r");
    if (userFile == NULL)
    {
        printf("No user profiles found. Please register first.\n");
        return 0;
    }

    while (attempts < 3 && !success)
    {
        printf("Enter username: ");
        scanf("%50s", inputUser);

        printf("Enter password: ");
        scanf("%20s", inputPass);

        rewind(userFile); // Reset file position

        while (fscanf(userFile, "%50s\n%20s\n%80[^\n]\n%30s\n%11s\n", storedUser, storedPass, storedName, storedEmail, storedNumber) != EOF)
        {
            if (strcmp(storedUser, inputUser) == 0 && strcmp(storedPass, inputPass) == 0)
            {
                printf("\n\nWELCOME %s!\n", storedUser);
                strcpy(p->username, storedUser);
                strcpy(p->pass, storedPass);
                strcpy(p->name, storedName);
                strcpy(p->email, storedEmail);
                strcpy(p->number, storedNumber);
                success = 1;
                break;
            }
        }

        if (!success)
        {
            attempts++;
            printf("Incorrect username and/or password! Attempt %d / 3\n", attempts);
        }
    }

    fclose(userFile);

    if (!success)
    {
        printf("\n\nNumber of attempts reached. Press any key to exit!\n\n");
    }

    return success;
}

//Function for taking input for food
int verifyFood(foodLog *f)
{
    int success = 0;
    
    //Food Name
	while (success == 0)
    {
        printf("Enter Food Name: ");
        scanf(" %[^\n]s", f->name);

        if (isAlphanumeric(f->name) == 1 && withinBounds(f->name, 3, 50))
        {
            success = 1;
        }
        else
        {
            printf("Food name must only contain between 3 - 50 alphanumeric characters!\n");
        }
    }

    success = 0;
    
    //Food Type
    while (success == 0)
    {
        printf("Enter Food Type (a - appetizer, m - main course, d - dessert): ");
        scanf(" %c", &f->type);

        if (f->type == 'a' || f->type == 'm' || f->type == 'd')
        {
            success = 1;
        }
        else
        {
            printf("Food name must be an a (appetizer), m (main course), or d (dessert)!\n");
        }
    }
	
	success = 0;
	
	//Number of Times Eaten
	while (success == 0)
	{
		printf("Number of times eaten: ");
        scanf(" %d", &f->timesEaten);
        clearInputBuffer();
        
        if (f->timesEaten > 0)
        {
        	success = 1;
		}
		else
		{
			printf("Number of times eaten must be a positive integer!\n");
		}
	}
	
	success = 0;
	
	//Date First Tried
	while (success == 0)
	{
		printf("Date First Tried (mm/dd/yyyy): ");
        scanf("%10s", f->ftDate);
        
        if (isValidDate(f->ftDate) == 0)
        {
        	printf("Date must be in mm/dd/yyyy format and must only contain digits.\n");
		}
		else if (isValidDate(f->ftDate) == 3)
		{
			printf("Invalid date! Please try again.\n");
		}
		else if (isValidDate(f->ftDate) == 1)
		{
			success = 1;
		}
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
	}
	
	success = 0;
	
	//Location First Tried
	while (success == 0)
	{
		printf("Location First Tried: ");
        scanf(" %[^\n]s", f->ftPlace);	
		
		int placeLength = strlen(f->ftPlace);
		
		if (placeLength > 0 && placeLength <= 30)
		{
			success = 1;
		}
		else
		{
			printf("Invalid location! Maximum number of characters is 30.\n");
		}
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
	}
	
	success = 0;
	
	//Description
	while (success == 0)
	{
		printf("Description (overall impression of food): ");
        scanf(" %[^\n]s", f->desc);	
        
        int descLength = strlen(f->desc);
		
		if (descLength > 0 && descLength <= 300)
		{
			success = 1;
		}
		else
		{
			printf("Invalid description! Maximum number of characters is 300.\n");
		}
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
	}
	
	return 1;
}

int foodNameExists(const char *foodName)
{
    FILE *file = fopen("foodLogs.txt", "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so no duplicates
    }

    foodLog tempLog;
    while (fscanf(file, " %50s\n%c\n%d\n%10s\n%30s\n%300[^\n]\n",
                  tempLog.name, &tempLog.type, &tempLog.timesEaten,
                  tempLog.ftDate, tempLog.ftPlace, tempLog.desc) == 6)
    {
        if (strcmp(tempLog.name, foodName) == 0)
        {
            fclose(file);
            return 1; // Food name exists
        }
    }

    fclose(file);
    return 0; // Food name doesn't exist
}

void addFoodLog()
{
    foodLog newLog; // Declare the foodLog struct
    
    displayDivider();
    if (verifyFood(&newLog)) // Pass the address of the struct to verifyFood
    {
        if (foodNameExists(newLog.name))
        {
            printf("Food name '%s' already exists. Please enter a unique food name.\n", newLog.name);
            system("pause");
            return;
        }

        FILE *file = fopen("foodLogs.txt", "a");
        if (file == NULL)
        {
            printf("Error opening food logs file.\n");
            system("pause");
            return;
        }

        fprintf(file, "%s\n%c\n%d\n%s\n%s\n%s\n",
                newLog.name, newLog.type, newLog.timesEaten,
                newLog.ftDate, newLog.ftPlace, newLog.desc);

        fclose(file);
        printf("Food log added successfully!\n");
        system("pause");
    }
    else
    {
        printf("Food Log creation failed. Going back to main menu!\n");
        system("pause");
    }

}

//Function for taking input for recipe
int verifyRecipe(Recipe *r)
{
    int success = 0;
    
    //Recipe Name
	while (success == 0)
    {
        printf("Enter Recipe Name: ");
        scanf(" %[^\n]s", r->name);
        

        if (isAlphanumeric(r->name) == 1 && withinBounds(r->name, 3, 50))
        {
            success = 1;
        }
        else
        {
            printf("Recipe name must only contain between 3 - 50 alphanumeric characters!\n");
        }
    }

    success = 0;
    
    //Recipe Description
	while (success == 0)
	{
		printf("Recipe Description (overall impression): ");
        scanf(" %[^\n]s", r->desc);	
        
        int descLength = strlen(r->desc);
		
		if (descLength > 0 && descLength <= 160)
		{
			success = 1;
		}
		else
		{
			printf("Invalid description! Maximum number of characters is 160.\n");
		}
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
	}
	
	success = 0;
	//Time to Prepare
	while (success == 0)
	{
		printf("Time to prepare (in minutes): ");
        scanf(" %d", &r->prepTime);
        clearInputBuffer();
        
        if (r->prepTime > 0)
        {
        	success = 1;
		}
		else
		{
			printf("Minutes to prepare must be a positive integer!\n");
		}

	}
	
	success = 0;
	//Time to Cook
	while (success == 0)
	{
		printf("Time to cook (in minutes): ");
        scanf(" %d", &r->cookTime);
        clearInputBuffer();
        
        if (r->cookTime > 0)
        {
        	success = 1;
		}
		else
		{
			printf("Minutes to cook must be a positive integer!\n");
		}
	}
	
	success = 0;
	//Num of Ingredients
	while (success == 0)
	{
		printf("Number of ingredients needed: ");
        scanf(" %d", &r->numIng);
        clearInputBuffer();
        
        if (r->numIng > 0 && r->numIng < MAX_INGREDIENTS)
        {
        	success = 1;
		}
		else
		{
			printf("Number of ingredients must be a positive integer!\n");
		}
	}
	
	success = 0;
	//List of Ingredients
	while (success == 0)
	{
		int i;
		
		for (i = 0; i < r->numIng; i++)
		{
			printf("Ingredient #%d (max 80 characters): ", i + 1);
	        scanf(" %[^\n]s", r->ingredients[i]);
			success = 1;			
		}	
		void clearInputBuffer();
	}
	
	success = 0;
	//Num of Instructions
	while (success == 0)
	{
		printf("Number of instructions needed: ");
        scanf(" %d", &r->numInstructions);
        clearInputBuffer();
        
        if (r->numInstructions > 0 && r->numInstructions < MAX_INSTRUCTIONS)
        {
        	success = 1;
		}
		else
		{
			printf("Number of instructions must be a positive integer!\n");
		}
	}
	
	success = 0;
	//List of Instructions
	while (success == 0)
	{
		int i;
		
		for (i = 0; i < r->numInstructions; i++)
		{
			printf("Instruction #%d (max 20 characters): ", i + 1);
	        scanf(" %[^\n]s", r->instructions[i]);
			success = 1;			
		}	
		void clearInputBuffer();
	}
	
	return 1;
}

int recipeNameExists(const char *recipeName)
{
	int i;
	
    FILE *file = fopen("Recipes.txt", "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so no duplicates
    }

    Recipe tempRecipe;
    while (fscanf(file, " %50s\n%160[^\n]\n%d\n%d\n%d\n",
                  tempRecipe.name, tempRecipe.desc, &tempRecipe.prepTime,
                  &tempRecipe.cookTime, &tempRecipe.numIng) == 5) 
	{
        for (i = 0; i < tempRecipe.numIng; i++) 
		{
            fscanf(file, " %80[^\n]\n", tempRecipe.ingredients[i]);
        }
        fscanf(file, "%d\n", &tempRecipe.numInstructions);
        
        for(i = 0; i < tempRecipe.numInstructions; i++) 
		{
            fscanf(file, " %100[^\n]\n", tempRecipe.instructions[i]);
        }

        if (strcmp(tempRecipe.name, recipeName) == 0) 
		{
            fclose(file);
            return 1; // Food name exists
        }
    }


    fclose(file);
    return 0; // Food name doesn't exist
}

void addRecipe()
{
    Recipe newRecipe; // Declare the foodLog struct
    
    displayDivider();
    if (verifyRecipe(&newRecipe)) // Pass the address of the struct to verifyFood
    {
        if (recipeNameExists(newRecipe.name))
        {
            printf("Recipe name '%s' already exists. Please enter a unique food name.\n", newRecipe.name);
            system("pause");
            return;
        }

        FILE *file = fopen("Recipes.txt", "a");
        if (file == NULL)
        {
            printf("Error opening recipes file.\n");
            return;
        }

        fprintf(file, "%s\n%s\n%d\n%d\n%d\n",
                newRecipe.name, newRecipe.desc, newRecipe.prepTime,
                newRecipe.cookTime, newRecipe.numIng);

        for(int i = 0; i < newRecipe.numIng; i++)
		{
            fprintf(file, "%s\n", newRecipe.ingredients[i]);
        }

        fprintf(file,"%d\n", newRecipe.numInstructions);

        for(int i = 0; i < newRecipe.numInstructions; i++)
		{
            fprintf(file, "%s\n", newRecipe.instructions[i]);
        }

        fclose(file);
        printf("Recipe added successfully!\n");
        system("pause");
    }
    else
    {
        printf("Recipe creation failed. Going back to main menu!\n");
        system("pause");
    }

}

int displayMenu ()
{
	int choice;
	int validInput;
	
	do
	{
		system("cls");
		
	    printf("Foodie App Menu\n");
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
	    
	    validInput = scanf("%d", &choice);
	
	    if (validInput != 1 || choice < 1 || choice > 15)
	    {
	        printf("Invalid input. Please enter a number between 1 and 15.\n");
	
	        while (getchar() != '\n');
			system("pause");
	    }

    } while (validInput != 1 || choice < 1 || choice > 15);

    return choice;
}

void displayFoodLog(const foodLog *log) 
{
    printf("Food Name: %s\n", log->name);
    printf("Type: %c\n", log->type);
    printf("Times Eaten: %d\n", log->timesEaten);
    printf("Date: %s\n", log->ftDate);
    printf("Place: %s\n", log->ftPlace);
    printf("Description: %s\n", log->desc);
}

void modifyFoodLog() 
{
    FILE *file = fopen("foodLogs.txt", "r");
    
    if (file == NULL) 
	{
        printf("There are no food logs to modify.\n");
        Sleep(1000);
        return;
    }

    // Check if file is empty
    fpos_t start;
    fgetpos(file, &start);
    fscanf(file, "%*c");
    
    if (feof(file)) 
	{
        printf("There are no food logs to modify.\n");
        fclose(file);
        Sleep(1000);
        return;
    }
    rewind(file);

    FILE *temp = fopen("temp.txt", "w");
    char foodName[51];
    printf("Enter food name to modify: ");
    scanf("%50s", foodName);
    
    clearInputBuffer();

    foodLog log; 
	foodLog tempLog;

    int found = 0;
    while (fscanf(file, "%50[^\n]\n%c\n%d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  log.name, &log.type, &log.timesEaten, log.ftDate, log.ftPlace, log.desc) == 6) {
        if (strcmp(log.name, foodName) == 0) {
            found = 1;
            displayDivider();
            printf("Current:\n");
            displayFoodLog(&log);

            tempLog = log;
            
            displayDivider();
            verifyFood(&tempLog);

            char confirm;
            printf("Confirm changes? (Y/N): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                fprintf(temp, "%s\n%c\n%d\n%s\n%s\n%s\n",
                        tempLog.name, tempLog.type, tempLog.timesEaten, tempLog.ftDate, tempLog.ftPlace, tempLog.desc);
                printf("Food log modified successfully.\n");
            } else {
                fprintf(temp, "%s\n%c\n%d\n%s\n%s\n%s\n",
                        log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
                printf("Modification cancelled.\n");
            }

        } else {
            fprintf(temp, "%s\n%c\n%d\n%s\n%s\n%s\n",
                    log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
        }
    }
    fclose(file);
    fclose(temp);
    remove("foodLogs.txt");
    rename("temp.txt", "foodLogs.txt");
    
    if (!found) 
	{
		printf("Food log not found.\n");	
	}
    Sleep(1000);
}

void displayRecipe(const Recipe *recipe) 
{
    printf("Food Name: %s\n", recipe->name);
    printf("Description: %s\n", recipe->desc);
    printf("Preparation Time: %d min/s\n", recipe->prepTime);
    printf("Cooking Time: %d min/s\n", recipe->cookTime);
    printf("Number of Ingredients: %d\n", recipe->numIng);
    printf("List of Ingredients:\n");
    
    for (int i = 0; i < recipe->numIng; i++) 
	{
        printf("- %s\n", recipe->ingredients[i]);
    }
    
    printf("Number of Instructions: %d\n", recipe->numInstructions);
    printf("Instructions:\n");
    
    for (int i = 0; i < recipe->numInstructions; i++) 
	{
        printf("%d. %s\n",i+1, recipe->instructions[i]);
    }
}

void modifyRecipe() 
{
    FILE *file = fopen("Recipes.txt", "r");
    if (file == NULL) 
	{
        printf("There are no recipes to modify.\n");
        Sleep(1000);
        return;
    }

    // Check if file is empty
    fpos_t start;
    fgetpos(file, &start);
    fscanf(file, "%*c");
    
    if (feof(file)) 
	{
        printf("There are no recipes to modify.\n");
        fclose(file);
        Sleep(1000);
        return;
    }
    
    rewind(file);

    FILE *temp = fopen("temp.txt", "w");
    char recipeName[51];
    printf("Enter recipe name to modify: ");
    scanf("%50s", recipeName);
    clearInputBuffer();

    Recipe recipe;
    Recipe tempRecipe;
    
    int i, found = 0;

    while (fscanf(file, "%50[^\n]\n%160[^\n]\n%d\n%d\n%d\n",
            recipe.name, recipe.desc, &recipe.prepTime, &recipe.cookTime, &recipe.numIng) == 5) 
	{
        for (i = 0; i < recipe.numIng; i++) 
		{
            fscanf(file, "%80[^\n]\n", recipe.ingredients[i]);
        }

        fscanf(file, "%d\n", &recipe.numInstructions);

        for (i = 0; i < recipe.numInstructions; i++) 
		{
            fscanf(file, "%100[^\n]\n", recipe.instructions[i]);
        }

        if (strcmp(recipe.name, recipeName) == 0) 
		{
            found = 1;
            displayDivider();
            printf("\nCurrent:\n");
            displayRecipe(&recipe);

            tempRecipe = recipe;
            
            displayDivider();
            verifyRecipe(&tempRecipe);

            char confirm;
            printf("Confirm changes? (Y/N): ");
            scanf(" %c", &confirm);
            clearInputBuffer();

            if (confirm == 'y' || confirm == 'Y') 
			{
                fprintf(temp, "%s\n%s\n%d\n%d\n%d\n",
                        tempRecipe.name, tempRecipe.desc, tempRecipe.prepTime, tempRecipe.cookTime, tempRecipe.numIng);

                for (i = 0; i < tempRecipe.numIng; i++) 
				{
                    fprintf(temp, "%s\n", tempRecipe.ingredients[i]);
                }

                fprintf(temp, "%d\n", tempRecipe.numInstructions);

                for (i = 0; i < tempRecipe.numInstructions; i++) 
				{
                    fprintf(temp, "%s\n", tempRecipe.instructions[i]);
                }

                printf("Recipe modified successfully.\n");
            } 
			else 
			{
                fprintf(temp, "%s\n%s\n%d\n%d\n%d\n",
                        recipe.name, recipe.desc, recipe.prepTime, recipe.cookTime, recipe.numIng);

                for (i = 0; i < recipe.numIng; i++) 
				{
                    fprintf(temp, "%s\n", recipe.ingredients[i]);
                }

                fprintf(temp, "%d\n", recipe.numInstructions);

                for (i = 0; i < recipe.numInstructions; i++) 
				{
                    fprintf(temp, "%s\n", recipe.instructions[i]);
                }
                printf("Modification cancelled.\n");
            }
        } 
		else 
		{
            fprintf(temp, "%s\n%s\n%d\n%d\n%d\n",
                    recipe.name, recipe.desc, recipe.prepTime, recipe.cookTime, recipe.numIng);

            for (i = 0; i < recipe.numIng; i++) 
			{
                fprintf(temp, "%s\n", recipe.ingredients[i]);
            }

            fprintf(temp, "%d\n", recipe.numInstructions);

            for (i = 0; i < recipe.numInstructions; i++) 
			{
                fprintf(temp, "%s\n", recipe.instructions[i]);
            }
        }
    }

    fclose(file);
    fclose(temp);
    remove("Recipes.txt");
    rename("temp.txt", "Recipes.txt");
    if (!found) 
	{
		printf("Recipe not found.\n");	
	}
    Sleep(1000);
}

void deleteFoodLog() 
{
    FILE *file = fopen("foodLogs.txt", "r");
    
    displayDivider();
    if (file == NULL) 
	{
        printf("There are no food logs to delete.\n");
        Sleep(1000);
        system("pause");
        return;
    }

    fpos_t start;
    fgetpos(file, &start); 
    fscanf(file, "%*c"); 
    
    if (feof(file)) 
	{ 
        printf("There are no food logs to delete.\n");
        fclose(file);
        Sleep(1000);
        system("pause");
        return;
    }
    rewind(file); 

    FILE *temp = fopen("temp.txt", "w");
    char foodName[51];
    printf("Enter food name to delete: ");
    scanf("%50s", foodName);
    
    clearInputBuffer();

    foodLog log;
    int found = 0;

    while (fscanf(file, "%50[^\n]\n%c\n%d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
        log.name, &log.type, &log.timesEaten, log.ftDate, log.ftPlace, log.desc) == 6) 
	{
        if (strcmp(log.name, foodName) == 0) 
		{
            found = 1;
            printf("Food Log to Delete:\n\n");
            displayFoodLog(&log);

            char confirm;
            printf("Confirm deletion? (Y/N): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') 
			{
				printf("Food log deletion process completed.\n");
            } 
			else
			{
                fprintf(temp, "%s\n%c\n%d\n%s\n%s\n%s\n",
                log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
                printf("Deletion cancelled. Food log retained.\n");
            }
        }
		else 
		{
            fprintf(temp, "%s\n%c\n%d\n%s\n%s\n%s\n",
            log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
        }
    }

    fclose(file);
    fclose(temp);
    remove("foodLogs.txt");
    rename("temp.txt", "foodLogs.txt");

    if (found) 
	{
        system("pause");
        FILE *check = fopen("foodLogs.txt", "r");
        if (check != NULL) {
            fscanf(check, "%*c");

            if (feof(check)) {
                remove("foodLogs.txt");
            }

            fclose(check);
        }
    } 
	else 
	{
        printf("Food log not found.\n");
        system("pause");
    }

    Sleep(1000);
}

void deleteRecipe() 
{
	displayDivider();
    FILE *file = fopen("Recipes.txt", "r");
    if (file == NULL) 
	{
        printf("There are no recipes to delete.\n");
        Sleep(1000);
        return;
    }

    fpos_t start;
    fgetpos(file, &start); 
    fscanf(file, "%*c");  

    
    if (feof(file)) 
	{  
        printf("There are no recipes to delete.\n");
        fclose(file);
        Sleep(1000);
        return;
    }
    
    rewind(file); 

    FILE *temp = fopen("temp.txt", "w");
    char recipeName[51];
    printf("Enter recipe name to delete: ");
    scanf("%50s", recipeName);
    
    clearInputBuffer();

    Recipe recipe;
    int i, found = 0;
    
    while (fscanf(file, "%50[^\n]\n%160[^\n]\n%d\n%d\n%d\n",
                  recipe.name, recipe.desc, &recipe.prepTime, &recipe.cookTime, &recipe.numIng) == 5) {
        for (i = 0; i < recipe.numIng; i++) 
		{
            fscanf(file, "%80[^\n]\n", recipe.ingredients[i]);
        }
        
        fscanf(file, "%d\n", &recipe.numInstructions);
        
        for (i = 0; i < recipe.numInstructions; i++) 
		{
            fscanf(file, "%100[^\n]\n", recipe.instructions[i]);
        }

        if (strcmp(recipe.name, recipeName) == 0) 
		{
            found = 1;
            printf("Recipe to Delete:\n\n");
            displayRecipe(&recipe);

            char confirm;
            printf("Confirm deletion? (Y/N): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') 
			{
 		       	printf("Recipe deleted successfully.\n");
            } 
			else 
			{
                fprintf(temp, "%s\n%s\n%d\n%d\n%d\n",
                        recipe.name, recipe.desc, recipe.prepTime, recipe.cookTime, recipe.numIng);

                for (i = 0; i < recipe.numIng; i++) 
				{
                    fprintf(temp, "%s\n", recipe.ingredients[i]);
                }

                fprintf(temp, "%d\n", recipe.numInstructions);

                for (i = 0; i < recipe.numInstructions; i++) 
				{
                    fprintf(temp, "%s\n", recipe.instructions[i]);
                }
                printf("Deletion cancelled. Recipe retained.\n"); 
            }
        } 
		else 
		{

            fprintf(temp, "%s\n%s\n%d\n%d\n%d\n",
                    recipe.name, recipe.desc, recipe.prepTime, recipe.cookTime, recipe.numIng);

            for (i = 0; i < recipe.numIng; i++) 
			{
                fprintf(temp, "%s\n", recipe.ingredients[i]);
            }

            fprintf(temp, "%d\n", recipe.numInstructions);

            for (i = 0; i < recipe.numInstructions; i++) 
			{
                fprintf(temp, "%s\n", recipe.instructions[i]);
            }
        }
    }
    
    fclose(file);
    fclose(temp);
    remove("Recipes.txt");
    rename("temp.txt", "Recipes.txt");
    
    if (found) 
	{
        system("pause");
		FILE *check = fopen("Recipes.txt", "r");
        
        if (check != NULL) 
		{
            fscanf(check, "%*c");
            
            if (feof(check)) 
			{
                remove("Recipes.txt");
            }
            
            fclose(check);
        }
    } 
	else 
	{
        printf("Recipe not found.\n");
        system("pause");
    }
    
    Sleep(1000);
}

void displayUser(User *profile) 
{
	FILE *file = fopen("profiles.dat", "r");
	
	displayDivider();
    printf("Username: %s\nName: %s\nEmail: %s\nNumber: %s\n",
           profile->username, profile->name, profile->email, profile->number);
    system("pause");

    clearInputBuffer();
    fclose(file);
}

int compareDates(const char *date1, const char *date2) 
{
    int year1, month1, day1, year2, month2, day2;

    sscanf(date1, "%d/%d/%d", &month1, &day1, &year1);
    sscanf(date2, "%d/%d/%d", &month2, &day2, &year2);
    
    printf("Comparing: %s and %s\n", date1, date2);
    printf("Date 1: %d/%d/%d, Date 2: %d/%d/%d\n", month1, day1, year1, month2, day2, year2);

    if (year1 != year2) {
        return year1 - year2;
    }
    if (month1 != month2) {
        return month1 - month2;
    }
    return day1 - day2;
}

void displayAllFoodLogs() 
{
    FILE *foodFile = fopen("foodLogs.txt", "r");
    
    if (foodFile == NULL) 
	{
        printf("Error opening food logs file.\n");
        return;
    }

    foodLog logs[50];
    int logCount = 0;

    while (fscanf(foodFile, "%50[^\n]\n%c\n%d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  logs[logCount].name, &logs[logCount].type, &logs[logCount].timesEaten,
                  logs[logCount].ftDate, logs[logCount].ftPlace, logs[logCount].desc) == 6) {
        logCount++;
    }

    fclose(foodFile);

    if (logCount > 0) 
	{
        for (int i = 0; i < logCount - 1; i++) 
		{
            for (int j = 0; j < logCount - i - 1; j++) 
			{
                if (compareDates(logs[j].ftDate, logs[j + 1].ftDate) < 0)
				{
                    foodLog temp = logs[j];
                    logs[j] = logs[j + 1];
                    logs[j + 1] = temp;
                }
            }
        }

        printf("\nALL FOOD LOGS (Descending Order):\n");
        for (int i = 0; i < logCount; i++) 
		{
			printf("Food Log #%d\n", i+1);
            displayFoodLog(&logs[i]);
            printf("\n");
        }
    } else {
        printf("No food logs found.\n");
    }
    system("pause");
}


void displayAllRecipes() 
{
    FILE *recipeFile = fopen("Recipes.txt", "r");
    
    if (recipeFile == NULL) 
	{
        printf("Error opening recipes file.\n");
        return;
    }

    Recipe recipes[20];
    int recipeCount = 0;

    while (fscanf(recipeFile, "%50[^\n]\n%160[^\n]\n%d\n%d\n%d\n",
                  recipes[recipeCount].name, recipes[recipeCount].desc, &recipes[recipeCount].prepTime, &recipes[recipeCount].cookTime, &recipes[recipeCount].numIng) == 5) 
	{
        for (int i = 0; i < recipes[recipeCount].numIng; i++) 
		{
            fscanf(recipeFile, "%80[^\n]\n", recipes[recipeCount].ingredients[i]);
        }
        
        fscanf(recipeFile, "%d\n", &recipes[recipeCount].numInstructions);
        
        for (int i = 0; i < recipes[recipeCount].numInstructions; i++) 
		{
            fscanf(recipeFile, "%100[^\n]\n", recipes[recipeCount].instructions[i]);
        }
        recipeCount++;
    }

    fclose(recipeFile);

    if (recipeCount > 0) 
	{
        for (int i = 0; i < recipeCount - 1; i++) 
		{
            for (int j = 0; j < recipeCount - i - 1; j++) 
			{
                if (strcmp(recipes[j].name, recipes[j + 1].name) > 0)
				{
                    Recipe temp = recipes[j];
                    recipes[j] = recipes[j + 1];
                    recipes[j + 1] = temp;
                }
            }
        }

        printf("\nALL RECIPES (Ascending Order):\n");
        for (int i = 0; i < recipeCount; i++) 
		{
			printf("Recipe #%d\n", i+1);
            displayRecipe(&recipes[i]);
            printf("\n");
        }
    } else {
        printf("No recipes found.\n");
    }
    system("pause");
}

int findUser(const char *username, User *foundUser) 
{
    FILE *userFile = fopen("profiles.dat", "r");
    if (userFile == NULL) 
	{
        return 0;
    }

    User tempUser;
    while (fscanf(userFile, "%50[^\n]\n%50[^\n]\n%100[^\n]\n%100[^\n]\n%20[^\n]\n",
                  tempUser.username, tempUser.pass, tempUser.name, tempUser.email, tempUser.number) == 5) 
	{
		if (strcmp(tempUser.username, username) == 0) 
		{
            *foundUser = tempUser;
            fclose(userFile);
            return 1;
        }
    }

    fclose(userFile);
    return 0;
}


void displayAllByUsername(User *profile) 
{
    char username[MAX_USERNAME_LENGTH];
    User user;

    printf("Enter username to search: ");
    scanf("%50s", username);
    clearInputBuffer();

    if (findUser(username, &user)) 
	{
        if (profile != NULL && strcmp(profile->username, username) == 0) 
		{
            displayUser(&user);
        } 
		else 
		{
            printf("Full Name: %s\n", user.name);
            printf("Username: %s\n", user.username);
        }

        FILE *foodFile = fopen("foodLogs.txt", "r");
        FILE *recipeFile = fopen("Recipes.txt", "r");
        int found = 0;

        if (foodFile != NULL) 
		{
            printf("\nFOOD LOGS FOR %s\n", user.username);
            foodLog log;
            char fileUsername[MAX_USERNAME_LENGTH];

            while (fscanf(foodFile, "%50[^\n]\n%c\n%d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                    log.name, &log.type, &log.timesEaten, log.ftDate, log.ftPlace, log.desc) == 6) 
			{
                    displayFoodLog(&log);
                    found = 1;
            }
            fclose(foodFile);
        }

        if (recipeFile != NULL) 
		{
            printf("\nRECIPES FOR %s\n", user.username);
            Recipe recipe;
            char recipeUsername[MAX_USERNAME_LENGTH];
            int i;

            while (fscanf(recipeFile, "%50[^\n]\n%160[^\n]\n%d\n%d\n%d\n",
                recipe.name, recipe.desc, &recipe.prepTime, &recipe.cookTime, &recipe.numIng) == 5) 
			{

                for (i = 0; i < recipe.numIng; i++) 
				{
                    fscanf(recipeFile, "%80[^\n]\n", recipe.ingredients[i]);
                }

                fscanf(recipeFile, "%d\n", &recipe.numInstructions);

                for (i = 0; i < recipe.numInstructions; i++) 
				{
                    fscanf(recipeFile, "%100[^\n]\n", recipe.instructions[i]);
                }

                    displayRecipe(&recipe);
                    found = 1;
            }
            fclose(recipeFile);
        }

        if (!found) 
		{
            printf("No entries found for %s.\n", user.username);
        }

        system("pause");
    } 
	else 
	{
        printf("User '%s' not found.\n", username);
        system("pause");
    }
    clearInputBuffer();
}

void searchFoodLog() 
{
    FILE *foodFile = fopen("foodLogs.txt", "r");
    char searchName[51];
    int found = 0;
    
    displayDivider();
    if (foodFile == NULL) 
	{
        printf("Error opening food logs file.\n");
        printf("Press any key to continue and go back to main menu...\n");
    	getchar();
    	getchar();
        return;
    }

    printf("Enter the food name to search: ");
    scanf(" %50[^\n]", searchName);

    foodLog log;
    
    while (fscanf(foodFile, "%50[^\n]\n%c\n%d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
            log.name, &log.type, &log.timesEaten, log.ftDate, log.ftPlace, log.desc) == 6) 
	{
        if (strcmp(log.name, searchName) == 0) 
		{
            displayFoodLog(&log);
            found = 1;
        }
    }

    fclose(foodFile);

    if (!found) 
	{
        printf("No such food has been logged.\n");
    }

    printf("Press any key to continue and go back to main menu...\n");
    getchar();
    getchar();
}

void searchRecipe() 
{
    FILE *recipeFile = fopen("Recipes.txt", "r");
    
    displayDivider();
    if (recipeFile == NULL) 
	{
        printf("Error opening recipes file.\n");
        printf("Press any key to continue and go back to main menu...\n");
    	getchar();
    	getchar();
        return;
    }

    char searchName[51];
    printf("Enter the recipe name to search: ");
    scanf(" %50[^\n]", searchName);

    Recipe recipe;
    int found = 0;

    while (fscanf(recipeFile, "%50[^\n]\n%160[^\n]\n%d\n%d\n%d\n",
                recipe.name, recipe.desc, &recipe.prepTime, &recipe.cookTime, &recipe.numIng) == 5) 
	{
		for (int i = 0; i < recipe.numIng; i++) 
		{
            fscanf(recipeFile, "%80[^\n]\n", recipe.ingredients[i]);
        }

        fscanf(recipeFile, "%d\n", &recipe.numInstructions);

        for (int i = 0; i < recipe.numInstructions; i++) 
		{
            fscanf(recipeFile, "%100[^\n]\n", recipe.instructions[i]);
        }
        
        if (strcmp(recipe.name, searchName) == 0) 
		{
			displayRecipe(&recipe);
            found = 1;
        }    
    }

    fclose(recipeFile);

    if (!found) {
        printf("No such recipe has been logged.\n");
    }

    printf("Press any key to continue and go back to main menu...\n");
    getchar();
    getchar();
}


void showLoadingBar() 
{
    printf("\nLogging in . . .");
    for (int i = 0; i <= 100; i += 25) 
	{
        printf("\rLogging in . . . [%3d%%] ", i);
        usleep(350000);
    }
    printf("\n");
}
