#include "foodieHEADER.h"


/* clearInputBuffer clears any remaining characters in the input buffer.
*/
void clearInputBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* isAlphanumeric checks if a given string contains only alphanumeric characters.
   @param str - pointer to the string to be checked.
   @return 1 if the string contains only letters (A-Z, a-z) and digits (0-9).
   @return 0 if the string contains any non-alphanumeric character.
   Pre-condition: str is a valid null-terminated string.
*/
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


/* isAlphabetic checks if a given string contains only alphabetic characters and spaces.
   @param str - pointer to the string to be checked.
   @return 1 if the string contains only letters (A-Z, a-z) and spaces.
   @return 0 if the string contains any non-alphabetic character other than spaces.
   Pre-condition: str is a valid null-terminated string.
*/
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



/* withinBounds checks if the length of a given string falls within a specified range.
	@param str - pointer to the input string
	@param lowerLimit - minimum allowable length (inclusive)
	@param upperLimit - maximum allowable length (inclusive)
	@return 1 if the string length is within bounds, 0 otherwise
	Pre-condition: str is a valid null-terminated string.
*/
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


/* verifyPass checks if a given password meets the required criteria: 
   it must contain at least one uppercase letter, one lowercase letter, 
   one numeric digit, and one special character from the allowed set (!, @, $, %, &, *, .).
   
   @param str - pointer to the input password string
   @return 1 if the password meets all criteria, 0 otherwise
   Pre-condition: str is a valid null-terminated string.
*/

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

/* verifyNumber checks if a given string represents a valid 11-digit mobile number.
   
   @param str - pointer to the input string representing the mobile number
   @return 1 if the number is valid (exactly 11 digits, starts with '0', and contains only digits)
   @return 0 if the number is invalid (not 11 characters long or contains non-numeric characters)
   @return 2 if the number does not start with '0'
   Pre-condition: str is a valid null-terminated string.
*/
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


/* verifyEmail checks if a given string is a valid email address.

   @param str - pointer to the input string representing the email address
   @return 1 if the email is valid (contains exactly one '@', has a '.' after '@', and follows proper format)
   @return 0 if the email is invalid (missing '@' or '.', misplaced characters, or incorrect format)
   @return 2 if the email exceeds the maximum length of 30 characters
   @return 3 if the input string is empty
   Pre-condition: str is a valid null-terminated string.
*/
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

