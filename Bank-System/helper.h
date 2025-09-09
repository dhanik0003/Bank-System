#ifndef HELPER_H
#define HELPER_H

#pragma once

#include <string>
#include "account.h"

long long generateAccountNumber();
std::string getDOB();
std::string getfname();
std::string getlname();
std::string getGender();
std::string getAddress();
std::string getPhone();
std::string getPin();
std::string getPIN_once();
double getdeposit(std::string prompt = "Enter Initial Deposit Amount: $");
bool admin_initial_login(std::string& admin_username,std::string& admin_password);
bool user_initial_login(std::string& acc_number, std::string& password);

#endif