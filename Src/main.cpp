#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using 
    std::cout,
    std::cin,
    std::string,
    std::fstream,
    std::vector,
    std::istringstream,
    std::ios;

// Global variables
bool isRunning = true;
bool isLogin = false;
int latestId = 1;

fstream userFile;
fstream bookingFile;
string userFileName = "users.txt";
string bookingFileName = "booking.txt";


struct UserInfo{
    int id;
    string username ;
    string password; 
};

struct Booking{
    int id;
    string name;
};

int nextId(){
    return latestId;
}

void nextLine(){
    cout << '\n';
}

void displayMenu(vector<string> menuOptions)
{
    for(int i = 0; i < menuOptions.size(); i++)
    {
        cout << "[" << (i + 1) << "] " << menuOptions[i] << '\n';
    }
}

void checkFileOpen(fstream& file, string fileName)
{
    if(!file.is_open())
    {
        cout << "File not found: " << fileName << '\n';
        exit(1);
    }
}

string getUserInput(string prompt)
{
    string input;
    cout << prompt;
    cin >> input;

    return input;
}

vector<string> readFromFile(fstream& file, string& fileName)
{
    vector<string> text;
    string line;
    int amoutOfLines = 0;

    file.open(fileName, ios::in);
    checkFileOpen(file, fileName);
    
    while(getline(file, line))
    {
        text.push_back(line);
        amoutOfLines++;
    }
    
    if(amoutOfLines > 0)
        latestId = amoutOfLines;
        
    file.close();

    return text;
}

void writeToFile(fstream& file, string& fileName, vector<string> input)
{
    file.open(fileName, ios::out | ios::app);
    checkFileOpen(file, fileName);

    for(string text : input)
        file << text << '\n';
    
    file.close();
}

void getBookings(){
    
}

vector<UserInfo> getUsers()
{
    vector<UserInfo> users;
    for(string text: readFromFile(userFile, userFileName))
    {
        UserInfo user;
        istringstream iss(text);   
        iss >> user.id >> user.username >> user.password;
        users.push_back(user);
    }
    return users;
}

bool verifyUser(UserInfo& input)
{
    for(UserInfo user : getUsers())
        if(user.username == input.username && user.password == input.password)
            return true;
        
    
    return false;
}

void printMessage(string message)
{
    cout << message << '\n';
}

void registration(UserInfo input)
{
    if(verifyUser(input))
    {
        printMessage("User already exist");
        return;
    }
    input.id = nextId();
    
    writeToFile(userFile, userFileName, {std::to_string(input.id), input.username, input.password});
    // Get user input
    // else create user
    // Check if user already exist
}

UserInfo inputUserInfo(){
    UserInfo input;
    input.username = getUserInput("Enter your username: ");
    input.password = getUserInput("Enter your password: ");

    return input;
}

void login(UserInfo input){    
    if(!verifyUser(input))
    {
        printMessage("Login failed");
        return;
    }
    
    printMessage("Login successful");
    isLogin = true;   
}

void logout(){
    isLogin = false;
}

void bookingMenuSelection(string userInput){
    if(userInput == "1"){
        cout << "Add booking" <<'\n';
    } else if(userInput == "2"){
        getBookings();
        cout << "Reservations" << '\n';
    } else if (userInput == "3"){
        cout << "Remove reservation" << '\n';
    } else if (userInput == "4"){
        cout << "Change reservation" << '\n';
    } else if (userInput == "5"){
        isLogin = false;
    }
    else {
        cout << "Invalid selection. Try again." << '\n';
    }
}

void bookingLoop(){
    while(isLogin){
        displayMenu({"Add booking","Check your Reservations", "Remove reservation", "Update reservation", "Logout"});
        bookingMenuSelection(getUserInput("Enter your selection: "));
    }
}

void handleUserSelection(string input){
    if(input == "1")
    {
        login(inputUserInfo());
        bookingLoop();
    }

    else if(input == "2")
    {
        registration(inputUserInfo());
    }

    else if(input == "3")
    {
        cout << "Exit" << '\n';
    }
    else
        cout << "Invalid input. Please try again." << '\n';
    
    nextLine();
}



void loginLoop(){
    while(isRunning)
    {
        displayMenu({"Login", "Register", "Exit"});
        handleUserSelection(getUserInput("Enter your selection: "));  
    }
}

// Main function
int main (){
    loginLoop();
}