/* isLeapYear checks whether a given year is a leap year.

   @param year - the year to check
   @return 1 if the year is a leap year (divisible by 4 and either not divisible by 100 or divisible by 400)
   @return 0 if the year is not a leap year
   Pre-condition: year is a positive integer.
*/
int isLeapYear(int year) 
{
    // Leap year: divisible by 4 AND (not divisible by 100 OR divisible by 400)
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

/* isValidDate checks if a given date string is in the format "MM/DD/YYYY" and represents a valid calendar date.

   @param str - pointer to the date string
   @return 1 if the date is valid
   @return 0 if the format is incorrect (not in "MM/DD/YYYY" or contains non-numeric characters)
   @return 3 if the month, day, or year is out of valid range
   Pre-condition: str is a null-terminated string.
   - The expected format is "MM/DD/YYYY" (length = 10).
   - Month must be between 1 and 12.
   - Year must be between 1900 and 2099.
   - Day must be within the valid range for the given month and year.
*/
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


/* verifyProfile handles the user registration process by collecting and validating user credentials and profile details.

   @return User - a struct containing the registered user's details.
   
   The function ensures that:
   - The username is alphanumeric and between 8 to 50 characters.
   - The password is 8-20 characters long and contains at least one uppercase letter, one lowercase letter, one number, and one special character.
   - The full name consists only of alphabetic characters and is 5-80 characters long.
   - The email follows a valid format.
   - The phone number is exactly 11 digits long and starts with '0'.
   
   If all inputs are valid, the user data is appended to "profiles.dat". 
   If file writing fails, an error message is displayed.
   
   Pre-condition: The function assumes that the `User` structure and validation functions (`isAlphanumeric`, `verifyPass`, `isAlphabetic`, `verifyEmail`, `verifyNumber`, and `withinBounds`) are properly defined and implemented.
*/
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


/* verifyUser handles the user login process by checking provided credentials against stored user data.

   @param p - pointer to a User struct where the authenticated user's details will be stored.
   @return 1 if login is successful, 0 if unsuccessful after 3 attempts.

   The function performs the following:
   - Opens "profiles.dat" to read stored user credentials.
   - Prompts the user to enter their username and password.
   - Compares the input credentials with stored credentials.
   - If a match is found, the user's details are copied into the provided User struct.
   - Allows up to 3 login attempts before locking the user out.
   - Displays an error message if no user profiles are found.

   Pre-condition: The function assumes the `User` structure is properly defined. 
   The "profiles.dat" file must exist and contain valid user records in the expected format.
*/
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

/* isValidFoodName checks if a given food name follows the required format.

   @param str - pointer to the input string representing the food name.
   @return 1 if the food name is valid, 0 otherwise.

   The function ensures:
   - The length of the food name is between 3 and 50 characters (inclusive).
   - The name consists of only alphanumeric characters and spaces.
   - No consecutive spaces are present.

   Pre-condition: str must be a valid null-terminated string.
*/
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

/* foodNameExists checks if a food entry with the given name and username already exists in the food logs.

   @param foodName - pointer to the input string representing the food name.
   @param username - pointer to the input string representing the username of the food entry's author.
   @return 1 if the food name exists under the specified username, 0 otherwise.

   The function reads "foodLogs.txt" and compares each food name with the given name.
   If a match is found where both the food name and username match, the function returns 1.
   If the file doesn't exist or no match is found, it returns 0.

   Pre-condition: foodName and username must be valid null-terminated strings.
*/
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

/* verifyFood prompts the user to input and validate food log details.

   @param f - pointer to a foodLog struct where the details will be stored.
   @param originalName - the original food name (used for checking uniqueness if modifying an entry).
   @return 1 when a valid food entry is successfully gathered.

   The function ensures:
   - The food name is unique (unless unchanged) and follows format rules.
   - The food type is restricted to 'a', 'm', or 'd'.
   - The number of times eaten is a positive integer.
   - The date first tried follows mm/dd/yyyy format and is a valid date.
   - The location name is within 30 characters.
   - The description does not exceed 300 characters.

   Pre-condition: f must be a valid pointer to an initialized foodLog structure.
*/
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
            printf(" Food name '%s' already exists!            \n", f->name);
            printf(" Please enter a unique food name.              \n");
            printf("|-----------------------------------------------|\n\n");
            Sleep(2);
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
			printf("|------------------------------------------------------|\n");
            printf("| Invalid location! Maximum number of characters is 30.|\n");
            printf("|------------------------------------------------------|\n\n");
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
			printf("|----------------------------------------------------------|\n");
            printf("| Invalid description! Maximum number of characters is 300.|\n");
            printf("|----------------------------------------------------------|\n\n");
		}
		
	}
	return 1;
}

/* addFoodLog allows a user to add a new food log entry.

   @param profile - pointer to a User struct containing the logged-in user's details.

   The function:
   - Calls verifyFood() to ensure the new food log entry meets validation rules.
   - Appends the validated food log entry to "foodLogs.txt" if successful.
   - Displays success or failure messages accordingly.

   Pre-condition: profile must be a valid pointer to a User struct with an active session.
*/
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

/* recipeNameExists checks if a recipe name already exists in "Recipes.txt".

	@param recipeName - the name of the recipe to check.
	@param username - the username of the user checking for duplicates.
	@return 1 if the recipe name exists, 0 otherwise.
	Pre-condition: "Recipes.txt" follows the correct format and exists if not empty.
*/
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

