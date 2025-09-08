#ifndef SQLITE_HELPER_H
#define SQLITE_HELPER_H

#include <sqlite3.h>
#include <string>

// Open or create a database
sqlite3* openDatabase(const std::string& dbName);

// Create USERS table if it doesn't exist
bool createTable(sqlite3* db);

// Insert a new user
bool insertUser(sqlite3* db,
                long long account_number,
                const std::string& first_name,
                const std::string& last_name,
                const std::string& dob,
                const std::string& gender,
                const std::string& address,
                const std::string& phone,
                double balance,
                const std::string& pin);

// Retrieve all users
void getAllUsersPrepared(sqlite3* db);

// Retrieve a single user by account number
void getUserByAccountNumber(sqlite3* db, long long account_number);

std::string getUserField(sqlite3* db, long long account_number, const std::string& field_name);

std::string getAdminField(sqlite3* db, const std::string& username, const std::string& field);

// Update a single field for a user
bool updateField(sqlite3* db, long long account_number, const std::string& field, const std::string& value);

// Delete one user (by account number) or all users
bool deleteUser(sqlite3* db, long long account_number);

#endif // SQLITE_HELPER_H
