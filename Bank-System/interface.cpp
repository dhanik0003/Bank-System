#include <iostream>
#include <string>
#include <conio.h>
#include "interface.h"
#include "console_utils.h"
#include "helper.h"
#include "account_manager.h"
#include "account.h"

void Startup_Screen()
{
    bank_system_header();
    cout<<endl;
    typing_effect("Welcome To Bank System",100);
    loading_animation("Loading Bank System, Please Wait",500);
}

int Main_Menu()
{
    int choice;
    main_menu_header();
    setcolor(10);
    cout<<"\n1. Create an Account\n2. User Login\n3. Admin Login\n4. Exit\n\nEnter your choice[1-4]: ";
    choice = getValidatedChoice(1,4);
    return choice;
}



void create_account()
{
    Account acc;

    create_account_header();

    cout<<endl;

    setcolor(10);

    acc.accountNumber = generateAccountNumber();

    acc.firstName = getfname();

    acc.lastName = getlname();

    acc.dob = getDOB();

    acc.gender = getGender();

    acc.address = getAddress();

    acc.phone = getPhone();

    acc.pin = getPin();

    acc.deposit = getdeposit();

    if(createAccount_db(acc))
    {
        system("cls");
        create_account_header();
        cout<<endl;
        setcolor(10);
        cout<<"Account Created Successfully!\n";
        cout<<"\nAccount Number: "<<acc.accountNumber<<endl;
        cout<<"\nPlease save your Account Number and Security PIN for future logins."<<endl;
    }
    else
    {
        cout<<"There was trouble in creating your account";
    }

    cout << "\nPress any key to return to the main menu...";
    _getch();

}

void user_login()
{
    user_login_header();
    cout<<endl;

    setcolor(10);

    string acc_number, password;

    if(user_initial_login(acc_number, password))
    {
        if(check_useraccount_db(acc_number, password))
        {
            int choice;
            do {
                system("cls");
                user_login_header();
                cout<<endl;
                setcolor(10);
                cout<<"User Logged In Successfully!"<<endl;
                cout<<"\n1. View Balance\n2. Deposit\n3. Withdraw\n4. Change PIN\n5. Change name\n6. Logout\n"
                    <<"\nEnter your choice[1-6]: ";
                choice = getValidatedChoice(1,6);
                system("cls");
                user_login_header();
                cout<<endl;
                setcolor(10);
                cout<<retrieve_user_db(acc_number, choice);

                if(choice != 6) {
                    cout << "\nPress any key to continue...";
                    _getch();
                }
            } while(choice != 6); // Repeat until Logout is chosen
        }
        else
        {
            cout<<"Login Failed!";
            cout << "\nPress any key to return to the main menu...";
            _getch();
        }
    }
    else
    {
        cout<<"Login Failed!";
        cout << "\nPress any key to return to the main menu...";
        _getch();
    }
}

void admin_login()
{
    admin_login_header();
    cout<<endl;
    setcolor(10);
    string admin_username, admin_password;
    if(admin_initial_login(admin_username, admin_password))
    {
        if(check_adminaccount_db(admin_username, admin_password))
        {
            int choice;
            do {
                system("cls");
                admin_login_header();
                cout<<endl;
                setcolor(10);
                cout<<"Admin Logged In Successfully!"<<endl;
                cout<<"\n1. View All Accounts\n2. Delete Account\n3. Change Account Details\n4. Clear Database\n5. Logout\n"
                    <<"\nEnter your choice[1-5]: ";
                choice = getValidatedChoice(1,5);
                system("cls");
                admin_login_header();
                cout<<endl;
                setcolor(10);
                cout<<retrieve_admin_db(choice);

                if(choice != 5) {
                    cout << "\nPress any key to continue...";
                    _getch();
                }
            } while(choice != 5); // Repeat until Logout is chosen
        }
        else
        {
            cout<<"Login Failed!";
            cout << "\nPress any key to return to the main menu...";
            _getch();
        }
    }
    else
    {
        cout<<"Login Failed!";
        cout << "\nPress any key to return to the main menu...";
        _getch();
    }
}