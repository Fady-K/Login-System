#include <iostream>
#include "headers/utility.h"

//_________________
using namespace std;

//_________________
int main()
{
    bool program_running = true;
    string choice;

    display(choice, true);
    while (program_running)
    {
        if (choice == "1")
        {
            registeration();
        }
        else if (choice == "2")
        {
            login();
        }
        else if (choice == "3")
        {
            change_password();
        }
        else if (choice == "4")
        {
            program_running = false;
            break;
        }
        else
        {
            cout << "#############################" << endl;
            cout << "!! invalid !!" << endl;
            cout << "#############################" << endl;
        }
        display(choice, false);
    }
    return 0;
}
