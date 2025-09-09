#define NOMINMAX
#include <iostream>
#include <string>
#include <random>
#include <conio.h>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <regex>
#include <sstream>
#include "helper.h"
#include "console_utils.h"

using namespace std;


bool isValidFirstName(const string& fname) {
    if (fname.empty()) return false;  // cannot be empty
    regex namePattern("^[A-Za-z]+([ '-][A-Za-z]+)*$");  
    return regex_match(fname, namePattern);
}

bool isValidLastName(const string& lname) {
    if (lname.empty()) return true;  // last name is optional
    regex namePattern("^[A-Za-z]+([ '-][A-Za-z]+)*$");
    return regex_match(lname, namePattern);
}

bool isValidPhone(const string& ph) {
    string phone = ph;
    // Trim leading and trailing spaces
    phone.erase(phone.begin(), find_if(phone.begin(), phone.end(), [](int ch) {
        return !isspace(ch);
    }));
    phone.erase(find_if(phone.rbegin(), phone.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), phone.end());

    if (phone.empty()) return false;           // reject empty input
    if (phone.length() != 10) return false;    // must be exactly 10 digits
    if (!isdigit(phone[0])) return false;      // first char must be a digit
    if (phone[0] == '0') return false;        // cannot start with 0
    if (phone[0] < '6') return false;         // must start with 6-9
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isValidDOB(const string& dob) {
    // check format with regex dd/mm/yyyy
    regex dobPattern(R"(^\d{2}/\d{2}/\d{4}$)");
    if (!regex_match(dob, dobPattern)) {
        return false;
    }

    int day, month, year;
    char sep1, sep2;
    istringstream iss(dob);
    iss >> day >> sep1 >> month >> sep2 >> year;

    if (sep1 != '/' || sep2 != '/') return false;

    // validate ranges
    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2025) return false; // adjust as needed

    // days per month
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // leap year check for February
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeap) daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1]) return false;

    // get today's date
    time_t t = time(0);
    tm *now = localtime(&t);
    int curDay = now->tm_mday;
    int curMonth = now->tm_mon + 1; // tm_mon is 0-based
    int curYear = now->tm_year + 1900;

    // reject if DOB is in the future or today
    if (year > curYear) return false;
    if (year == curYear && month > curMonth) return false;
    if (year == curYear && month == curMonth && day >= curDay) return false;

    return true;
}

bool isValidAddress(const string& addr) {
    // Must not be empty and should contain at least one non-space character
    if (addr.empty()) return false;

    for (char c : addr) {
        if (!isspace(c)) return true;  // found a valid character
    }
    return false; // only spaces
}

bool isValidPIN(const string& pin) {
    if (pin.empty()) return false;                // must not be empty
    if (pin.length() != 4 && pin.length() != 6) return false; // 4 or 6 digits only

    for (char c : pin) {
        if (!isdigit(c)) return false;           // only digits allowed
    }

    return true;
}

bool isValidAmt(const string& amtStr) {
    if (amtStr.empty()) return false;

    bool decimalPointFound = false;
    for (size_t i = 0; i < amtStr.size(); ++i) {
        char c = amtStr[i];
        if (c == '.') {
            if (decimalPointFound) return false; // more than 1 dot
            decimalPointFound = true;
        } else if (!isdigit(c)) {
            return false; // non-digit character
        }
    }

    // Convert string to double
    double amt;
    stringstream ss(amtStr);
    ss >> amt;
    if (ss.fail() || !ss.eof()) return false; // invalid number
    if (amt <= 0) return false;              // must be positive

    // Optional: limit to 2 decimal places
    if (decimalPointFound) {
        size_t dotPos = amtStr.find('.');
        if (amtStr.length() - dotPos - 1 > 2) return false;
    }

    return true;
}

bool isValidAccountNumber(const std::string& accNum) {
    if (accNum.empty()) return false;

    // every character must be a digit
    for (char c : accNum) {
        if (!isdigit(c)) return false;
    }

    //disallow leading zeros
    if (accNum.size() > 1 && accNum[0] == '0') return false;

    if (accNum.length() < 10 || accNum.length() > 12) return false;

    return true;
}

bool isValidAdminCredential(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) return false;
    if (username[0] == ' ' || password[0] == ' ') return false;
    return true;
}