/* verifyRecipe prompts the user to input and validate a recipe's details.

   @param r - pointer to a Recipe struct where the recipe details will be stored.
   @param originalName - the original recipe name (used to check for name changes).
   @return 1 after successfully gathering and validating the recipe details.
   Pre-condition: `r` must be a valid pointer to a Recipe struct.
*/
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
            printf("|----------------------------------------------|\n");
            printf("| Recipe name must contain 3 - 50 alphanumeric |\n");
            printf("| characters and may contain single spaces.    |\n");
            printf("|----------------------------------------------|\n\n");
        }
        else if (strcmp(r->name, originalName) != 0 && recipeNameExists(r->name,r->username))
        {
            printf("|-----------------------------------------------------|\n");
            printf(" Recipe name '%s' already exists!            \n", r->name);
            printf(" Please enter a unique food name.                    \n");
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
			printf("|---------------------------------------------|\n");
            printf("| Invalid input! Maximum 160 characters only. |\n");
            printf("|---------------------------------------------|\n\n");
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

/* addRecipe allows a user to create and save a new recipe.

   @param profile - pointer to a User struct containing the logged-in user's details.
   @return void (displays success or failure messages accordingly).
   Pre-condition: `profile` must be a valid pointer to a User struct with an active session.
*/
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

/* displayMenu presents the main menu and prompts the user to make a selection.

   @return the user's selected menu option (integer between 1 and 15).
   Pre-condition: The input must be a valid integer within the range of available options.
*/
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

/* displayFoodLog displays the details of a given food log.

   @param log - pointer to a foodLog struct containing the food log details.
   @return void (prints the food log information to the console).
   Pre-condition: `log` must be a valid pointer to a foodLog struct.
*/
void displayFoodLog(const foodLog *log) 
{
    printf("| Food Name      : %s\n", log->name);
    printf("| Username       : %s\n", log->username);
    printf("| Type           : %c\n", log->type);
    printf("| Times Eaten    : %d\n", log->timesEaten);
    printf("| Date First Tried : %s\n", log->ftDate);
    printf("| Place          : %s\n", log->ftPlace);
    printf("| Description    : %s\n", log->desc);
}

/* modifyFoodLog allows a user to update an existing food log if they are authorized.

   @param profile - pointer to a User struct containing the logged-in user's details.
   @return void (displays success or failure messages accordingly).
   Pre-condition: `profile` must be a valid pointer to a User struct with an active session.
                 "foodLogs.txt" must exist if not empty and follow the correct format.
*/
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
                printf("==================================================\n");
                printf("| You are NOT authorized to modify this food log! |\n");
                printf("==================================================\n");
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

/* displayRecipe prints the details of a given recipe.

   @param recipe - pointer to a Recipe struct containing the recipe details.
   @return void (prints the recipe information to the console).
   Pre-condition: `recipe` must be a valid pointer to a Recipe struct.
*/
void displayRecipe(const Recipe *recipe) 
{
    printf("| Food Name: %s\n", recipe->name);
    printf("| Username: %s\n", recipe->username);
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

/* modifyRecipe allows a user to modify an existing recipe in "Recipes.txt". 

   @param profile - pointer to a User struct representing the logged-in user.
   @return void (modifies the recipe file if changes are confirmed).
   Pre-condition: "Recipes.txt" follows the correct format and exists if not empty.
*/
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

/* deleteFoodLog allows a user to delete an existing food log from "foodLogs.txt".

   @param profile - pointer to a User struct representing the logged-in user.
   @return void (removes the food log if deletion is confirmed).
   Pre-condition: "foodLogs.txt" follows the correct format and exists if not empty.
*/
void deleteFoodLog(User *profile) 
{
    FILE *file = fopen("foodLogs.txt", "r");
    
    printf("==============================================\n");
    printf("|              DELETE FOOD LOG               |\n");
    printf("==============================================\n");
    
    if (file == NULL) 
    {
        printf("| There are no food logs to delete.          |\n");
        printf("==============================================\n");
        system("pause");
        return;
    }

    char foodName[51];
    printf("| Enter food name to delete: ");
    scanf(" %[^\n]", foodName);
    
    clearInputBuffer();

    FILE *temp = fopen("temp.txt", "w");
    foodLog log;
    int found = 0, authorized = 0;
    int shouldWrite;

    while (fscanf(file, "%50[^\n]\n%50s %[^\n]\n%c %d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  log.name, log.username, log.fullname, &log.type, &log.timesEaten,
                  log.ftDate, log.ftPlace, log.desc) == 8) 
    {
        shouldWrite = 1; // Assume we write unless deletion is confirmed
        
        if (strcmp(log.name, foodName) == 0) 
        {
            found = 1;
            
            if (strcmp(log.username, profile->username) == 0)
            {
                authorized = 1;
                printf("==============================================\n");
			    printf("|            FOOD LOG TO DELETE              |\n");
			    printf("==============================================\n");
                displayFoodLog(&log);
                printf("==============================================\n");

                char confirm;
                printf("| Confirm deletion? (Y/N): ");
                scanf(" %c", &confirm);
                clearInputBuffer();

                if (confirm == 'y' || confirm == 'Y') 
                {
                    printf("| Food log successfully deleted.             |\n");
        			printf("==============================================\n");
                    shouldWrite = 0;
                } 
                else
                {
                    printf("| Deletion cancelled. Food log retained.     |\n");
        			printf("==============================================\n");
                }
            }
            else
            {
                printf("==============================================\n");
                printf("|  You are not authorized to delete this log! |\n");
                printf("==============================================\n");
                system("pause");
            }
        }

        // Write the log back only if it should not be deleted
        if (shouldWrite)
        {
            fprintf(temp, "%s\n%s %s\n%c %d\n%s\n%s\n%s\n",
                    log.name, log.username, log.fullname, log.type, log.timesEaten, 
                    log.ftDate, log.ftPlace, log.desc);
        }
    }

    fclose(file);
    fclose(temp);

    if (found && authorized)
    {
        remove("foodLogs.txt");
        rename("temp.txt", "foodLogs.txt");

        // Check if the file is now empty after deletion
        FILE *check = fopen("foodLogs.txt", "r");
        if (check != NULL) 
        {
            fseek(check, 0, SEEK_END);
            if (ftell(check) == 0)
            {
                fclose(check);
                remove("foodLogs.txt");
            } 
            else 
            {
                fclose(check);
            }
        }
    } 
    else 
    {
        remove("temp.txt");
        if (!found)
        {
            printf("==============================================\n");
            printf("| Food log not found.                        |\n");
            printf("==============================================\n");
            system("pause");
        }
    }

    Sleep(1000);
}

/* deleteRecipe allows a user to delete a recipe from "Recipes.txt" if they are the author.

   @param profile - pointer to a User struct representing the logged-in user.
   @return void (removes the recipe if deletion is confirmed).
   Pre-condition: "Recipes.txt" exists and follows the correct format.
*/
void deleteRecipe(User *profile) 
{
    FILE *file = fopen("Recipes.txt", "r");
    
    printf("==============================================\n");
    printf("|               DELETE RECIPE                |\n");
    printf("==============================================\n");
    
    if (file == NULL) 
	{
        printf("| There are no recipes to delete.            |\n");
        printf("==============================================\n");
        Sleep(1000);
        return;
    }

    fpos_t start;
    fgetpos(file, &start); 
    fscanf(file, "%*c");  

    if (feof(file)) 
	{  
        printf("| There are no recipes to delete.            |\n");
        printf("==============================================\n");
        fclose(file);
        Sleep(1000);
        return;
    }
    
    rewind(file); 

    FILE *temp = fopen("temp.txt", "w");
    char recipeName[51];
    printf("| Enter recipe name to delete: ");
    scanf(" %[^\n]", recipeName);
    clearInputBuffer();

    Recipe recipe;
    int i, found = 0, authorized = 0, shouldWrite;
    
    while (fscanf(file, "%50[^\n]\n%50s %[^\n]\n%160[^\n]\n%d %d\n%d\n",
                  recipe.name, recipe.username, recipe.fullname, recipe.desc,
                  &recipe.prepTime, &recipe.cookTime, &recipe.numIng) == 7) 
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
        
        shouldWrite = 1; //Assume writing

        if (strcmp(recipe.name, recipeName) == 0) 
		{
            found = 1;
            
            if (strcmp(recipe.username, profile->username) == 0)
            {
            	authorized = 1;
            	printf("==============================================\n");
                printf("|            RECIPE TO DELETE                |\n");
                printf("==============================================\n");
	            displayRecipe(&recipe);
	            printf("==============================================\n");
	
	            char confirm;
	            printf("| Confirm deletion? (Y/N): ");
	            scanf(" %c", &confirm);
	            clearInputBuffer();
	            printf("==============================================\n");
	
	            if (confirm == 'y' || confirm == 'Y') 
				{
	 		       	printf("| Recipe successfully deleted.               |\n");
                    printf("==============================================\n");
                    shouldWrite = 0;
	            } 
				else 
				{
					printf("| Deletion cancelled. Recipe retained.       |\n");
                    printf("==============================================\n"); 
	            }
	        }
	        else 
            {
                printf("==============================================\n");
                printf("|  You are not authorized to delete this!    |\n");
                printf("==============================================\n");
            }
        }
		 
		if (shouldWrite)  
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
    
    if (found && authorized) 
	{
        remove("Recipes.txt");
        rename("temp.txt", "Recipes.txt");

        FILE *check = fopen("Recipes.txt", "r");
        if (check != NULL) 
        {
            fseek(check, 0, SEEK_END);
            if (ftell(check) == 0) 
            {
                fclose(check);
                remove("Recipes.txt");
            } 
            else 
            {
                fclose(check);
            }
        }
    } 
    else if (!found) 
    {
        remove("temp.txt");
        printf("| Recipe not found.                          |\n");
        printf("==============================================\n");
    }

    system("pause");
    Sleep(1000);
}

/* 
   displayUser displays the current user's profile information.

   @param profile - pointer to a User struct representing the logged-in user.
   @return void (simply prints the user details).
   Pre-condition: profile is already loaded with valid user data.
*/
void displayUser(User *profile) 
{
	
	printf("=============================================\n");
    printf("|                 USER PROFILE              |\n");
    printf("=============================================\n");
    printf("| Username : %-30s |\n", profile->username);
    printf("| Name     : %-30s |\n", profile->name);
    printf("| Email    : %-30s |\n", profile->email);
    printf("| Number   : %-30s |\n", profile->number);
    printf("=============================================\n");
    system("pause");

}

/* 
   compareDates compares two date strings in the format MM/DD/YYYY.

   @param date1 - first date string to compare.
   @param date2 - second date string to compare.
   @return int - returns a positive value if date1 is later than date2, 
                 a negative value if date1 is earlier than date2, 
                 and 0 if both dates are the same.
   Pre-condition: date1 and date2 must be valid strings in MM/DD/YYYY format.
*/
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

/* 
   displayAllFoodLogs reads and displays all food logs from "foodLogs.txt" in descending order by date.

   @return void (prints the list of food logs or an error message if no logs exist).
   Pre-condition: "foodLogs.txt" must exist and contain valid food log entries.
*/
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
            printf(" Name       : %-30s \n", logs[i].name);
            printf(" Username   : %-30s \n", logs[i].username);
            printf(" Full Name  : %-30s \n", logs[i].fullname);
            printf(" Type       : %-30c \n", logs[i].type);
            printf(" Times Eaten: %-30d \n", logs[i].timesEaten);
            printf(" First Tried: %-30s \n", logs[i].ftDate);
            printf(" Location   : %-30s \n", logs[i].ftPlace);
            printf(" Description: %-30s \n", logs[i].desc);
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

/* 
   displayAllRecipes reads and displays all recipes from "Recipes.txt" in ascending order by name.

   @return void (prints the list of recipes or an error message if no recipes exist).
   Pre-condition: "Recipes.txt" must exist and contain valid recipe entries.
*/
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
            printf(" Name        : %-30s \n", recipes[i].name);
            printf(" Author      : %-30s \n", recipes[i].fullname);
            printf(" Username    : %-30s \n", recipes[i].username);
            printf(" Description : %-30s \n", recipes[i].desc);
            printf(" Prep Time   : %-30d \n", recipes[i].prepTime);
            printf(" Cook Time   : %-30d \n", recipes[i].cookTime);
            printf(" Ingredients : %-30d \n", recipes[i].numIng);

            for (int j = 0; j < recipes[i].numIng; j++) 
			{
                printf("| - %-40s \n", recipes[i].ingredients[j]);
            }

            printf("| Instructions: %-30d |\n", recipes[i].numInstructions);
            printf("=============================================\n");

            for (int j = 0; j < recipes[i].numInstructions; j++) 
			{
                printf("| Step %d: %-40s \n", j + 1, recipes[i].instructions[j]);
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

/* 
   findUser searches for a user by username in "profiles.dat" and stores the user details in foundUser.

   @param username - the username to search for.
   @param foundUser - pointer to a User struct where the found user's data will be stored.
   @return int - returns 1 if the user is found, otherwise returns 0.
   Pre-condition: "profiles.dat" must exist and contain valid user data.
*/
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

/* 
   displayAllByUsername searches for a user's food logs and recipes based on their username.

   @param profile - pointer to a User struct representing the currently logged-in user.
   @return void (displays the user's food logs and recipes if found).
   Pre-condition: "profiles.dat", "foodLogs.txt", and "Recipes.txt" must exist and contain valid data.
*/
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
            printf("           FOOD LOGS FOR %s          \n", user.username);
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
                printf(" No food logs found for %s.                 \n", user.username);
                printf("=============================================\n");
            }
        }

        if (recipeFile != NULL) 
        {
             printf("\n=============================================\n");
            printf("           RECIPES FOR %s             \n", user.username);
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
                printf(" No recipes found for %s.                   \n", user.username);
                printf("=============================================\n");
            }
        }

        if (!foundFood && !foundRecipe) 
        {
            printf("\n=============================================\n");
            printf(" No food logs or recipes found for %s. \n", user.username);
            printf("=============================================\n");
        }

        system("pause");
    } 
    else 
    {
        printf("=============================================\n");
        printf(" User '%s' not found.                      \n", username);
        printf("=============================================\n");
        system("pause");
    }
    clearInputBuffer();
}

