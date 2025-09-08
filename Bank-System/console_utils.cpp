#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <sstream>
#include "console_utils.h"
#include "art.h"



void setcolor(WORD color) { 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hConsole, color); // complete color change of text in console 
    /*[BLACK=0, BLUE=1, GREEN=2, CYAN=3, RED=4, MAGENTA=5, YELLOW=6, LIGHT_GRAY=7, DARK_GRAY=8, LIGHT_BLUE=9, 
    LIGHT_GREEN=10, LIGHT_CYAN-11, LIGHT_RED-12, LIGHT_MAGENTA-13, LIGHT_YELLOW=14, WHITE=15]*/
}

void bank_system_header(WORD color)
{
    setcolor(color);
    system("CLS");
    Startup_logo();
    setcolor(15);
}

void thank_you_header(WORD color)
{
    setcolor(color);
    system("CLS");
    thank_you_logo();
    setcolor(15);
}

void main_menu_header(WORD color)
{
    setcolor(color);
    system("CLS");
    main_menu_logo();
    setcolor(15);
}

void create_account_header(WORD color)
{
    setcolor(color);
    system("CLS");
    create_account_logo();
    setcolor(15);
}

void user_login_header(WORD color)
{
    setcolor(color);
    system("CLS");
    user_login_logo();
    setcolor(15);
}

void admin_login_header(WORD color)
{
    setcolor(color);
    system("CLS");
    admin_login_logo();
    setcolor(15);
}

void typing_effect(const string &text, int duration)
{
    setcolor(10);
    for (char c : text) {
        cout << c << flush;   // print one char at a time
        Sleep(duration);         // wait (ms) before next char
    }
    cout << endl; // move to next line after text
    setcolor(15);
}

void loading_animation(string text, int speed, int duration) {
    setcolor(6);
    time_t start = time(0);  // Start time
    while (difftime(time(0), start) < duration) {  // Run for 8 seconds
        for (int i = 1; i <= 3; i++) {
            cout << "\r"<<text;   // carriage return, move to line start
            for (int j = 0; j < i; j++) {
                cout << ".";
            }
            cout << "   "; // clear extra dots if any
            cout.flush();
            Sleep(speed); // control speed
        }
    }
    Sleep(2000);
    setcolor(15);
}

// Move cursor to specific position
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Clear the current line
void clearLine(int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD written;
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, {0, (SHORT)y}, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, csbi.dwSize.X, {0, (SHORT)y}, &written);
}

// Validated input that erases previous input
int getValidatedChoice(int lowerLimit, int upperLimit) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int curX = csbi.dwCursorPosition.X;
    int curY = csbi.dwCursorPosition.Y;

    string input;
    int choice;

    while (true) {
        getline(cin, input);

        // Handle blank input
        if (input.empty()) {
            clearLine(curY);
            setCursorPosition(0, curY);
            cout << "Input cannot be blank! Enter a number between "
                 << lowerLimit << " and " << upperLimit << ": " << flush;
            continue;
        }

        // Try to convert input to integer
        stringstream ss(input);
        if (!(ss >> choice) || (choice < lowerLimit || choice > upperLimit)) {
            clearLine(curY);
            setCursorPosition(0, curY);
            cout << "Invalid input! Enter a number between "
                 << lowerLimit << " and " << upperLimit << ": " << flush;
            continue;
        }

        return choice;
    }
}