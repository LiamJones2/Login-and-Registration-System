// Login and Registration System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>




std::fstream checkForAccessToUsersDatabase("users_database.txt");



//Ensures we do have access to database otherwise throw exception
void checkAccessToFileDatabase() {
    if (checkForAccessToUsersDatabase.fail()) {
        throw "Unable to access user database";
    }
}


//Namespace to login 
namespace loginNamespace {

    void welcomeUserToLogin() {
        std::cout << "Welcome to login" << std::endl;
    }





}


namespace registrationNamespace {
    std::string registerUsername;
    std::string registerPassword;





    void welcomeUserToRegistrationMessage() {
        std::cout << "Welcome to registration" << std::endl;
    }




    void requestForRegistrationNameMessage() {
        std::cout << "Please input your requested username: ";
    }



    void inputForRegistrationUsername() {
        std::cin >> registerUsername;
    }


    void checkIfRequestedUsernameIsAlreadyTaken() {
        std::string requestedUsername = registerUsername;
        std::string lineOfUserDatabase;
        while (getline(checkForAccessToUsersDatabase, lineOfUserDatabase)) {
            if (lineOfUserDatabase == requestedUsername)
                inputForRegistrationUsername();
        }
    }



    void displayMoreThenSevenCharactersMessageRule() {
        std::cout << "Your password must have more then seven characters" << std::endl;
    }



    void displayAtLeastOneNumberRegistrationMessageRule() {
        std::cout << "Your password must contain at least one number" << std::endl;
    }



    void displayAllRegistrationMessagePasswordRules() {
        displayMoreThenSevenCharactersMessageRule();
        displayAtLeastOneNumberRegistrationMessageRule();
    }



    void requestForRegistrationPasswordMessage() {
        std::cout << "Please input your requested password: ";
    }



    void inputForRegistrationPassword() {
        std::cin >> registerPassword;
    }






    int checkIfRegistedPasswordHasMoreThenSevenCharacters(int rulesBrokenCountForFunction) {
        if (registerPassword.size() < 7) { displayMoreThenSevenCharactersMessageRule(); return ++rulesBrokenCountForFunction; }
        return rulesBrokenCountForFunction;
    }

    int checkIfRegistedPasswordHasAtLeastOneNumber(int rulesBrokenCountForFunction) {
        for (int i = 0; i < registerPassword.size(); i++)
            if (registerPassword[i] >= '0' && registerPassword[i] <= '9') { return rulesBrokenCountForFunction; }


        //if no number is found then we will return false and display the rule message for having at least one number
        displayAtLeastOneNumberRegistrationMessageRule();
        return ++rulesBrokenCountForFunction;
    }

    void checkIfRegistedPasswordMatchesPasswordRules() {  
        int rulesBrokenCountCheck = 0;
        do {
            rulesBrokenCountCheck = 0;
            rulesBrokenCountCheck = checkIfRegistedPasswordHasMoreThenSevenCharacters(rulesBrokenCountCheck);
            rulesBrokenCountCheck = checkIfRegistedPasswordHasAtLeastOneNumber(rulesBrokenCountCheck);
            if (rulesBrokenCountCheck > 0) { requestForRegistrationPasswordMessage(); inputForRegistrationPassword(); }
        } while (rulesBrokenCountCheck > 0);

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
}



//After requestCommandFromUser(), gets the command from the user for what they want to do, either login or register
std::string getCommandFromUser() {
    std::string command;
    std::cin >> command;
    return command;
}




void sorryCanYouTryThatAgainMessage() {
    std::cout << "Sorry can you please try that again" << std::endl;
}






void callWelcomeToLoginCommand() {
    loginNamespace::welcomeUserToLogin();
}





void tryToCallLoginCommand() {
    try {
        callWelcomeToLoginCommand();
    }
    catch(std::string error){
        std::cout << error << std::endl;
    }
}








void callCheckAccessToFileDatabaseCommand() {
    try {
        checkAccessToFileDatabase();
    }
    catch (...) {
        _exit;
    }
}

void tryToCallinputForRegistrationUsername() {
    try {
        registrationNamespace::inputForRegistrationUsername();
    }
    catch (...) {

    }
}

void tryToCallRegisterForUsernameCommand() {
    try {
        callCheckAccessToFileDatabaseCommand();
        registrationNamespace::welcomeUserToRegistrationMessage();
        registrationNamespace::requestForRegistrationNameMessage();
        tryToCallinputForRegistrationUsername();
    }
    catch (std::string error) {
        std::cout << error << std::endl;
    }
}








void tryToCallInputForRegistrationPassword() {
    try {
        registrationNamespace::inputForRegistrationPassword();
    }
    catch (...) {

    }
}


void tryToCallRegisterForPasswordCommand() {
    try {
        registrationNamespace::displayAllRegistrationMessagePasswordRules();
        registrationNamespace::requestForRegistrationPasswordMessage();
        tryToCallInputForRegistrationPassword();
    }
    catch (...) {

    }
}



void runCheckIfPasswordMatchesAllRules() {
    registrationNamespace::checkIfRegistedPasswordMatchesPasswordRules();
}




void checkIfCommandInputIsCorrect(std::string checkCommand) {
    if (checkCommand == "login") { tryToCallLoginCommand(); }
    else if (checkCommand == "register") {
        tryToCallRegisterForUsernameCommand(); tryToCallRegisterForPasswordCommand();  runCheckIfPasswordMatchesAllRules();
    }
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
    tryToGetCommand();
    std::cout << "test" << std::endl;



    
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