/* 
   searchFoodLog searches for a specific food log by name.

   @return void (displays the matching food log if found).
   Pre-condition: "foodLogs.txt" must exist and contain valid food log data.
*/
void searchFoodLog() 
{
    FILE *foodFile = fopen("foodLogs.txt", "r");
    char searchName[51];
    int found = 0;
    
    printf("==============================================\n");
    printf("|              SEARCH FOOD LOG               |\n");
    printf("==============================================\n");
    
    if (foodFile == NULL) 
	{
        printf("| Error: Unable to open food logs file.      |\n");
        printf("| Returning to main menu...                  |\n");
        printf("==============================================\n");;
    	getchar();
    	getchar();
        return;
    }

    printf("| Enter the food name to search: ");
    scanf(" %50[^\n]", searchName);
    clearInputBuffer();
    printf("==============================================\n");

    foodLog log;
    
    while (fscanf(foodFile, "%50[^\n]\n%50s %[^\n]\n%c %d\n%10[^\n]\n%30[^\n]\n%300[^\n]\n",
                  log.name, log.username, log.fullname, &log.type, &log.timesEaten,
                  log.ftDate, log.ftPlace, log.desc) == 8) 
	{
        if (strcmp(log.name, searchName) == 0) 
		{
			printf("|                 MATCH FOUND!               |\n");
            printf("==============================================\n");
            displayFoodLog(&log);
            found = 1;
            printf("==============================================\n");
        }
    }

    fclose(foodFile);

    if (!found) 
	{
        printf("| No matching food log found.                |\n");
        printf("==============================================\n");
    }

    printf("| Press any key to return to the main menu...|\n");
    printf("==============================================\n");
    getchar();
}

