#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_INGREDIENTS 21
#define MAX_INSTRUCTIONS 21
#define MAX_USERNAME_LENGTH 51
#define MAX_FILENAME 30

/* FOOD LOG STRUCT */
typedef struct 
{
    char name[51];
    char username[51];
    char fullname[81];
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
    char username[51];
    char fullname[81];
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
	printf("\n\n=============================================\n");
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
User
verifyProfile()
{
    User p;
    char passwordConfirm[21];
    FILE *userFile = fopen("profiles.dat", "r");
    int validPassword = 0;
    int passwordMatch = 0;
    
    system("cls");
    printf("==============================================\n");
    printf("|                REGISTRATION                |\n");
    printf("==============================================\n");

    do
    {
        printf("Enter Username: ");
        scanf("%50s", p.username);
        clearInputBuffer();

        if (!(isAlphanumeric(p.username) && strlen(p.username) >= 8 && strlen(p.username) <= 50))
        {
            printf("Username must contain 8-50 alphanumeric characters!\n");
        }

    } while (!(isAlphanumeric(p.username) && strlen(p.username) >= 8 && strlen(p.username) <= 50));

    // Password input
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
	
	do
	{
	    printf("Confirm Password: ");
	    scanf("%20s", passwordConfirm);
	
	    if (strcmp(p.pass, passwordConfirm) == 0)
	    {
	        passwordMatch = 1;
	    }
	    else
	    {
	        printf("Passwords do not match. Try again.\n");
	    }
	} while (!passwordMatch);

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
        clearInputBuffer();

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
        printf("\n============================================\n");
        printf("|          NO USER PROFILES FOUND            |\n");
        printf("|          Please register first.            |\n");
        printf("==============================================\n\n");
        return 0;
    }

    while (attempts < 3 && !success)
    {
	if (attempts == 0)
	{
		system("cls");
	}	
        printf("==============================================\n");
        printf("|                  LOGIN                     |\n");
        printf("==============================================\n");

        printf("| Username: ");
        scanf("%50s", inputUser);
        clearInputBuffer();

        printf("| Password: ");
        scanf("%20s", inputPass);
        clearInputBuffer();

        rewind(userFile); // Reset file position

        while (fscanf(userFile, "%50s\n%20s\n%80[^\n]\n%30s\n%11s\n", storedUser, storedPass, storedName, storedEmail, storedNumber) != EOF)
        {
            if (strcmp(storedUser, inputUser) == 0 && strcmp(storedPass, inputPass) == 0)
            {
                printf("==============================================\n");
                printf("               WELCOME, %s!                 \n", storedUser);
                printf("==============================================\n\n");
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
            printf("\n==============================================\n");
            printf("|     Incorrect username and/or password!    |\n");
            printf("|       Attempt %d / 3                        |\n", attempts);
            printf("==============================================\n\n");
        }
    }

    fclose(userFile);

    if (!success)
    {
        printf("==============================================\n");
        printf("|    MAXIMUM ATTEMPTS REACHED                |\n");
        printf("|    Please try again later.                 |\n");
        printf("==============================================\n");
        printf("Press ENTER to exit.");
    }

    return success;
}

// Function to check if the food name is valid
int isValidFoodName(const char *str) 
{
    int len = strlen(str);
    
    if (len < 3 || len > 50) 
	{
        return 0; 
    }
    
    for (int i = 0; i < len; i++) 
	{
        if (!isalnum(str[i]) && str[i] != ' ') 
		{
            return 0; 
        }
    }

    for (int i = 0; i < len - 1; i++) 
	{
        if (str[i] == ' ' && str[i + 1] == ' ') 
		{
            return 0;
        }
    }

    return 1; // Valid food name
}

int foodNameExists(const char *foodName, const char *username)
{
    FILE *file = fopen("foodLogs.txt", "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so no duplicates
    }

    foodLog tempLog;
    while (fscanf(file, "%50[^\n]\n%50s %[^\n]\n%c %d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  tempLog.name, tempLog.username, tempLog.fullname,
				  &tempLog.type, &tempLog.timesEaten,
                  tempLog.ftDate, tempLog.ftPlace, tempLog.desc) == 8)
    {
        if (strcmp(tempLog.name, foodName) == 0 && strcmp(tempLog.username, username) == 0)
        {
            fclose(file);
            return 1; // Food name exists
        }
    }

    fclose(file);
    return 0; // Food name doesn't exist
}

//Function for taking input for food
int verifyFood(foodLog *f, const char *originalName)
{
    int success = 0;
    
    //Food Name
	while (success == 0)
    {
    	printf("==============================================\n");
        printf("|                FOOD LOG ENTRY              |\n");
        printf("==============================================\n");
        printf("| Enter Food Name: ");
        scanf(" %[^\n]", f->name);
		
		if (!isValidFoodName(f->name))
        {
            printf("|--------------------------------------------|\n");
            printf("| Food name must be 3 - 50 alphanumeric      |\n");
            printf("| characters and may contain single spaces.  |\n");
            printf("|--------------------------------------------|\n\n");
        }
        else if (strcmp(f->name, originalName) != 0 && foodNameExists(f->name, f->username))
        {
            printf("|-----------------------------------------------|\n");
            printf("| Food name '%s' already exists!            |\n", f->name);
            printf("| Please enter a unique food name.              |\n");
            printf("|-----------------------------------------------|\n\n");
            sleep(2);
            system("cls");
        }
        else
        {
            success = 1;
        }
    }

    success = 0;
    
    //Food Type
    while (success == 0)
    {
        printf("| Enter Food Type (a - appetizer, m - main course, d - dessert): ");
        scanf(" %c", &f->type);

        if (f->type == 'a' || f->type == 'm' || f->type == 'd')
        {
            success = 1;
        }
        else
        {
            printf("|-----------------------------------------------------|\n");
            printf("| Invalid choice! Food name must be 'a', 'm', or 'd'. |\n");
            printf("|-----------------------------------------------------|\n\n");
        }
        clearInputBuffer();
    }
	
	success = 0;
	
	//Number of Times Eaten
	while (success == 0)
	{
		printf("| Number of times eaten: ");
		 
        if (scanf("%d", &f->timesEaten) != 1)
    	{
	        printf("|--------------------------------------------|\n");
	        printf("| Invalid input! Please enter a valid number. |\n");
	        printf("|--------------------------------------------|\n\n");
	        clearInputBuffer();
    	}
	    else if (f->timesEaten > 0)
	    {
	        success = 1;
	    }
	    else
	    {
	        printf("|--------------------------------------------|\n");
	        printf("| Number of times eaten must be a positive integer! |\n");
	        printf("|--------------------------------------------|\n\n");
	        clearInputBuffer();
	    }
	}
	success = 0;
	
	//Date First Tried
	while (success == 0)
	{
		printf("| Date First Tried (mm/dd/yyyy): ");
        scanf(" %10s", f->ftDate);
        
        int dateValidation = isValidDate(f->ftDate);
        if (dateValidation == 1) 
		{
            success = 1;
        } 
		else 
		{
            printf("|--------------------------------------------|\n");
            if (dateValidation == 0)
            {
                printf("| Date must be in mm/dd/yyyy format.\n");
            }
            else
            {
                printf("| Invalid date! Please try again.\n");
            	printf("|--------------------------------------------|\n\n");
            }
            clearInputBuffer();
        }
        clearInputBuffer();
	}
	
	success = 0;
	
	//Location First Tried
	while (success == 0)
	{
		printf("| Location First Tried: ");
        scanf(" %[^\n]s", f->ftPlace);	
		
		int placeLength = strlen(f->ftPlace);
		
		if (placeLength > 0 && placeLength <= 30)
		{
			success = 1;
		}
		else
		{
			printf("|--------------------------------------------|\n");
            printf("| Invalid location! Maximum number of characters is 30.\n");
            printf("|--------------------------------------------|\n\n");
		}
	}
	
	success = 0;
	
	//Description
	while (success == 0)
	{
		printf("| Description (overall impression of food): ");
        scanf(" %[^\n]s", f->desc);	
        
        int descLength = strlen(f->desc);
		
		if (descLength > 0 && descLength <= 300)
		{
			success = 1;
		}
		else
		{
			printf("|--------------------------------------------|\n");
            printf("| Invalid description! Maximum number of characters is 300.\n");
            printf("|--------------------------------------------|\n\n");
		}
		
	}
	return 1;
}

void addFoodLog(User *profile)
{
    foodLog newLog;
    
    if (verifyFood(&newLog, "")) 
    {
        FILE *file = fopen("foodLogs.txt", "a");
        if (file == NULL)
        {
            printf("|-------------------------------------------------|\n");
            printf("|     Error: Unable to open food logs file.       |\n");
            printf("|-------------------------------------------------|\n");
            system("pause");
            return;
        }

        fprintf(file, "%s\n%s %s\n%c %d\n%s\n%s\n%s\n",
                newLog.name, profile->username, profile->name, 
                newLog.type, newLog.timesEaten,
                newLog.ftDate, newLog.ftPlace, newLog.desc);

        fclose(file);
        printf("==============================================\n");
    	printf("|       FOOD LOG SUCCESSFULLY RECORDED!      |\n");
    	printf("==============================================\n");
        system("pause");
    }
    else
    {
        printf("|--------------------------------------------|\n");
        printf("|        Food Log creation failed!           |\n");
        printf("|         Returning to main menu.            |\n");
        printf("|--------------------------------------------|\n");
        system("pause");
    }

}

int recipeNameExists(const char *recipeName, const char *username)
{
	int i;
	
    FILE *file = fopen("Recipes.txt", "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so no duplicates
    }

    Recipe tempRecipe;
    while (fscanf(file, "%50[^\n]\n%50s %[^\n]\n%160[^\n]\n%d %d\n%d\n",
                  tempRecipe.name, tempRecipe.username, tempRecipe.fullname,
				  tempRecipe.desc, &tempRecipe.prepTime,
                  &tempRecipe.cookTime, &tempRecipe.numIng) == 7) 
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

//Function for taking input for recipe
int verifyRecipe(Recipe *r, const char *originalName)
{
    int success = 0;
    
    //Recipe Name
	while (success == 0)
    {
        printf("==============================================\n");
        printf("|              RECIPE CREATION               |\n");
        printf("==============================================\n");
        printf("| Enter Recipe Name: ");
        scanf(" %[^\n]s", r->name);

        if (!isValidFoodName(r->name))
        {
            printf("|--------------------------------------------|\n");
            printf("| Recipe name must contain 3 - 50 alphanumeric |\n");
            printf("| characters and may contain single spaces.   |\n");
            printf("|--------------------------------------------|\n\n");
        }
        else if (strcmp(r->name, originalName) != 0 && recipeNameExists(r->name,r->username))
        {
            printf("|-----------------------------------------------------|\n");
            printf("| Recipe name '%s' already exists!            |\n", r->name);
            printf("| Please enter a unique food name.                    |\n");
            printf("|-----------------------------------------------------|\n\n");
            sleep(2);
            system("cls");
        }
        else
        {
        	success = 1;
		}
    }

    success = 0;
    
    //Recipe Description
	while (success == 0)
	{
		printf("| Enter Recipe Description (max 160 characters): ");
        scanf(" %[^\n]s", r->desc);	
        
        int descLength = strlen(r->desc);
		
		if (descLength > 0 && descLength <= 160)
		{
			success = 1;
		}
		else
		{
			printf("|--------------------------------------------|\n");
            printf("| Invalid input! Maximum 160 characters only. |\n");
            printf("|--------------------------------------------|\n\n");
            clearInputBuffer();
		}
	}
	
	success = 0;
	//Time to Prepare
	while (success == 0)
	{
		printf("| Time to prepare (in minutes): ");
        if (scanf("%d", &r->prepTime) == 1 && r->prepTime > 0)
        {
            success = 1;
        }
        else
        {
            printf("|--------------------------------------------|\n");
            printf("| Invalid input! Enter a positive integer.   |\n");
            printf("|--------------------------------------------|\n\n");
            clearInputBuffer();
        }
	}
	
	success = 0;
	//Time to Cook
	while (success == 0)
	{
		printf("| Time to cook (in minutes): ");
        if (scanf("%d", &r->cookTime) == 1 && r->cookTime > 0)
        {
            success = 1;
        }
        else
        {
            printf("|--------------------------------------------|\n");
            printf("| Invalid input! Enter a positive integer.   |\n");
            printf("|--------------------------------------------|\n\n");
            clearInputBuffer();
        }
	}
	
	success = 0;
	//Num of Ingredients
	while (success == 0)
	{
		printf("| Number of ingredients needed: ");
        if (scanf("%d", &r->numIng) == 1 && r->numIng > 0 && r->numIng < MAX_INGREDIENTS)
        {
            success = 1;
        }
        else
        {
            printf("|--------------------------------------------|\n");
            printf("| Enter a valid number between 1 and %d. |\n", MAX_INGREDIENTS);
            printf("|--------------------------------------------|\n\n");
            clearInputBuffer();
        }
	}
	
	success = 0;
	//List of Ingredients
	while (success == 0)
	{
		printf("|--------------------------------------------|\n");
		int i;
		
		for (i = 0; i < r->numIng; i++)
		{
			printf("| Ingredient #%d (max 80 characters): ", i + 1);
	        scanf(" %[^\n]s", r->ingredients[i]);
			success = 1;			
		}	
		clearInputBuffer();
	}
	
	success = 0;
	//Num of Instructions
	while (success == 0)
	{
		printf("| Number of instructions needed: ");
        if (scanf("%d", &r->numInstructions) == 1 && r->numInstructions > 0 && r->numInstructions < MAX_INSTRUCTIONS)
        {
            success = 1;
        }
        else
        {
            printf("|--------------------------------------------|\n");
            printf("| Enter a valid number between 1 and %d. |\n", MAX_INSTRUCTIONS);
            printf("|--------------------------------------------|\n\n");
            clearInputBuffer();
        }
	}
	
	success = 0;
	//List of Instructions
	while (success == 0)
	{
		printf("|--------------------------------------------|\n");
		int i;
		
		for (i = 0; i < r->numInstructions; i++)
		{
			printf("| Instruction #%d (max 100 characters): ", i + 1);
        	scanf(" %[^\n]", r->instructions[i]);
			success = 1;			
		}	
		clearInputBuffer();
	}
	
	return 1;
}

void addRecipe(User *profile)
{
    Recipe newRecipe; // Declare the foodLog struct
    
    if (verifyRecipe(&newRecipe, "")) // Pass the address of the struct to verifyFood
    {

        FILE *file = fopen("Recipes.txt", "a");
        if (file == NULL)
        {
            printf("|--------------------------------------------|\n");
            printf("| Error opening recipes file.                |\n");
            printf("|--------------------------------------------|\n\n");
            return;
        }
        
        strcpy(newRecipe.username, profile->username);
        strcpy(newRecipe.fullname, profile->name);
        
        fprintf(file, "%s\n%s %s\n%s\n%d %d\n%d\n",
                newRecipe.name, newRecipe.username, newRecipe.fullname,
                newRecipe.desc, newRecipe.prepTime, newRecipe.cookTime, newRecipe.numIng);

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
        printf("|--------------------------------------------|\n");
        printf("| Recipe added successfully!                 |\n");
        printf("|--------------------------------------------|\n\n");
        system("pause");
    }
    else
    {
        printf("|--------------------------------------------|\n");
        printf("| Recipe creation failed. Returning to menu. |\n");
        printf("|--------------------------------------------|\n\n");
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
		
	    printf("=============================================\n");
        printf("|              FOODIE APP MENU              |\n");
        printf("=============================================\n");
        printf("| [1]   + Add Food Log                      |\n");
        printf("| [2]   + Add Recipe                        |\n");
        printf("| [3]   + Modify Food Log                   |\n");
        printf("| [4]   + Modify Recipe                     |\n");
        printf("| [5]   + Delete Food Log                   |\n");
        printf("| [6]   + Delete Recipe                     |\n");
        printf("| [7]   + Display User                      |\n");
        printf("| [8]   + Display All Logs by Username      |\n");
        printf("| [9]   + Display All Food Logs             |\n");
        printf("| [10]  + Display All Recipes               |\n");
        printf("| [11]  + Search Food Log                   |\n");
        printf("| [12]  + Search Recipe                     |\n");
        printf("| [13]  + Export Data                       |\n");
        printf("| [14]  + Import Data                       |\n");
        printf("| [15]  + Exit                              |\n");
        printf("=============================================\n");
	    
	    printf("Enter your choice (1-15): ");
	    
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
    printf("| Food Name      : %s\n", log->name);
    printf("| Type           : %c\n", log->type);
    printf("| Times Eaten    : %d\n", log->timesEaten);
    printf("| Date First Tried : %s\n", log->ftDate);
    printf("| Place          : %s\n", log->ftPlace);
    printf("| Description    : %s\n", log->desc);
}

void modifyFoodLog(User *profile) 
{
    FILE *file = fopen("foodLogs.txt", "r");
    
    if (file == NULL) 
	{
        printf("| There are no food logs to modify.          |\n");
        printf("==============================================\n");
        Sleep(1000);
        return;
    }

    // Check if file is empty
    fpos_t start;
    fgetpos(file, &start);
    fscanf(file, "%*c");
    
    if (feof(file)) 
	{
        printf("| There are no food logs to modify.          |\n");
        printf("==============================================\n");
        fclose(file);
        Sleep(1000);
        return;
    }
    rewind(file);

    FILE *temp = fopen("temp.txt", "w");
    char foodName[51];
    printf("==============================================\n");
    printf("|           MODIFY FOOD LOG                  |\n");
    printf("==============================================\n");
    printf("| Enter food name to modify: ");
    scanf(" %[^\n]", foodName);
    
    clearInputBuffer();

    foodLog log; 
	foodLog tempLog;

    int found = 0, authorized = 0;
    
    while (fscanf(file, "%50[^\n]\n%50s %[^\n]\n%c %d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  log.name, log.username, log.fullname, &log.type, &log.timesEaten,
                  log.ftDate, log.ftPlace, log.desc) == 8) 
	{
        if (strcmp(log.name, foodName) == 0) 
		{
            found = 1;
            
            if (strcmp(log.username, profile->username) == 0)
            {
            	authorized = 1;
	            printf("\n\n==============================================\n");
	            printf("|             CURRENT FOOD LOG               |\n");
	            printf("==============================================\n");
	            displayFoodLog(&log);
	
	            tempLog = log;
	            
	
	            printf("\n\n|         ENTER NEW FOOD LOG DETAILS         |\n\n");
	            verifyFood(&tempLog, log.name);
	
	            char confirm;
	            printf("==============================================\n");
	            printf("| Confirm changes? (Y/N): ");
	            scanf(" %c", &confirm);
	            clearInputBuffer();
	
	            if (confirm == 'y' || confirm == 'Y') {
	                fprintf(temp, "%s\n%s %s\n%c %d\n%s\n%s\n%s\n",
	                        tempLog.name, tempLog.username, tempLog.fullname, 
							tempLog.type, tempLog.timesEaten, tempLog.ftDate, tempLog.ftPlace, tempLog.desc);
	                printf("Food log modified successfully.\n");
	            } 
				else 
				{
	                fprintf(temp, "%s\n%s %s\n%c %d\n%s\n%s\n%s\n",
	                        log.name, log.username, log.fullname, 
							log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
	                printf("| Modification cancelled.                     |\n");
	            }
			}
   			else
			{ 
                printf("==============================================\n");
                printf("| You are NOT authorized to modify this food log! |\n");
                printf("==============================================\n");
                system("pause");
            }
        } 
        
		if (strcmp(log.name, foodName) != 0 || !authorized)
		{
            fprintf(temp, "%s\n%s %s\n%c %d\n%s\n%s\n%s\n",
                    log.name, log.username, log.fullname, log.type, 
					log.timesEaten, log.ftDate, log.ftPlace, log.desc);
        }
    }
    fclose(file);
    fclose(temp);
    remove("foodLogs.txt");
    rename("temp.txt", "foodLogs.txt");
    
    if (!found) 
	{
		printf("==============================================\n");
        printf("| Food log not found.                        |\n");
        printf("==============================================\n");	
	}
    Sleep(1000);
}

void displayRecipe(const Recipe *recipe) 
{
    printf("| Food Name: %s\n", recipe->name);
    printf("| Description: %s\n", recipe->desc);
    printf("| Preparation Time: %d min/s\n", recipe->prepTime);
    printf("| Cooking Time: %d min/s\n", recipe->cookTime);
    printf("| Number of Ingredients: %d\n", recipe->numIng);
    printf("|---------------------------------------------\n");
    printf("| List of Ingredients:\n");
    
    for (int i = 0; i < recipe->numIng; i++) 
	{
        printf("| - %s\n", recipe->ingredients[i]);
    }
    
    printf("|---------------------------------------------\n");
    printf("| Number of Instructions: %d\n", recipe->numInstructions);
    printf("| Instructions:\n");
    
    for (int i = 0; i < recipe->numInstructions; i++) 
	{
        printf("| %d. %s\n", i+1, recipe->instructions[i]);
    }
}

void modifyRecipe(User *profile) 
{
    FILE *file = fopen("Recipes.txt", "r");
    if (file == NULL) 
	{
        printf("==============================================\n");
        printf("| There are no recipes to modify.            |\n");
        printf("==============================================\n");
        Sleep(1000);
        return;
    }

    // Check if file is empty
    fpos_t start;
    fgetpos(file, &start);
    fscanf(file, "%*c");
    
    if (feof(file)) 
	{
        printf("==============================================\n");
        printf("| There are no recipes to modify.            |\n");
        printf("==============================================\n");
        fclose(file);
        Sleep(1000);
        return;
    }
    
    rewind(file);

    FILE *temp = fopen("temp.txt", "w");
    char recipeName[51];
    printf("==============================================\n");
    printf("|              MODIFY RECIPE                 |\n");
    printf("==============================================\n");
    printf("| Enter recipe name to modify: ");
    scanf(" %[^\n]", recipeName);
    clearInputBuffer();

    Recipe recipe;
    Recipe tempRecipe;
    
    int i, found = 0, authorized = 0;

    while (fscanf(file, "%50[^\n]\n%50s %[^\n]\n%160[^\n]\n%d %d\n%d\n",
            recipe.name, recipe.username, recipe.fullname, 
			recipe.desc, &recipe.prepTime, &recipe.cookTime, &recipe.numIng) == 7) 
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
            
            if (strcmp(recipe.username, profile->username) == 0)
            {
            	authorized = 1;
	            printf("\n\n==============================================\n");
	            printf("|             CURRENT RECIPE                 |\n");
	            printf("==============================================\n");
	            displayRecipe(&recipe);
	
	            tempRecipe = recipe;
	            
	            printf("\n\n|         ENTER NEW RECIPE DETAILS           |\n\n");
	            verifyRecipe(&tempRecipe, recipe.name);
	
	            char confirm;
	            printf("==============================================\n");
	            printf("| Confirm changes? (Y/N): ");
	            scanf(" %c", &confirm);
	            clearInputBuffer();
	
	            if (confirm == 'y' || confirm == 'Y') 
				{
	                fprintf(temp, "%s\n%s %s\n%s\n%d %d\n%d\n",
	                        tempRecipe.name, tempRecipe.username, tempRecipe.fullname, tempRecipe.desc,
	                        tempRecipe.prepTime, tempRecipe.cookTime, tempRecipe.numIng);
	
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
	                fprintf(temp, "%s\n%s %s\n%s\n%d %d\n%d\n",
	                        recipe.name, recipe.username, recipe.fullname, recipe.desc,
	                        recipe.prepTime, recipe.cookTime, recipe.numIng);
	
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
	        	printf("|------------------------------------------------|\n");
                printf("|  You are not authorized to modify this recipe! |\n");
                printf("|------------------------------------------------|\n");
                system("pause");
			}
        } 
        
		if (strcmp(recipe.name, recipeName) != 0 || !authorized)
		{
            fprintf(temp, "%s\n%s %s\n%s\n%d %d\n%d\n",
                        recipe.name, recipe.username, recipe.fullname, recipe.desc,
                        recipe.prepTime, recipe.cookTime, recipe.numIng);

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
		printf("==============================================\n");
        printf("| Recipe not found.                          |\n");
        printf("==============================================\n");
	}
    Sleep(1000);
}

void deleteFoodLog(User *profile) 
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
    scanf(" %[^\n]", foodName);
    
    clearInputBuffer();

    foodLog log;
    int found = 0;

    while (fscanf(file, "%50[^\n]\n%50s %[^\n]\n%c %d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  log.name, log.username, log.fullname, &log.type, &log.timesEaten,
                  log.ftDate, log.ftPlace, log.desc) == 8) 
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
                fprintf(temp, "%s\n%s %s\n%c %d\n%s\n%s\n%s\n",
                            log.name, log.username, log.fullname, log.type, log.timesEaten, 
                            log.ftDate, log.ftPlace, log.desc);
                printf("Deletion cancelled. Food log retained.\n");
            }
        }
		else 
		{
            fprintf(temp, "%s\n%s %s\n%c %d\n%s\n%s\n%s\n",
                    log.name, log.username, log.fullname, log.type, log.timesEaten, 
                    log.ftDate, log.ftPlace, log.desc);
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
    
    while (fscanf(file, "%50[^\n]\n%50s %[^\n]\n%160[^\n]\n%d %d\n%d\n",
                  recipe.name, recipe.username, recipe.fullname, recipe.desc,
                  &recipe.prepTime, &recipe.cookTime, &recipe.numIng) == 7) {
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
                fprintf(temp, "%s\n%s %s\n%s\n%d %d\n%d\n",
                        recipe.name, recipe.username, recipe.fullname, recipe.desc,
                        recipe.prepTime, recipe.cookTime, recipe.numIng);

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

            fprintf(temp, "%s\n%s %s\n%s\n%d %d\n%d\n",
                        recipe.name, recipe.username, recipe.fullname, recipe.desc,
                        recipe.prepTime, recipe.cookTime, recipe.numIng);

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
	
	printf("=============================================\n");
    printf("|                 USER PROFILE              |\n");
    printf("=============================================\n");
    printf("| Username : %-30s |\n", profile->username);
    printf("| Name     : %-30s |\n", profile->name);
    printf("| Email    : %-30s |\n", profile->email);
    printf("| Number   : %-30s |\n", profile->number);
    printf("=============================================\n");
    system("pause");

    clearInputBuffer();
    fclose(file);
}

int compareDates(const char *date1, const char *date2) 
{
    int year1, month1, day1, year2, month2, day2;

    sscanf(date1, "%d/%d/%d", &month1, &day1, &year1);
    sscanf(date2, "%d/%d/%d", &month2, &day2, &year2);
    
//    printf("Comparing: %s and %s\n", date1, date2);
//    printf("Date 1: %d/%d/%d, Date 2: %d/%d/%d\n", month1, day1, year1, month2, day2, year2);

    if (year1 != year2) 
	{
        return year1 - year2;
    }
    if (month1 != month2) 
	{
        return month1 - month2;
    }
    return day1 - day2;
}

void displayAllFoodLogs() 
{
    FILE *foodFile = fopen("foodLogs.txt", "r");
    
    if (foodFile == NULL) 
	{
        printf("================================================\n");
        printf("|          ERROR OPENING FOOD LOGS FILE        |\n");
        printf("================================================\n");
        system("pause");
        return;
    }

    foodLog logs[50];
    int logCount = 0;

    while (fscanf(foodFile, "%50[^\n]\n%50s %50[^\n]\n%c %d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  logs[logCount].name, logs[logCount].username, logs[logCount].fullname, 
                  &logs[logCount].type, &logs[logCount].timesEaten, 
                  logs[logCount].ftDate, logs[logCount].ftPlace, logs[logCount].desc) == 8) 
	{
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

        printf("=================================================\n");
        printf("|                 ALL FOOD LOGS                 |\n");
        printf("|          (Sorted by Date - Descending)        |\n");
        printf("=================================================\n");

        for (int i = 0; i < logCount; i++) 
		{
            printf("| Food Log #%d                               |\n", i + 1);
            printf("=============================================\n");
            printf("| Name       : %-30s |\n", logs[i].name);
            printf("| Username   : %-30s |\n", logs[i].username);
            printf("| Full Name  : %-30s |\n", logs[i].fullname);
            printf("| Type       : %-30c |\n", logs[i].type);
            printf("| Times Eaten: %-30d |\n", logs[i].timesEaten);
            printf("| First Tried: %-30s |\n", logs[i].ftDate);
            printf("| Location   : %-30s |\n", logs[i].ftPlace);
            printf("| Description: %-30s |\n", logs[i].desc);
            printf("=============================================\n");
        }
    } 
	else 
	{
        printf("================================================\n");
        printf("|              NO FOOD LOGS FOUND              |\n");
        printf("================================================\n");
    }
    system("pause");
}


void displayAllRecipes() 
{
    FILE *recipeFile = fopen("Recipes.txt", "r");
    
    if (recipeFile == NULL) 
	{
        printf("=============================================\n");
        printf("|         ERROR OPENING RECIPES FILE        |\n");
        printf("=============================================\n");
        system("pause");
        return;
    }

    Recipe recipes[20];
    int recipeCount = 0;

    while (fscanf(recipeFile, "%50[^\n]\n%50s %[^\n]\n%160[^\n]\n%d %d\n%d\n",
                  recipes[recipeCount].name, recipes[recipeCount].username, recipes[recipeCount].fullname,
				  recipes[recipeCount].desc, &recipes[recipeCount].prepTime, &recipes[recipeCount].cookTime, 
				  &recipes[recipeCount].numIng) == 7) 
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

        printf("=============================================\n");
        printf("|                ALL RECIPES                |\n");
        printf("|         (Sorted by Name - Ascending)      |\n");
        printf("=============================================\n");

        for (int i = 0; i < recipeCount; i++) 
        {
            printf("| Recipe #%d                                 |\n", i+1);
            printf("=============================================\n");
            printf("| Name        : %-30s |\n", recipes[i].name);
            printf("| Author      : %-30s |\n", recipes[i].fullname);
            printf("| Username    : %-30s |\n", recipes[i].username);
            printf("| Description : %-30s |\n", recipes[i].desc);
            printf("| Prep Time   : %-30d |\n", recipes[i].prepTime);
            printf("| Cook Time   : %-30d |\n", recipes[i].cookTime);
            printf("| Ingredients : %-30d |\n", recipes[i].numIng);

            for (int j = 0; j < recipes[i].numIng; j++) 
			{
                printf("| - %-40s |\n", recipes[i].ingredients[j]);
            }

            printf("| Instructions: %-30d |\n", recipes[i].numInstructions);
            printf("=============================================\n");

            for (int j = 0; j < recipes[i].numInstructions; j++) 
			{
                printf("| Step %d: %-40s |\n", j + 1, recipes[i].instructions[j]);
            }
            printf("=============================================\n\n");
        }
    } 
	else 
	{
        printf("=============================================\n");
        printf("|           NO RECIPES FOUND                |\n");
        printf("=============================================\n");
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

    printf("=============================================\n");
    printf("|         SEARCH FOOD LOGS & RECIPES        |\n");
    printf("=============================================\n");
    printf("| Enter username to search: ");
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
        int foundFood = 0, foundRecipe = 0, count = 0;

        if (foodFile != NULL) 
        {
            printf("\n=============================================\n");
            printf("|           FOOD LOGS FOR %s          |\n", user.username);
            printf("=============================================\n");
            
            foodLog log;
            count = 0;

            while (fscanf(foodFile, "%50[^\n]\n%50s %[^\n]\n%c %d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                          log.name, log.username, log.fullname, &log.type, &log.timesEaten,
                          log.ftDate, log.ftPlace, log.desc) == 8) 
            {
                if (strcmp(log.username, username) == 0) 
                {
                    printf("| Food Log #%d                                |\n", ++count);
                    printf("=============================================\n");
                    displayFoodLog(&log);
                    printf("=============================================\n\n");
                    foundFood = 1;
                }
            }
            fclose(foodFile);

            if (!foundFood)
            {
                printf("| No food logs found for %s.                 |\n", user.username);
                printf("=============================================\n");
            }
        }

        if (recipeFile != NULL) 
        {
             printf("\n=============================================\n");
            printf("|           RECIPES FOR %s             |\n", user.username);
            printf("=============================================\n");

            Recipe recipe;
            int i;
            count = 0;

            while (fscanf(recipeFile, "%50[^\n]\n%50s %[^\n]\n%160[^\n]\n%d %d\n%d\n",
                          recipe.name, recipe.username, recipe.fullname, recipe.desc, 
                          &recipe.prepTime, &recipe.cookTime, &recipe.numIng) == 7) 
            {        
                if (strcmp(recipe.username, user.username) == 0)
                {
                    printf("| Recipe #%d                                 |\n", ++count);
                    printf("=============================================\n");

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
                    foundRecipe = 1;
                }
            }
            fclose(recipeFile);

            if (!foundRecipe)
            {
                printf("| No recipes found for %s.                   |\n", user.username);
                printf("=============================================\n");
            }
        }

        if (!foundFood && !foundRecipe) 
        {
            printf("\n=============================================\n");
            printf("| No food logs or recipes found for %s. |\n", user.username);
            printf("=============================================\n");
        }

        system("pause");
    } 
    else 
    {
        printf("=============================================\n");
        printf("| User '%s' not found.                      |\n", username);
        printf("=============================================\n");
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
    
    while (fscanf(foodFile, "%50[^\n]\n%50s %[^\n]\n%c %d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  log.name, log.username, log.fullname, &log.type, &log.timesEaten,
                  log.ftDate, log.ftPlace, log.desc) == 8) 
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