long long generateAccountNumber() {
    static std::mt19937 rng(
        std::chrono::system_clock::now().time_since_epoch().count()
    );

    // Decide length: either 10 or 12
    std::uniform_int_distribution<int> lenDist(0, 1);
    int length = (lenDist(rng) == 0) ? 10 : 12;

    std::uniform_int_distribution<int> digitDist(0, 9);

    std::string accNum;
    accNum.reserve(length);

    for (int i = 0; i < length; i++) {
        accNum += std::to_string(digitDist(rng));
    }

    // Ensure first digit is not 0
    if (accNum[0] == '0') {
        accNum[0] = '1' + digitDist(rng) % 9; // 1–9
    }

    // Convert safely to long long
    return std::stoll(accNum);
}


string getDOB()
{
    string dob;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;

    cout<<"Date of Birth(dd/mm/yyyy): ";
    
    do
    {
        setcolor(8);
        getline(cin,dob);
        setcolor(10);

        if(!isValidDOB(dob)){
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout<<"Invalid DOB";
            setCursorPosition(0, curY+1);
            cout<<"Enter DOB of format dd/mm/yyyy:";

        }
        else{
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout<<"Date of Birth(dd/mm/yyyy): "<<dob<<endl;
        }

    }while(!isValidDOB(dob));

    return dob;
}

string getfname()
{
    string f_name;

    // First Name
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  

    do
    {
        cout<<"First Name: ";
        setcolor(8);
        getline(cin,f_name);
        setcolor(10);

        if(!isValidFirstName(f_name)){
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout<<"Invalid First Name!";
            setCursorPosition(0, curY+1);
        }
        else{
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout<<"First Name: "<<f_name<<endl;
        }

    }while(!isValidFirstName(f_name));

    return f_name;
}
string getlname()
{

    string l_name="";

    // Last Name
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  

    do
    {
        cout<<"Last Name(optional): ";
        setcolor(8);
        getline(cin,l_name);
        setcolor(10);

        if(!isValidLastName(l_name)){
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout<<"Invalid Last Name!";
            setCursorPosition(0, curY+1);
        }
        else{
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout<<"Last Name: "<<l_name<<endl;
        }
    }while(!isValidLastName(l_name));

    return l_name;
}

string getGender()
{
    string input;
    while (true) {
        cout << "Gender (Male/Female/Others or M/F/O): ";
        cin >> input;

        // convert input to lowercase for easy comparison
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "m" || input == "male") {
            return "Male";
        } 
        else if (input == "f" || input == "female") {
            return "Female";
        } 
        else if (input == "o" || input == "others" || input == "other") {
            return "Others";
        } 
        else {
            cout << "Invalid input. Please enter M/F/O or Male/Female/Others." << endl;
        }
    }
}

string getAddress()
{
    string address;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    do
    {
        cout << "Address: ";
        setcolor(8);
        getline(cin, address);
        setcolor(10);

        if (!isValidAddress(address)) {
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout << "Invalid Address!";
            setCursorPosition(0, curY+1);
        }
        else {
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout << "Address: " << address << endl;
        }

    } while (!isValidAddress(address));

    return address;
}

string getPhone()
{
    string ph;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  

    do
    {
        cout<<"Phone Number: ";
        setcolor(8);
        getline(cin,ph);
        setcolor(10);

        if(!isValidPhone(ph)){
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout<<"Invalid Phone Number!";
            setCursorPosition(0, curY+1);
        }
        else{
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout<<"Phone Number: "<<ph<<endl;
        }

    }while(!isValidPhone(ph));

    return ph;
}

