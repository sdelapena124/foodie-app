# foodie-app

Your program should also allow the user to Manage Data, by providing a user-friendly interface, as well as the functionality to do the following:

1. Enter User Profile
    The first run of the program will get user credentials from the username up to the mobile number. The password will be inputted twice on creating the user credentials, one for the intended password and another for confirmation. Succeeding runs of the program will ask for the provided username and password after successful user registration. If the provided user credentials are correct, show the program menu (referring to the set of bulleted features from Add Food Log to Exit). If not, make the user try again and display how many unsuccessful logins have been made so far. Upon reaching 3 unsuccessfully login attempts, show a message for the user to log in again after some time and terminate the program after letting the user press any key to confirm the message received.

2. Add Food Log
    The program will be able to create a food log record and store the information in the food logs file. The food name should be unique and no duplicate shall exist.

3. Add Recipe
    The program will be able to create a recipe record and store the information in the recipes file. The recipe name should be unique, and no duplicates should exist.

4. Modify Food Log
    The program will be able to edit a food log one at a time by searching for the food name. When the food name is in the records, display the food log information and proceed with editing the information. Before saving the modifications, the program must seek confirmation if the intended changes are to be applied. If the user confirms the modification, proceed with updating the food log. Otherwise, leave as is.

5. Modify Recipe
    The program will be able to edit a recipe one at a time by searching for the recipe name. When
    the recipe name is in the records, display the recipe information and proceed with editing the
    information. Before saving the modifications, the program must seek confirmation if the intended
    changes are to be applied. If the user confirms the modification, proceed with updating the recipe.
    Otherwise, leave as is.

6. Delete Food Log
    The program will be able to delete a food log one at a time by searching for the food name. When
    the food name is in the records, display the food log information to be deleted. Before deleting,
    the program must seek confirmation if the intended record is to be deleted. If the user confirms
    the deletion, proceed with removing the food log. Otherwise, leave as is.

7. Delete Recipe
    The program will be able to delete a recipe one at a time by searching for the recipe name. When
    the recipe name is in the records, display the recipe information to be deleted. Before deleting,
    the program must seek confirmation if the intended record is to be deleted. If the user confirms
    the deletion, proceed with removing the recipe. Otherwise, leave as is.

8. Display User
    The program will show the details of the registered user. Do not include the password.

9. Display All Food Log and Recipe by Username
    The program will search for a username which will show all the information by the Display User
    module along with all the food logs and recipes the specified user has created assuming the
    username searched happens to have some records within the program session or lifecycle. If the
    username is not the one logged in the program, display the full name and username only yet
    continue to display all the food logs and recipes made by that username.

10. Display All Food Log
    The program will show all the food logs in descending order (based from the date first tried).

11. Display All Recipe
    The program will show all the recipes in ascending order (by recipe name alphabetically).

12. Search Food Log
    The program will be able to search the food logs by food name. If the name of the food log
    happens to be available, print the food log data. Otherwise, print “No such food has been logged.”.
    Afterwards, let the user press any key to continue and go back to the main menu.

13. Search Recipe
    The program will be able to search the recipes by recipe name. If the name of the recipe happens
    to be available, print the recipe data. Otherwise, print “No such recipe has been entered.”.
    Afterwards, let the user press any key to continue and go back to the main menu.

