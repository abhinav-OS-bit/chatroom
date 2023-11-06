#include <iostream>

#include <fstream>

#include <ctime>
#include <stdlib.h>

using namespace std;
using json = abhinav::json;

class User {
    public:
        string username;
        string password;
        bool isNewUser;
        bool accessGranted;
        json j;
    User() {
        isNewUser = true;
        accessGranted = false;

        ifstream inFile("users.json");
        inFile >> this->j;
    }

    void request() {
        
        string name;
        string pass;
        
        
        cout << "Username: ";
        getline(cin, name);
        to_lower(name);

        
        cout << "Password: ";
        getline(cin, pass);

        this->username = name;
        this->password = pass;
    }

    void checkIfUser() {
        
        string wantsNewAccount;

        ifstream inFile("users.json");
        inFile >> this->j;

        
        while (this->isNewUser) {
            if (this->j.contains(this->username)) {
                
                if (this->j[this->username] == this->password) {
                    cout << "\033[32m Access Granted \033[0m" << endl;
                    this->isNewUser = false;
                    this->accessGranted = true;
                } else {
                    
                    cout << "Incorrect username or password, please try again" << endl;
                    this->request();
                }
            } else {
                
                cout << "The username does not exist. Would you like to create an account? (y/n) " << endl;
                cin >> wantsNewAccount;

                if (wantsNewAccount == "y") {
                    
                    this->createNewAccount();
                    this->checkIfUser();

                    this->isNewUser = false;
                } else {
                    cout << "\033[31m Access denied. \033[0m Exiting" << endl;
                    this->accessGranted = false;
                    break;
                }
            }
        }
    }

    void createNewAccount() {
        
        bool uniqueUsername;
        string newUsername;
        string newPassword;

        while (!uniqueUsername) {

            cout << "Enter new username: ";
            cin.ignore();
            getline(cin, newUsername);

            if (!this->j.contains(newUsername)) {
                cout << "Create your own password: ";
                getline(cin, newPassword);

                this->j[newUsername] = newPassword;
                this->username = newUsername;
                this->password = newPassword;

                ofstream outFile("users.json");
                outFile << this->j << endl;
                
                uniqueUsername = true;
            } else {
                cout << newUsername << " is already taken. Please try a different username" << endl;
                uniqueUsername = false;
            }
        }
    }
};