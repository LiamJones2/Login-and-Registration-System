// Login and Registration System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>





//Namespace to login. Filled with all the necessary functions to login
namespace loginNamespace {
    //username and password strings that will be used to hold input of user and compare it to the database for a successful login
    std::string username;
    std::string password;



    //creates access to the database (read only)
    std::fstream accessToUserDatabaseLoginVersion("users_database.txt");



    //prints out welcome to login message for the user when the login command is activated
    void welcomeUserToLogin() {
        std::cout << "Welcome to login" << std::endl;
    }

    //prints out request for username message
    void requestForUsernameMessage() {
        std::cout << "Please input your username: ";
    }

    //prints out request for password message
    void requestForPasswordMessage() {
        std::cout << "Please input your password: ";
    }

    //stores user's login username that they will attempt to login with
    void inputForUsername() {
        std::cin >> username;
    }

    //stores user's login password that they will attempt to login with
    void inputForPassword() {
        std::cin >> password;
    }

    //prints out wrong username and password message
    void unfortunatelyTheUsernameAndOrPasswordAreIncorrectMessage() {
        std::cout << "Unfortunately the username and/or password you provided are incorrect" << std::endl;
        std::cout << "Please try again." << std::endl;
    }

    //checks if line of database starts with a 'U', if it does then it holds a username in the line, needs the "Username: " part in the database removed
    //so we have an initial username and then return it so it can be tested against the string username in login namespace
    std::string checkIfLineOfUserDatabaseHoldsAUsername(std::string lineOfUserDatabase) {
        std::string singleLine = lineOfUserDatabase;
        if (lineOfUserDatabase[0] == 'U') {
            singleLine = lineOfUserDatabase.replace(0, 10, "");
            return singleLine;
        }
        return "";
    }

    //prints out thank you for logging in if username and password both match what is in the database
    void welcomeUserOnLoggingInCorrectly() {
        std::cout << "Thank you for logging in correctly" << std::endl;
        std::cout << "Welcome :)" << std::endl;
    }


    //checks if line of database starts with a 'p', if it does then it holds a password in the line and needs the "password: " part in the database removed
    //If the password correctly matches with the right username then we print the welcomeUserOnLoggingInCorrectly function's message
    void checkIfLineOfUserDatabaseHoldsAPasswordThenRemoveUnwantedPartAndIfCorrectPrintOutLoggingInCorrectlyMessage() {
        std::string lineOfUserDatabase;
        std::string passwordOfDatabase;
        getline(accessToUserDatabaseLoginVersion, lineOfUserDatabase);
        if (lineOfUserDatabase[0] == 'P') {
            passwordOfDatabase = lineOfUserDatabase.replace(0, 10, "");
            if (passwordOfDatabase == password) {
                welcomeUserOnLoggingInCorrectly();
            }
            else {
                unfortunatelyTheUsernameAndOrPasswordAreIncorrectMessage();
            }
        }
    }


    //resets database to prevent any bugs or problems
    void resetDatabaseLinesBackToTheFirstLine() {
        accessToUserDatabaseLoginVersion.clear();
        accessToUserDatabaseLoginVersion.seekg(0);
    }


    //checks if line every line of database holding a username matches with the username the user requested to login
    //If username matches then call the password check function to check if the password is correct
    //reset's database lines back to the first line
    bool getEveryLineOfUserDatabase() {
        std::string lineOfUserDatabase;
        while (getline(accessToUserDatabaseLoginVersion, lineOfUserDatabase)) {
            std::string previousUsernames = checkIfLineOfUserDatabaseHoldsAUsername(lineOfUserDatabase);
            if (previousUsernames == username) {
                checkIfLineOfUserDatabaseHoldsAPasswordThenRemoveUnwantedPartAndIfCorrectPrintOutLoggingInCorrectlyMessage();
                resetDatabaseLinesBackToTheFirstLine();
                return false;
            }

        }
        unfortunatelyTheUsernameAndOrPasswordAreIncorrectMessage();
        resetDatabaseLinesBackToTheFirstLine();
        return true;
    }





}

//Namespace to register that holds every function required to register
namespace registrationNamespace {
    std::string registerUsername;
    std::string registerPassword;



    std::ifstream accessToUserDatabaseRegisterVersion("users_database.txt");




    //Prints out welcome message to user when they pick to register
    void welcomeUserToRegistrationMessage() {
        std::cout << "Welcome to registration" << std::endl;
    }



