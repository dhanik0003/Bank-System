#define NOMINMAX
#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream> 
#include <limits>
#include <conio.h>
#include "console_utils.h"
#include "helper.h"
#include "account_manager.h"
#include "account.h"
#include "sqlite3.h"
#include "sqlite_helper.h"

using namespace std;

bool createAccount_db(const Account& acc)
{
    sqlite3* db = openDatabase("bank_server.db");

    if (!db) return false;

    if (!createTable(db)) {
        sqlite3_close(db);
        return false;
    }

    bool result = insertUser(db, acc.accountNumber, acc.firstName, acc.lastName, acc.dob, acc.gender, acc.address, acc.phone, acc.deposit, acc.pin);
    
    sqlite3_close(db);
    return result;
}

bool check_useraccount_db(std::string& accnumber, std::string& password)
{
    sqlite3* db = openDatabase("bank_server.db");

    long long acc_number = std::stoll(accnumber);

    if(accnumber == getUserField(db, acc_number, "ACCOUNT_NUMBER") && password == getUserField(db, acc_number, "PIN"))
    {
        sqlite3_close(db);
        return true;
    }
    else
    {
        sqlite3_close(db);
        return false;
    }   
}

bool check_adminaccount_db(std::string username, std::string password)
{
    sqlite3* db = openDatabase("bank_server.db");
    if(username == getAdminField(db, username, "USERNAME") && password == getAdminField(db, username, "PIN"))
    {
        sqlite3_close(db);
        return true;
    }
    else
    {
        sqlite3_close(db);
        return false;
    }
    return true;
}

string retrieve_user_db(std::string accnumber, int choice)
{
    sqlite3* db = openDatabase("bank_server.db");
    long long acc_number = std::stoll(accnumber);

    switch (choice)
    {
    case 1: {
        cout << "Balance Amount: ";
        string result = getUserField(db, acc_number, "BALANCE");
        sqlite3_close(db);
        return result;
    }
    case 2: {
        double balance = stod(getUserField(db, acc_number, "BALANCE"));
        double amount = getdeposit("Enter amount to deposit: $");
        balance += amount;
        updateField(db, acc_number, "BALANCE", to_string(balance));
        sqlite3_close(db);
        return "Deposit Successful";
    }
    case 3: {
        double balance = stod(getUserField(db, acc_number, "BALANCE"));
        double amount;
        amount = getdeposit("Enter amount to withdraw: $");
        if (amount > balance) {
            sqlite3_close(db);
            return "Insufficient Funds";
        }
        balance -= amount;
        updateField(db, acc_number, "BALANCE", to_string(balance));
        sqlite3_close(db);
        return "Withdraw Successful";
    }
    case 4: {
        string pin = getPIN_once();
        updateField(db, acc_number, "PIN", pin);
        sqlite3_close(db);
        return "PIN Changed Successfully";
    }
    case 5: {
        string fname = getfname();
        updateField(db, acc_number, "FIRST_NAME", fname);
        string lname = getlname();
        updateField(db, acc_number, "LAST_NAME", lname);
        sqlite3_close(db);
        return "Name Changed Successfully";
    }
    case 6: {
        sqlite3_close(db);
        return "Logged Out Successfully";
    }
    default: {
        sqlite3_close(db);
        return "Error in retrieving data";
    }
    }
}

std::string retrieve_admin_db(int choice)
{
    sqlite3* db = openDatabase("bank_server.db");
    if (!db) return "Database connection failed";

    std::string result;

    switch (choice)
    {
        case 1: {
            std::cout << "All User Accounts:" << std::endl;
            getAllUsersPrepared(db); // prints all users
            result = "Displayed all accounts.";
            break;
        }
        case 2: {
            long long accNum;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hConsole, &csbi);
            int curX = csbi.dwCursorPosition.X;
            int curY = csbi.dwCursorPosition.Y;

            while (true) {
                std::string input;
                std::cout << "Enter Account Number to delete: ";
                std::getline(std::cin, input);

                std::stringstream ss(input);
                if (!(ss >> accNum)) {
                    // Invalid input, clear line and set cursor back
                    clearLine(curY);
                    setCursorPosition(0, curY);
                    std::cout << "Invalid Account Number! Enter again: ";
                    continue;
                }

                // valid number
                break;
            }
            deleteUser(db, accNum);
            result = "Account deleted successfully.";
            break;
        }
        case 3: {
            long long accNum;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hConsole, &csbi);
            int curX = csbi.dwCursorPosition.X;
            int curY = csbi.dwCursorPosition.Y;

            while (true) {
                std::string input;
                std::cout << "Enter Account Number: ";
                std::getline(std::cin, input);

                std::stringstream ss(input);
                if (!(ss >> accNum)) {
                    // Invalid input, clear line and set cursor back
                    clearLine(curY);
                    setCursorPosition(0, curY);
                    std::cout << "Invalid Account Number! Enter again: ";
                    continue;
                }

                // valid number
                break;
            }

        int choice;
        std::cout << "Select field to update:\n";
        std::cout << "1. FIRST_NAME\n";
        std::cout << "2. LAST_NAME\n";
        std::cout << "3. DOB\n";
        std::cout << "4. GENDER\n";
        std::cout << "5. ADDRESS\n";
        std::cout << "6. PHONE\n";
        std::cout << "7. BALANCE\n";
        std::cout << "8. PIN\n";
        std::cout << "Enter choice: ";
        choice = getValidatedChoice(1,8);

        std::string field, value;

        
        switch(choice) {
            case 1:
                
                field = "FIRST_NAME";
                value = getfname();
                break;
            case 2:
            
            field = "LAST_NAME";
            value = getlname();
            break;
        case 3:
            
            field = "DOB";
            value = getDOB();
            break;
        case 4:
            
            field = "GENDER";
            value = getGender();
            break;
        case 5:
            
            field = "ADDRESS";
            value = getAddress();
            break;
        case 6:
            
            field = "PHONE";
            value = getPhone();
            break;
        case 7:
            
            field = "BALANCE";
            value = to_string(getdeposit("Enter new BALANCE(Number only): $"));
            break;
        case 8:
            
            field = "PIN";
            value = getPIN_once();
            break;
        default:
            std::cout << "Invalid choice!\n";
            field = "";
            value = "";
            break;
        }

        if(!field.empty()) {
            updateField(db, accNum, field, value);
            result = "User details updated successfully.";
        }

        break;
}

        case 4: {
            deleteUser(db, -1); // -1 clears all users
            result = "Database cleared successfully.";
            break;
        }
        case 5:
            result = "Logged out successfully.";
            break;
        default:
            result = "Invalid admin operation.";
            break;
    }

    sqlite3_close(db);
    return result;
}
