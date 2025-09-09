#include <iostream>
#include <conio.h>
#include "interface.h"
#include "console_utils.h"


using namespace std;

int main()
{
    Startup_Screen();
    while (true)
    {
        int main_menu_choice = Main_Menu();
        switch(main_menu_choice)
        {
            case 1:
                create_account();
                break;
            case 2:
                user_login();
                break;
            case 3:
                admin_login();
                break;
            case 4:
                thank_you_header(11);
                setcolor(5);
                cout<<"\nEnter any key to close....\n";
                getch();
                exit(0);
        }
    }

    return 0;
}