    //Prints out request message asking for input to what they want to name
    void requestForRegistrationNameMessage() {
        std::cout << "Please input your requested username: ";
    }




    //User inputs their requested username
    void inputForRegistrationUsername() {
        std::cin >> registerUsername;
    }



    //prints out username is already taken message
    void unfortunatelyThatUsernameIsAlreadyTakenMessage() {
        std::cout << "Unforunately that username is already taken" << std::endl;
        std::cout << "Please try another username: ";

    }



    //checks if line of database holds a username, if it does then it removes the "Username: " part and returns only the username
    std::string checkIfLineOfUserDatabaseHoldsAUsername(std::string lineOfUserDatabase) {
        std::string singleLine = lineOfUserDatabase;
        if (lineOfUserDatabase[0] == 'U') {
            singleLine = lineOfUserDatabase.replace(0, 10, "");
            return singleLine;
        }
        return "";
    }

    //resets database back to the first line to avoid bugs and problems
    void resetDatabaseLinesBackToTheFirstLine() {
        accessToUserDatabaseRegisterVersion.clear();
        accessToUserDatabaseRegisterVersion.seekg(0);
    }


    //goes through every line of the database and checks if the username's in the files match the username the user requested
    bool getEveryLineOfUserDatabase() {
        std::string lineOfUserDatabase;
        while (getline(accessToUserDatabaseRegisterVersion, lineOfUserDatabase)) {
            std::string previousUsernames = checkIfLineOfUserDatabaseHoldsAUsername(lineOfUserDatabase);
            if (previousUsernames == registerUsername) {
                resetDatabaseLinesBackToTheFirstLine();
                return false;
            }

        }
        resetDatabaseLinesBackToTheFirstLine();
        return true;
    }


    //checks if the username's in the files match the username the user requested and if so prints out the username is already taken message and asks for a new username since the old one is taken
    void checkIfRequestedUsernameIsAlreadyTaken() {
        bool isUsernameAUniqueUsername = false;
        while (isUsernameAUniqueUsername == false) {
            isUsernameAUniqueUsername = getEveryLineOfUserDatabase();
            if (isUsernameAUniqueUsername == false) {
                unfortunatelyThatUsernameIsAlreadyTakenMessage();
                inputForRegistrationUsername();
            }
        }
    }



    //prints out password must have more then seven characters message
    void displayMoreThenSevenCharactersMessageRule() {
        std::cout << "Your password must have more then seven characters" << std::endl;
    }


    //prints out password must have at least one number message
    void displayAtLeastOneNumberRegistrationMessageRule() {
        std::cout << "Your password must contain at least one number" << std::endl;
    }


    //prints both password requirement messages
    void displayAllRegistrationMessagePasswordRules() {
        displayMoreThenSevenCharactersMessageRule();
        displayAtLeastOneNumberRegistrationMessageRule();
    }


    //prints out request for password message
    void requestForRegistrationPasswordMessage() {
        std::cout << "Please input your requested password: ";
    }


    //user inputs their requested password
    void inputForRegistrationPassword() {
        std::cin >> registerPassword;
    }


    //checks if the password the user requested is larger then seven characters, if it is not then calls the seven characters rule message and returns that the rule was broken
    int checkIfRegistedPasswordHasMoreThenSevenCharacters(int rulesBrokenCountForFunction) {
        if (registerPassword.size() < 7) { displayMoreThenSevenCharactersMessageRule(); return ++rulesBrokenCountForFunction; }
        return rulesBrokenCountForFunction;
    }


    //checks if the password the user requested has at least one number, if it is not then calls the at least one number rule message and returns that the rule was broken
    int checkIfRegistedPasswordHasAtLeastOneNumber(int rulesBrokenCountForFunction) {
        for (int i = 0; i < registerPassword.size(); i++)
            if (registerPassword[i] >= '0' && registerPassword[i] <= '9') { return rulesBrokenCountForFunction; }


        //if no number is found then we will return false and display the rule message for having at least one number
        displayAtLeastOneNumberRegistrationMessageRule();
        return ++rulesBrokenCountForFunction;
    }


