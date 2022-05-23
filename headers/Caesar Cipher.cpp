#include <iostream>
#include <string>
using namespace std;

long mod_for_all(int a, int b)
{
    return (a % b + b) % b;
}

string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void encrypt(string &word_to_encrypt)
{

    string message;
    message = word_to_encrypt;

    for (auto &c : message)
        c = toupper(c);

    int shift = 17;

    int position_in_abc, new_position;
    string final;
    char encrypted;

    for (int i = 0; i < message.length(); ++i)
    {
        char character = message[i];
        if (isspace(character) || (isdigit(character)))
        {
            final += character;
            continue;
        }
        else
        {
            position_in_abc = abc.find(character);
            new_position = mod_for_all((position_in_abc + shift), 26);
            encrypted = abc[new_position];
            final += encrypted;
        }
    }

    word_to_encrypt = final;
}

void decryption()
{
    cout << "Enter The Message You Want To Decypt: ";
    string message;
    getline(cin >> ws, message);
    for (auto &c : message)
        c = toupper(c);
    cout << "shift: ";
    int shift;
    cin >> shift;

    int position_in_abc, new_position;
    string final;
    char decrypted;

    for (int i = 0; i < message.length(); ++i)
    {
        char character = message[i];
        if (isspace(character) || (isdigit(character)))
        {
            final += character;
            continue;
        }
        else
        {
            position_in_abc = abc.find(character);
            new_position = mod_for_all((position_in_abc - shift), 26);
            decrypted = abc[new_position];
            final += decrypted;
        }
    }
    cout << "######################################" << endl;
    cout << "Decrypted Message: " << final << endl;
    cout << "#######################################" << endl;
}

// int main()
// {
//     int choice;
//     while (true)
//     {
//         cout << "1- Encrypt A Message Using (Caesar Cipher)\n2- Decrypt A Message Using (Caesar Cipher)\n3- Exit" << endl;
//         cout << "What Do You Want To Do?: ";
//         cin >> choice;
//         if (choice == 1)
//         {
//             // encrypt();
//         }
//         else if (choice == 2)
//         {
//             decryption();
//         }
//         else
//         {
//             exit(1);
//         }
//     }

// }
