#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

// Function to open database
sqlite3* openDatabase(const string& dbName) {
    sqlite3* db;
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        cerr << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }
    cout << "Database opened successfully!" << endl;
    return db;
}

// Function to create USERS table
bool createTable(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS USERS("
                      "ACCOUNT_NUMBER INTEGER PRIMARY KEY, "
                      "FIRST_NAME TEXT NOT NULL, "
                      "LAST_NAME TEXT NOT NULL, "
                      "DOB TEXT NOT NULL, "
                      "GENDER TEXT NOT NULL, "
                      "ADDRESS TEXT NOT NULL, "
                      "PHONE TEXT NOT NULL, "
                      "BALANCE REAL NOT NULL, "
                      "PIN TEXT NOT NULL);";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Error creating table: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;  // return false on failure
    } 
    cout << "Table created (or already exists)." << endl;
    return true;  // success
}

// Function to insert user
bool insertUser(sqlite3* db,
                long long account_number,
                const string& first_name,
                const string& last_name,
                const string& dob,
                const string& gender,
                const string& address,
                const string& phone,
                double balance,
                const string& pin) 
{
    string sql = "INSERT INTO USERS (ACCOUNT_NUMBER, FIRST_NAME, LAST_NAME, DOB, GENDER, ADDRESS, PHONE, BALANCE, PIN) VALUES (" +
                 to_string(account_number) + ", '" +
                 first_name + "', '" +
                 last_name + "', '" +
                 dob + "', '" +
                 gender + "', '" +
                 address + "', '" +
                 phone + "', " +
                 to_string(balance) + ", '" +
                 pin + "');";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Error while creating account: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

    // Function to get all users (prepared statement)
void getAllUsersPrepared(sqlite3* db) {
    const char* sql = "SELECT ACCOUNT_NUMBER, FIRST_NAME, LAST_NAME, DOB, GENDER, ADDRESS, PHONE, BALANCE, PIN FROM USERS;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        long long account_number        = sqlite3_column_int64(stmt, 0);
        const unsigned char* first_name = sqlite3_column_text(stmt, 1);
        const unsigned char* last_name  = sqlite3_column_text(stmt, 2);
        const unsigned char* dob        = sqlite3_column_text(stmt, 3);
        const unsigned char* gender     = sqlite3_column_text(stmt, 4);
        const unsigned char* address    = sqlite3_column_text(stmt, 5);
        const unsigned char* phone      = sqlite3_column_text(stmt, 6);
        double balance            = sqlite3_column_double(stmt, 7);
        const unsigned char* pin        = sqlite3_column_text(stmt, 8);

        cout << "Account: " << account_number
             << ", Name: " << (first_name ? reinterpret_cast<const char*>(first_name) : "")
             << " " << (last_name ? reinterpret_cast<const char*>(last_name) : "")
             << ", DOB: " << (dob ? reinterpret_cast<const char*>(dob) : "")
             << ", Gender: " << (gender ? reinterpret_cast<const char*>(gender) : "")
             << ", Address: " << (address ? reinterpret_cast<const char*>(address) : "")
             << ", Phone: " << (phone ? reinterpret_cast<const char*>(phone) : "")
             << ", Balance: " << balance
             << ", PIN: " << (pin ? reinterpret_cast<const char*>(pin) : "")
             << endl;
    }

    sqlite3_finalize(stmt);
}