    //checks if requested password matches all the rules, if not then it will circle back round and keep repeating the process until all password rules are met
    void checkIfRegistedPasswordMatchesPasswordRules() {  
        int rulesBrokenCountCheck = 0;
        do {
            rulesBrokenCountCheck = 0;
            rulesBrokenCountCheck = checkIfRegistedPasswordHasMoreThenSevenCharacters(rulesBrokenCountCheck);
            rulesBrokenCountCheck = checkIfRegistedPasswordHasAtLeastOneNumber(rulesBrokenCountCheck);
            if (rulesBrokenCountCheck > 0) { requestForRegistrationPasswordMessage(); inputForRegistrationPassword(); }
        } while (rulesBrokenCountCheck > 0);

    }


    //writes the password and username that the user requested into the database
    void writePasswordAndUsernameToUserDatabaseFile() {
        std::ofstream accessToAppendUserDatabase("users_database.txt", std::ios::app);

        if (accessToAppendUserDatabase.fail()) {
            throw "Unable to access user database";
        }
        accessToAppendUserDatabase << "Username: " << registerUsername << "\nPassword: " << registerPassword << std::endl;

        accessToAppendUserDatabase.close();
    }

}







//Introduction to the application. Only used once at the start of the application
void introduction() {
    std::cout << "Welcome to the login and registration system" << std::endl;
}



//Outputs message to user to find out if they want to login or register
void requestCommandFromUser() {
    std::cout << "Please type login to login to your user." << std::endl;
    std::cout << "Please type register to register a new user." << std::endl;
    std::cout << "Please type quit to quit this application." << std::endl;
}



//After requestCommandFromUser(), gets the command from the user for what they want to do, either login or register
std::string getCommandFromUser() {
    std::string command;
    std::cin >> command;
    return command;
}



//prints can you try that again message
void sorryCanYouTryThatAgainMessage() {
    std::cout << "Sorry can you please try that again please" << std::endl;
}


//calls all base functions required for login
void tryToCallLoginCommand() {
    try {
        loginNamespace::welcomeUserToLogin();
        loginNamespace::requestForUsernameMessage();
        loginNamespace::inputForUsername();
        loginNamespace::requestForPasswordMessage();
        loginNamespace::inputForPassword();
        loginNamespace::getEveryLineOfUserDatabase();

    }
    catch(std::string error){
        std::cout << error << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error" << std::endl;
    }
}




//calls input for registration username and if there is an error catch it
void tryToCallinputForRegistrationUsername() {
    try {
        registrationNamespace::inputForRegistrationUsername();
    }
    catch (...) {
        std::cout << "Problem with username input" << std::endl;
    }
}



//calls all base functions for registration
void tryToCallRegisterForUsernameCommand() {
    try {
        registrationNamespace::welcomeUserToRegistrationMessage();
        registrationNamespace::requestForRegistrationNameMessage();
        tryToCallinputForRegistrationUsername();
        registrationNamespace::checkIfRequestedUsernameIsAlreadyTaken();
    }
    catch (std::string error) {
        std::cout << error << std::endl;
    }
}




//calls input for registration password and if there is an error catches it
void tryToCallInputForRegistrationPassword() {
    try {
        registrationNamespace::displayAllRegistrationMessagePasswordRules();
        registrationNamespace::requestForRegistrationPasswordMessage();
        registrationNamespace::inputForRegistrationPassword();
        registrationNamespace::checkIfRegistedPasswordMatchesPasswordRules();
        registrationNamespace::writePasswordAndUsernameToUserDatabaseFile();
    }
    catch (...) {
        std::cout << "Problem with password input" << std::endl;
    }
}




//will start the command calling depending on what is returned to this function
void checkIfCommandInputIsCorrect(std::string checkCommand) {
    if (checkCommand == "login") { tryToCallLoginCommand(); }
    else if (checkCommand == "register") {
        tryToCallRegisterForUsernameCommand(); tryToCallInputForRegistrationPassword();
    }
    else if (checkCommand == "quit") { exit(0); }
    else { throw "Wrong input"; }
}






//tryToRunApplication runs the two functions (requestCommandFromUser and getCommandFromUser) and if there are any problems will run them again
std::string tryToGetCommand() {
    std::string command;
    while (true) {
        try {
            requestCommandFromUser();
            command = getCommandFromUser();
            checkIfCommandInputIsCorrect(command);
        }
        catch (...) {
            sorryCanYouTryThatAgainMessage();
            continue;
        }
        break;
    }
    return command;
}






int main()
{    
    introduction();
    while (true) {
        tryToGetCommand();
    }
    
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