string masking_input(const string& prompt = "Enter password: ") {
    string password;  // local variable to store input
    char ch;

    cout << prompt;
    setcolor(8);
    while ((ch = _getch()) != 13) { // 13 = Enter key
        if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                setcolor(10);
                cout << "\b \b"; // erase last '*'
            }
        } else {
            password.push_back(ch);
            setcolor(10);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

string getPin()
{
    string pin, p1, p2;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  

    do
    {
       
        p1 = masking_input("Enter Security PIN: ");
        

        p2 = masking_input("Re-enter Security PIN: ");       

        if (!isValidPIN(p1)) {
            clearLine(curY);
            clearLine(curY + 1);
            clearLine(curY + 2);
            setCursorPosition(0, curY);
            cout << "Invalid PIN! Must be 4 or 6 digits.";
            setCursorPosition(0, curY + 1);
        }
        else if (p1 != p2) {
            clearLine(curY);
            clearLine(curY + 1);
            clearLine(curY + 2);
            setCursorPosition(0, curY);
            cout << "PINs do not match!";
            setCursorPosition(0, curY + 1);
        }
        else {
            pin = p1;
            clearLine(curY);
            clearLine(curY + 1);
            clearLine(curY + 2);
            setCursorPosition(0, curY);
            cout << "Security PIN: " << pin << endl;
        }

    } while (!isValidPIN(p1) || p1 != p2);

    return pin;
}

string getPIN_once()
{
    string p1;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  

    do
    {
       
        p1 = masking_input("Enter Security PIN: ");

        if (!isValidPIN(p1)) {
            clearLine(curY);
            clearLine(curY + 1);
            clearLine(curY + 2);
            setCursorPosition(0, curY);
            cout << "Invalid PIN! Must be 4 or 6 digits.";
            setCursorPosition(0, curY + 1);
        }

    } while (!isValidPIN(p1));

    return p1;
}

double getdeposit()
{
    string depositstr;
    double deposit = 0.0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  

    do
    {
        cout<<"Enter Initial Deposit Amount: $";
        setcolor(8);
        getline(cin,depositstr);
        setcolor(10);

        if (!isValidAmt(depositstr)) {
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout << "Invalid Amount!";
            setCursorPosition(0, curY+1);
        }
        else {
            deposit = stod(depositstr); // convert string to double
            clearLine(curY);
            clearLine(curY+1);
            setCursorPosition(0, curY);
            cout << "Enter Initial Deposit Amount: $" << deposit << endl;
        }

    } while (!isValidAmt(depositstr));

    return deposit;
}

bool user_initial_login(string& acc_number, string& password)
{
    cout<<"Enter the User Credentials to proceed further."<<endl;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  
    int i=0;
    string attempts_left[] = {"Last","Second","First"};
    do
    {
        cout<<"Account Number: ";
        setcolor(8);
        getline(cin,acc_number);
        setcolor(10);
        password = masking_input("Security PIN: ");

        if(!isValidAccountNumber(acc_number) || !isValidPIN(password)){
            clearLine(curY);
            clearLine(curY+1);
            clearLine(curY+2);
            clearLine(curY+3);
            setCursorPosition(0, curY);
            cout<<"Invalid Credentials!";
            setCursorPosition(0, curY+1);
            i++;
            if(i < 3)
                cout<<attempts_left[2-i]<<" Attempt";
            setCursorPosition(0, curY+2);
            if(i==3){
                clearLine(curY);
                clearLine(curY+1);
                clearLine(curY+2);
                clearLine(curY+3);
                clearLine(curY-1);
                setCursorPosition(0, curY-1);
                cout<<"Maximum Attempts Reached. Access Denied!"<<endl;
                return false;
            }
        }
        else{
            clearLine(curY);
            clearLine(curY+1);
            clearLine(curY+2);
            clearLine(curY+3);
            setCursorPosition(0, curY);
            return true;
        }

    }while(i<3);
    return false;
}

bool admin_initial_login(string& admin_username,string& admin_password)
{
    
    cout<<"Enter the Admin Credentials to proceed further."<<endl;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int curX = csbi.dwCursorPosition.X;  
    int curY = csbi.dwCursorPosition.Y;  
    int i=0;
    string attempts_left[] = {"Last","Second","First"};
    do
    {
        cout<<"Username: ";
        setcolor(8);
        getline(cin,admin_username);
        setcolor(10);
        admin_password = masking_input("Password: ");

        if(!isValidAdminCredential(admin_username, admin_password)){
            clearLine(curY);
            clearLine(curY+1);
            clearLine(curY+2);
            clearLine(curY+3);
            setCursorPosition(0, curY);
            cout<<"Invalid Credentials!";
            setCursorPosition(0, curY+1);
            i++;
            cout<<attempts_left[2-i]<<" Attempt";
            setCursorPosition(0, curY+2);
            if(i==3){
                clearLine(curY);
                clearLine(curY+1);
                clearLine(curY+2);
                clearLine(curY+3);
                clearLine(curY-1);
                setCursorPosition(0, curY-1);
                cout<<"Maximum Attempts Reached. Access Denied!"<<endl;
                return false;
            }
            
        }
        else{
            clearLine(curY);
            clearLine(curY+1);
            clearLine(curY+2);
            clearLine(curY+3);
            setCursorPosition(0, curY);
            return true;
        }

    }while(i<3 && (!isValidAdminCredential(admin_username, admin_password)));
    return false;
}