#ifndef FOODIEHEADER_H
#define FOODIEHEADER_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

#define MAX_INGREDIENTS 21
#define MAX_INSTRUCTIONS 21
#define MAX_USERNAME_LENGTH 51
#define MAX_FILENAME 30

/* FOOD LOG STRUCT */
/* USER STRUCT */
typedef struct
{
    char username[51];
    char pass[21];
    char name[81];
    char email[31];
    char number[12];
} User;

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

//FUNCTION PROTOTYPES
void displayDivider();
int isAlphanumeric(char *str);
int isAlphabetic(char *str);
void clearInputBuffer();
int withinBounds(char *str, int lowerLimit, int upperLimit);
int verifyPass(char *str);
int verifyNumber(char *str);
int verifyEmail (char *str);
int  isLeapYear(int year);
int isValidDate (char *str);
User verifyProfile();
int verifyUser(User *p);
int isValidFoodName(const char *str);
int foodNameExists(const char *foodName, const char *username);
int verifyFood(foodLog *f, const char *originalName);
void addFoodLog(User *profile);
int recipeNameExists(const char *recipeName, const char *username);
int verifyRecipe(Recipe *r, const char *originalName);
void addRecipe(User *profile);
int displayMenu ();
void displayFoodLog(const foodLog *log);
void modifyFoodLog(User *profile);
void displayRecipe(const Recipe *recipe);
void modifyRecipe(User *profile);
void deleteFoodLog(User *profile);
void deleteRecipe(User *profile);
void displayUser(User *profile);
int compareDates(const char *date1, const char *date2);
void displayAllFoodLogs();
void displayAllRecipes();
int findUser(const char *username, User *foundUser);
void displayAllByUsername(User *profile);
void searchFoodLog();
void searchRecipe();
void showLoadingBar();

#endif