14. Export
    Your program should allow all data to be saved into either a text file or a binary file. The data
    stored in the text file can be used later on. The system should allow the user to specify the
    filename. Filenames have at most 30 characters including the extension. If the file exists, the
    data will be overwritten (same applies when exiting the program).
        ● User will be saved in the user.dat as a text file and the following file format can be used:
            <username><new line>
            <password><new line>
            <full name><new line>
            <email address><new line>
            <mobile number><new line>
        ● Food Logs will be saved in the foodlogs.txt file as a text file with the following file format:
            <food name1><new line>
            <food author username1><space><food author fullname1><newline>
            <food type1><space><times eaten1><new line>
            <date first tried1><new line>
            <location1><new line>
            <description1><new line>
            <food name2><new line>
            <food author username2><space><food author fullname2><newline>
            <food type2><space><times eaten2><new line>
            <date first tried2><new line>
            <location2><new line>
            <description2><new line>
            <food nameN><new line>
            <food author username2><space><food author fullname2><newline>
            <food typeN><space><times eatenN><new line>
            <date first triedN><new line>
            <locationN><new line>
            <descriptionN><new line>
        ● Recipes will be saved in the recipes.txt file as a text file with the following file format:
            <recipe name1><new line>
            <recipe author username1><space><recipe author fullname1><new line>
            <recipe description1><new line>
            <time to prepare1><space><time to cook1><new line>
            <number of ingredients1><new line><list of ingredients1>=END=<new line>
            <number of instructions1><new line><instructions1>=END=<new line>
            <recipe name2><new line>
            <recipe author username2><space><recipe author fullname2><new line>
            <recipe description2><new line>
            <time to prepare2><space><time to cook2><new line>
            <number of ingredients2><new line><list of ingredients2>=END=<new line>
            <number of instructions2><new line><instructions2>=END=<new line>
            <recipe nameN><new line>
            <recipe author usernameN><space><recipe author fullnameN><new line>
            <recipe descriptionN><new line>
            <time to prepareN><space><time to cookN><new line>
            <number of ingredientsN><new line><list of ingredientsN>=END=<new line>
            <number of instructionsN><new line><instructionsN>=END=<new line>

15. Import
    Your program should allow the data stored in the text file to be added to the list of entries in the
    program (for both food logs and recipes). The user should be able to specify which file (input
    filename) to load. If entries have been added (or loaded previously) in the current run, the
    program shows one entry loaded from the text file and asks if this is to be added to the list of
    entries (in the array). If yes, it is added as another entry. If no, this entry is skipped. Whichever
    choice is made by the user, the program proceeds to retrieve the next entry in the file and asks
    the user again if this is to be included in the array or not, until all entries in the file are retrieved. The data in the text file will follow the format indicated in Export.

16. Exit
    The exit option will just allow the user to quit the program. The information in the lists should be
    cleared after this option, only through the Export module will specified data be saved in a file.

_________________________________________________________________________________________________________
BONUS: 
    A maximum of 10 points may be given for features over & above the requirements, like (1) producing top 5 of the number of times eaten based from the food log (not necessarily with equal count); 
    (2) producing top 3 recipes of the shortest time to prepare and cook; or other features not conflicting with the given requirements or changing the requirements) subject to evaluation of the teacher. Required features must be completed first before bonus features are credited. Note that
    use of conio.h, or other advanced C commands/statements may not necessarily merit bonuses.

IMPORTANT NOTES:
    1. Use gcc -Wall to compile your C program. Make sure you test your program completely (compiling &
       running).
    2. Do not use brute force. Use appropriate conditional statements properly. Use, wherever 
       appropriate, appropriate loops & functions properly.
    3. You may use topics outside the scope of CCPROG2 but this will be self-study. Goto label, exit(),
       break (excepT in switch), continue, global variables, calling main() are not allowed.
    4. Include internal documentation (comments) in your program.
    5. The following is a checklist of the deliverables:
        ❒ Upload via AnimoSpace submission:
            ❒ source code*
            ❒ test script**
            ❒ sample text file exported from your program
        ❒ email the softcopies of all requirements as attachments to YOUR own email address on or before the deadline

Group Solution: 
    Once both students are done with their solution: they discuss and compare their respective solutions (ONLY within the group)--note that learning with a peer is the objective here-- to see a possibly different or better way of solving a problem. They then come up with their group's final solution -- which may be the solution of one of the students, or an improvement over both solutions. Only the group's final solution, with internal documentation (part of comment) indicating whose code was used or was it an improved version of both solutions) will be submitted as part of the final deliverables. It is the group solution that will be checked/assessed/graded. Thus, only 1 final set of deliverables should be uploaded by one of the members in the Canvas submission page. [Prior to submission, make sure to indicate the members in the group by JOINing the same group number.]