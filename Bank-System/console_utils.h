#ifndef BANK_UTILS_H
#define BANK_UTILS_H

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <limits>

using namespace std;

// Only declarations here
void setcolor(WORD color);
void bank_system_header(WORD color = 3);
void thank_you_header(WORD color = 11);
void main_menu_header(WORD color = 6);
void create_account_header(WORD color = 1);
void user_login_header(WORD color = 1);
void admin_login_header(WORD color = 12);
void typing_effect(const string &text, int duration = 50);
void loading_animation(string text = "Loading", int speed = 250, int duration = 8);
void setCursorPosition(int x, int y);
void clearLine(int y);
int getValidatedChoice(int lowerLimit, int upperLimit);

#endif
