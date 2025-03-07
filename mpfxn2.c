#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_INGREDIENTS 20
#define MAX_INSTRUCTIONS 20

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
	printf("\n\n====================================\n\n\n");
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

    for(i = 1; i < 11; i++)
    {
        if (str[0] != 0)
        {
            return 2;
        }
        
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
	
	if (length == 0) {
        return 3;  // empty string
    }
    if (length > 30) {
        return 2;  // exceeds max length
    }

    for (int i = 0; i < length; i++) {
        if (str[i] == '@') {
            atCount++;
            atIndex = i;
        } else if (str[i] == '.') {
            dotIndex = i;
        }
    }

    if (atCount != 1) {
        return 0;  //must have exactly one @
    }
    if (dotIndex == -1 || atIndex > dotIndex) {
        return 0;  // must have a '.' after '@'
    }
    if (atIndex == 0 || dotIndex == length - 1) {
        return 0;  // '@' must not be first, '.' must not be last
    }
    if (dotIndex - atIndex == 1) {
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
    int success = 0;
    char passwordConfirm[21];
    FILE *userFile = fopen("user.dat", "r");

    if (userFile != NULL)  // If file exists, load user data and return
    {
        fscanf(userFile, "%50s %20s %80[^\n] %30s %11s", 
               p.username, p.pass, p.name, p.email, p.number);
        fclose(userFile);
        printf("User profile loaded.\n");
        return p;
    }
    
    while (success == 0)
    {
        printf("Enter Username: "); //can it have spaces or no idk
        scanf("%50s", p.username);

        if (isAlphanumeric(p.username) == 1 && (strlen(p.username) >= 8 && strlen(p.username) <= 50))
        {
            success = 1;
        }
        else
        {
            printf("Username must only contain between 8 - 50 alphanumeric characters!\n");
        }
    }

    success = 0;

    //password input
    while (success == 0)
    {
        printf("Enter Password: ");
        scanf("%20s", p.pass);

        if (verifyPass(p.pass) == 1 && withinBounds(p.pass, 8, 20) == 1)
        {
            success = 1;
        }
        else
        {
            if (verifyPass(p.pass) == 0 && withinBounds(p.pass, 8, 20) == 1)
            {
                printf("Password must have at least 1 uppercase character, 1 lowercase character, 1 number, and 1 special character(!, @. #, $, %, &, *, and . only)!\n");
            }
            else if (verifyPass(p.pass) == 1 && withinBounds(p.pass, 8, 20) == 0)
            {
                printf("Password must be between 8 to 20 characters!\n");
            }
            else
            {
                printf("Password must be between 8 to 20 characters and must have at least 1 uppercase character, 1 lowercase character, 1 number, and 1 special character!\n");
            }
        }
    }
    
    while (strcmp(p.pass, passwordConfirm) != 0)
    {
        printf("Confirm Password: ");
        scanf("%20s", passwordConfirm);
        if (strcmp(p.pass, passwordConfirm) != 0) 
		{
            printf("Passwords do not match. Please try again.\n");
        }	
	}


    success = 0;

    //full name input
    while (success == 0)
    {
        printf("Enter full name: ");
        scanf(" %[^\n]s", p.name);

        if (isAlphabetic(p.name) == 1 && withinBounds(p.name, 5, 80) == 1)
        {
            success = 1;
        }
        else
        {
            if (isAlphabetic(p.name) == 0)
            {
                printf("Full name must only contain alphabetic characters.\n");
            }
            else if (isAlphabetic(p.name) == 1 && withinBounds(p.name, 5, 80) == 0)
            {
                printf("Full name must be between 5 and 80 characters.\n");
            }
            else
            {
                printf("Full name must be between 5 and 80 and contain only alphabetic characters.\n");
            }
        }
        void clearInputBuffer();
    }

    success = 0;

    //email address input
    while (success == 0)
    {
        printf("Enter email address: ");
        scanf("%30s", p.email);
        
        if (verifyEmail(p.email) == 1)
        {
        	success = 1;
		}
		else
		{
			if (verifyEmail(p.email) == 3)
	        {
	        	printf("Email address should not be empty.\n");
			}
			else if (verifyEmail(p.email) == 2)
			{
				printf("Email address should not be more than 30 characters.\n");
			}
			else
			{
				printf("Email address should be valid.\n");
			}
		}
		
		void clearInputBuffer();
    }
    
    success = 0;

    //mobile number input
    while (success == 0) //with spaces no work???
    {
        printf("Enter phone number (w/ no spaces): ");
        scanf("%11s", p.number);

        if (p.number[0] == '0' && strlen(p.number) == 11)
        {
            success = 1;
        }
        else 
        {
            if (p.number[0] != '0' && strlen(p.number) == 11)
            {
                printf("Phone number must start with 0!\n");
            }
            else if (p.number[0] == '0' && strlen(p.number) != 11)
            {
                printf("Phone number must contain 11 digits!\n");
            }
            else
            {
                printf("Phone number must start with 0 and contain 11 digits!\n");
            }
        }
		void clearInputBuffer();
    }

    printf("Successful account creation!\n");
    
    userFile = fopen("user.dat", "w");
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
    int success = 0;
    int attempts = 0;
    int maxAttempts = 3;
    char verifyPass[21];
    char verifyUser[51];

    while (attempts < maxAttempts && !success)
    {
    	printf("Enter username: ");
        scanf("%50s", verifyUser);
        
        printf("Enter password: ");
        scanf("%20s", verifyPass);

        if (strcmp(p->pass, verifyPass) != 0 || strcmp(p->username, verifyUser) != 0)
        {
            attempts++;
            printf("Incorrect username and/or password! Attempt %d / %d\n", attempts, maxAttempts);
        }
        else if (strcmp(p->pass, verifyPass) == 0 && strcmp(p->username, verifyUser) == 0)
        {
            printf("\n\nWelcome!\n");
            success = 1;
        }
    }
    
    if (!success)
    {
    	printf("\n\nNumber of attempts reached. Press any key and the program will terminate!\n\n");
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
        
        if (f->timesEaten > 0)
        {
        	success = 1;
		}
		else
		{
			printf("Number of times eaten must be a positive integer!\n");
		}
		
		//smegma clear buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        //smegma clear buffer
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
    FILE *file = fopen("foodlogs.txt", "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so no duplicates
    }

    foodLog tempLog;
    while (fscanf(file, "%50s %c %d %10s %30s %300[^\n]\n",
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
            return;
        }

        FILE *file = fopen("foodlogs.txt", "a");
        if (file == NULL)
        {
            printf("Error opening food logs file.\n");
            return;
        }

        fprintf(file, "%s\n%c\n%d\n%s\n%s\n%s\n",
                newLog.name, newLog.type, newLog.timesEaten,
                newLog.ftDate, newLog.ftPlace, newLog.desc);

        fclose(file);
        printf("Food log added successfully!\n");
    }
    else
    {
        printf("Food Log creation failed. Please try again.\n");
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
        
        if (r->prepTime > 0)
        {
        	success = 1;
		}
		else
		{
			printf("Minutes to prepare must be a positive integer!\n");
		}
		
		//smegma clear buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        //smegma clear buffer
	}
	
	success = 0;
	//Time to Cook
	while (success == 0)
	{
		printf("Time to cook (in minutes): ");
        scanf(" %d", &r->cookTime);
        
        if (r->cookTime > 0)
        {
        	success = 1;
		}
		else
		{
			printf("Minutes to cook must be a positive integer!\n");
		}
		
		void clearInputBuffer();
	}
	
	success = 0;
	//Num of Ingredients
	while (success == 0)
	{
		printf("Number of ingredients needed: ");
        scanf(" %d", &r->numIng);
        
        if (r->numIng > 0 && r->numIng < MAX_INGREDIENTS)
        {
        	success = 1;
		}
		else
		{
			printf("Number of ingredients must be a positive integer!\n");
		}
		
		void clearInputBuffer();
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
        
        if (r->numInstructions > 0 && r->numInstructions < MAX_INSTRUCTIONS)
        {
        	success = 1;
		}
		else
		{
			printf("Number of instructions must be a positive integer!\n");
		}
		
		void clearInputBuffer();
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
	
    FILE *file = fopen("recipes.txt", "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so no duplicates
    }

    Recipe tempRecipe;
    while (fscanf(file, "%50s %160[^\n] %d %d %d",
                  tempRecipe.name, tempRecipe.desc, &tempRecipe.prepTime,
                  &tempRecipe.cookTime, &tempRecipe.numIng) == 5) 
	{
        for (i = 0; i < tempRecipe.numIng; i++) 
		{
            fscanf(file, " %80[^\n]", tempRecipe.ingredients[i]);
        }
        fscanf(file, "%d", &tempRecipe.numInstructions);
        
        for(i = 0; i < tempRecipe.numInstructions; i++) 
		{
            fscanf(file, " %100[^\n]", tempRecipe.instructions[i]);
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
            return;
        }

        FILE *file = fopen("recipes.txt", "a");
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
    }
    else
    {
        printf("Recipe creation failed. Please try again.\n");
    }

}

int displayMenu ()
{
	int choice;
	
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
    
    return choice;
}

void modifyFoodLog() 
{
    FILE *file = fopen("foodlogs.txt", "r");
    
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
    
    int found = 0;
    while (fscanf(file, "%50[^\n]\n%c\n%d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  log.name, &log.type, &log.timesEaten, log.ftDate, log.ftPlace, log.desc) == 6) 
	{
        if (strcmp(log.name, foodName) == 0) 
		{
            found = 1;
            printf("Current: %s, Type: %c, Times Eaten: %d, Date: %s, Place: %s, Desc: %s\n",
                   log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
            printf("Enter new times eaten: ");
            scanf("%d", &log.timesEaten);
            
            clearInputBuffer();
            
            printf("Enter new date (mm/dd/yyyy): ");
            scanf("%10s", log.ftDate);
            
            clearInputBuffer();
            
            fprintf(temp, "%s\n%c\n%d\n%s\n%s\n%s\n",
                    log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
            printf("Food log modified successfully.\n");
        } 
		else 
		{
            fprintf(temp, "%s\n%c\n%d\n%s\n%s\n%s\n",
                    log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
        }
    }
    fclose(file);
    fclose(temp);
    remove("foodlogs.txt");
    rename("temp.txt", "foodlogs.txt");
    if (!found) printf("Food log not found.\n");
    Sleep(1000);
}

void modifyRecipe() {
    FILE *file = fopen("recipes.txt", "r");
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
            
            printf("Current: %s, Prep: %d min, Cook: %d min\n", recipe.name, recipe.prepTime, recipe.cookTime);
            printf("Enter new prep time (minutes): ");
            scanf("%d", &recipe.prepTime);
            
            clearInputBuffer();
            
            printf("Enter new cook time (minutes): ");
            scanf("%d", &recipe.cookTime);
            
            clearInputBuffer();
            
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
        }
    }
    
    fclose(file);
    fclose(temp);
    remove("recipes.txt");
    rename("temp.txt", "recipes.txt");
    if (!found) printf("Recipe not found.\n");
    Sleep(1000);
}

void deleteFoodLog() {
    FILE *file = fopen("foodlogs.txt", "r");
    
    if (file == NULL) 
	{
        printf("There are no food logs to delete.\n");
        Sleep(1000);
        return;
    }

    // check if file is empty
    fpos_t start;
    fgetpos(file, &start); // starting pos
    fscanf(file, "%*c");   // try to read a char
    
    if (feof(file)) 
	{      // if end of file is reached immediately, empty
        printf("There are no food logs to delete.\n");
        fclose(file);
        Sleep(1000);
        return;
    }
    rewind(file); // file pointer restart

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
        if (strcmp(log.name, foodName) != 0) 
		{
            fprintf(temp, "%s\n%c\n%d\n%s\n%s\n%s\n",
                    log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace, log.desc);
        } 
		else 
		{
            found = 1;
        }
    }
    
    fclose(file);
    fclose(temp);
    remove("foodlogs.txt");
    rename("temp.txt", "foodlogs.txt");
    
    if (found) 
	{
        printf("Food log deleted successfully.\n"); // check if file is empty after deleting
        
        FILE *check = fopen("foodlogs.txt", "r");
        if (check != NULL)
		{
            fscanf(check, "%*c");
            
            if (feof(check)) 
			{
                remove("foodlogs.txt"); //byeee empty file
            }
            
            fclose(check);
        }
    } 
	else 
	{
        printf("Food log not found.\n");
    }
    
    Sleep(1000);
}

void deleteRecipe() 
{
    FILE *file = fopen("recipes.txt", "r");
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

        if (strcmp(recipe.name, recipeName) != 0) 
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
		else 
		{
            found = 1;
        }
    }
    
    fclose(file);
    fclose(temp);
    remove("recipes.txt");
    rename("temp.txt", "recipes.txt");
    
    if (found) 
	{
        printf("Recipe deleted successfully.\n");

        FILE *check = fopen("recipes.txt", "r");
        
        if (check != NULL) 
		{
            fscanf(check, "%*c");
            
            if (feof(check)) 
			{
                remove("recipes.txt");
            }
            
            fclose(check);
        }
    } 
	else 
	{
        printf("Recipe not found.\n");
    }
    
    Sleep(1000);
}

void displayUser(User *profile) 
{
    printf("Username: %s\nName: %s\nEmail: %s\nNumber: %s\n",
           profile->username, profile->name, profile->email, profile->number);
    printf("Press Enter to continue...\n");
    
    clearInputBuffer();
}

void displayAllByUsername(User *profile) 
{
    FILE *foodFile = fopen("foodlogs.txt", "r");
    FILE *recipeFile = fopen("recipes.txt", "r");
    int found = 0;

    if (foodFile != NULL) 
	{
        printf("\nFood Logs for %s:\n", profile->username);
        foodLog log;
        
        while (fscanf(foodFile, "%50[^\n]\n%c\n%d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                      log.name, &log.type, &log.timesEaten, log.ftDate, log.ftPlace, log.desc) == 6) 
		{
            if (strcmp(profile->username, "admin") == 0 || foodNameExists(log.name)) 
			{ 
                printf("%s, Type: %c, Times: %d, Date: %s, Place: %s\n",
                       log.name, log.type, log.timesEaten, log.ftDate, log.ftPlace);
                found = 1;
            }
        }
        
        fclose(foodFile);
    }

    if (recipeFile != NULL) 
	{
        printf("\nRecipes for %s:\n", profile->username);
        Recipe recipe;
        
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
            
            if (strcmp(profile->username, "admin") == 0 || recipeNameExists(recipe.name)) 
			{
                printf("%s, Prep: %d min, Cook: %d min\n",
                       recipe.name, recipe.prepTime, recipe.cookTime);
                found = 1;
            }
        }
        
        fclose(recipeFile);
    }

    if (!found) printf("No entries found for %s.\n", profile->username);
    printf("Press Enter to continue...\n");
    clearInputBuffer();
}