/* 
   searchRecipe searches for a specific recipe by name.

   @return void (displays the matching recipe if found).
   Pre-condition: "Recipes.txt" must exist and contain valid recipe data.
*/
void searchRecipe() 
{
    FILE *recipeFile = fopen("Recipes.txt", "r");
    
    printf("==============================================\n");
    printf("|              SEARCH RECIPE                 |\n");
    printf("==============================================\n");
    
    if (recipeFile == NULL) 
	{
        printf("| Error: Unable to open recipes file.        |\n");
        printf("| Returning to main menu...                  |\n");
        printf("==============================================\n");
    	getchar();
    	getchar();
        return;
    }

    char searchName[51];
    printf("| Enter the recipe name to search: ");
    scanf(" %50[^\n]", searchName);
    clearInputBuffer();
    printf("==============================================\n");

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
			printf("|               MATCH FOUND!                  |\n");
            printf("==============================================\n");
			displayRecipe(&recipe);
			printf("==============================================\n");
            found = 1;
        }    
    }

    fclose(recipeFile);

    if (!found) 
	{
        printf("| No matching recipe found.                   |\n");
        printf("==============================================\n");
    }

    printf("| Press any key to return to the main menu... |\n");
    printf("==============================================\n");
    getchar();
}

/* 
   showLoadingBar simulates a loading progress bar during the login process.

   @return void (displays a progress bar effect on the console).
   Pre-condition: The function is called when a loading effect is needed.
*/
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
