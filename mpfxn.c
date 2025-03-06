#include <stdio.h>
#include <string.h>
#include <windows.h>

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
    int numSteps;
    char steps[101];
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


/* func for taking input and storing user info in the struct*/
User
verifyProfile()
{
    User p;
    int success = 0;
    char passwordConfirm[21];
    FILE *userFile = fopen("user.txt", "r");

    //username input
    if (userFile == NULL)
    {
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

        //smegma clear buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        //smegma clear buffer
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
		
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
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
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("Successful account creation!\n");
    
    userFile = fopen("user.txt", "w");
        if (userFile != NULL) 
		{
            fprintf(userFile, "%s\n%s\n%s\n%s\n%s\n", p.username, p.pass, p.name, p.email, p.number);
            fclose(userFile);
        } 
		else 
		{
            printf("Error saving user data.\n");
        }
	}
	else 
	{ // Load existing user profile
        fscanf(userFile, "%50s %20s %80s%160s %30s %11s\n", p.username, p.pass, p.name, p.email, p.number);
        fclose(userFile);
        printf("User profile loaded.\n");
    }


    return p;
}


//still need to add more features
int
verifyUser(User p)
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

        if (strcmp(p.pass, verifyPass) != 0 || strcmp(p.username, verifyUser) != 0)
        {
            printf("Password and/or username does not match!\n");
            attempts++;
        }
        else if (strcmp(p.pass, verifyPass) == 0 && strcmp(p.username, verifyUser) == 0)
        {
            printf("Welcome!\n");
            success = 1;
        }
    }
    
    if (!success)
    {
    	printf("Number of attempts reached. Program will now terminate!");
	}
	
    return success;
}