void getUserByAccountNumber(sqlite3* db, long long account_number) {
    const char* sql = "SELECT ACCOUNT_NUMBER, FIRST_NAME, LAST_NAME, DOB, GENDER, ADDRESS, PHONE, BALANCE, PIN FROM USERS WHERE ACCOUNT_NUMBER = ?;";
    sqlite3_stmt* stmt;

    // Prepare statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Bind the account_number parameter
    sqlite3_bind_int(stmt, 1, account_number);

    // Step once since we expect at most 1 row
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int acc_num                  = sqlite3_column_int(stmt, 0);
        const unsigned char* first   = sqlite3_column_text(stmt, 1);
        const unsigned char* last    = sqlite3_column_text(stmt, 2);
        const unsigned char* dob     = sqlite3_column_text(stmt, 3);
        const unsigned char* gender  = sqlite3_column_text(stmt, 4);
        const unsigned char* address = sqlite3_column_text(stmt, 5);
        const unsigned char* phone   = sqlite3_column_text(stmt, 6);
        double balance               = sqlite3_column_double(stmt, 7);
        const unsigned char* pin     = sqlite3_column_text(stmt, 8);

        cout << "Account: " << acc_num
             << ", Name: " << (first ? reinterpret_cast<const char*>(first) : "")
             << " " << (last ? reinterpret_cast<const char*>(last) : "")
             << ", DOB: " << (dob ? reinterpret_cast<const char*>(dob) : "")
             << ", Gender: " << (gender ? reinterpret_cast<const char*>(gender) : "")
             << ", Address: " << (address ? reinterpret_cast<const char*>(address) : "")
             << ", Phone: " << (phone ? reinterpret_cast<const char*>(phone) : "")
             << ", Balance: " << balance
             << ", PIN: " << (pin ? reinterpret_cast<const char*>(pin) : "")
             << endl;
    } else {
        cout << "No user found with Account Number: " << account_number << endl;
    }

    sqlite3_finalize(stmt);
}

std::string getUserField(sqlite3* db, long long account_number, const std::string& field_name) {
    std::string result;
    std::string sql = "SELECT " + field_name + " FROM USERS WHERE ACCOUNT_NUMBER = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    sqlite3_bind_int64(stmt, 1, account_number);  // <-- important for large account numbers

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        result = text ? reinterpret_cast<const char*>(text) : "";
    } else {
        std::cerr << "No user found with Account Number: " << account_number << std::endl;
    }

    sqlite3_finalize(stmt);
    return result;
}

// Get a specific field from ADMINS
string getAdminField(sqlite3* db, const string& username, const string& field) {
    string sql = "SELECT " + field + " FROM ADMINS WHERE USERNAME = ?;";
    sqlite3_stmt* stmt;
    string result = "";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return "";
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* val = sqlite3_column_text(stmt, 0);
        result = val ? reinterpret_cast<const char*>(val) : "";
    }

    sqlite3_finalize(stmt);
    return result;
}

// Update a specific field in ADMINS
bool updateAdminField(sqlite3* db, const string& username, const string& field, const string& value) {
    string sql = "UPDATE ADMINS SET " + field + " = ? WHERE USERNAME = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // All admin fields are TEXT
    sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    cout << "Admin updated successfully!" << endl;
    return true;
}

bool updateField(sqlite3* db, long long account_number, const string& field, const string& value) {
    // Use ACCOUNT_NUMBER in WHERE clause
    string sql = "UPDATE USERS SET " + field + " = ? WHERE ACCOUNT_NUMBER = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind value
    if (field == "BALANCE") {
        // numeric column
        sqlite3_bind_double(stmt, 1, stod(value));
    } else {
        // text columns
        sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_TRANSIENT);
    }

    // Bind account_number
    sqlite3_bind_int64(stmt, 2, account_number);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    cout << "User updated successfully!" << endl;
    return true;
}

bool deleteUser(sqlite3* db, long long account_number = -1) {
    string sql;
    if (account_number == -1) {
        // No account_number passed → delete everything
        sql = "DELETE FROM USERS;";
    } else {
        // Delete only the specified account
        sql = "DELETE FROM USERS WHERE ACCOUNT_NUMBER = " + to_string(account_number) + ";";
    }

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Delete failed: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }

    if (account_number == -1)
        cout << "All rows deleted from USERS table." << endl;
    else
        cout << "Row with Account Number " << account_number << " deleted." << endl;

    return true;
}