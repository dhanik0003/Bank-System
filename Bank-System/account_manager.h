#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include "account.h"
#include <string>

bool createAccount_db(const Account& acc);
bool check_useraccount_db(std::string& acc_number, std::string& password);
bool check_adminaccount_db(std::string username, std::string password);
std::string retrieve_admin_db(int choice);
std::string retrieve_user_db(std::string acc_number, int choice);
#endif