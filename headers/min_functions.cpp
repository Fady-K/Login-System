#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <conio.h>
#include "Caesar Cipher.h"

//_________________
using namespace std;

//__________________
bool matching_name(string name_to_check)
{
    regex pattern("^[A-Za-z_]+$");
    return regex_match(name_to_check, pattern);
}

//___________________
bool matching_phone_number(string phone_number_to_check)
{
    regex pattern("^(010|011|012|015)\\d{8}$");
    return regex_match(phone_number_to_check, pattern);
}

//___________________
bool mathcing_email(string email_to_check)
{
    // meta characters in c++ need to be escaped twice
    regex pattern("[A-Za-z0-9_]+@(gmail|hotmail)\\.com");
    return regex_match(email_to_check, pattern);
}

bool mathcing_age(string age)
{
    regex pattern("^\\d{2}$");
    return regex_match(age, pattern);
}

//___________________
bool in_emails(string email_to_check)
{
    bool out = false;
    // create varible of fstream datatype (object), where the file wil be stored
    fstream file;

    // open the emails.txt in reading mood
    file.open("./data/Emails.txt", ios::in);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (email_to_check == line)
            {
                out = true;
                break;
            }
        }
    }
    else
    {
        cout << "#############################" << endl;
        cout << "!! emails can't be open !!" << endl;
        cout << "#############################" << endl;
    }

    file.close();
    return out;
}

//_______________________
bool in_id(string id)
{
    bool out = false;
    fstream file;
    file.open("./data/Id.txt", ios::in);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line == id)
            {
                out = true;
            }
        }
    }
    else
    {
        cout << "!! Id.txt can't be open !!" << endl;
    }

    file.close();
    return out;
}

//____________________________
// encryption function to store password encrypted
void encrypt_a_password(string &password)
{
    // convert all the password letter into uppercase to be suitable for caesar cipher encryption
    for (auto &c : password)
        c = toupper(c);

    // encrypt password with caeser cipher encryption
    encrypt(password);
}

//________________________
bool in_passwords(string password)
{
    // encrypt the given password to recognize if in passwords.txt
    encrypt_a_password(password);

    bool out = false;
    fstream file;
    file.open("./data/Passwords.txt", ios::in);

    // to store each line brought from password.txt
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line == password)
            {
                out = true;
            }
        }
    }
    else
    {
        cout << "!! passowrd.txt can't be open !!" << endl;
    }

    file.close();
    return out;
}

//________________________
// convert input password into * while entering the password
string convert_password_into_astirisks()
{
    // declare ch inwhich pressed key will be saved
    char ch;

    // declare password and initialize with "" to concatinate to it ch from getch
    string password;

    // while pressed key not equal enter
    while ((ch = getch()) != '\r')
    {
        // check if returned key from getch is a backspace and stream isn't empty
        if ((ch == 8) && (password.size() > 0))
        {
            // use pop_back to remove the last character added to the string
            password.pop_back();

            // use \d \d to remove the last * from stream
            cout << "\b \b";
        }
        else
        {
            // if not a back space mask the letter with *
            cout << '*';

            // append the pressed key to password
            password += ch;
        }
    }
    cout << endl;
    return password;
}

//_________________
// is_it_strong_password
bool is_it_strong_password(string password)
{

    regex pattern("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$");
    return regex_match(password, pattern);
}

//__________________
void re_password(string &password_to_match)
{
    cout << "Re-enter the password: ";
    string re_entered_password;
    re_entered_password = convert_password_into_astirisks();

    while (password_to_match != re_entered_password)
    {
        cout << "#############################" << endl;
        cout << "!! Not A match !!" << endl;
        cout << "#############################" << endl;
        cout << "Re-enter the password: ";
        re_entered_password = convert_password_into_astirisks();
    }
    cout << "#############################" << endl;
    cout << "!! MATCHING !!" << endl;
    cout << "#############################" << endl;
}

//______________________
// save inforamtion into a particluar file

void save_user_info(string file_name, string text)
{
    fstream file;
    file.open(file_name, ios::app);

    if (file.is_open())
    {
        file << text << endl;
    }
    else
    {
        cout << "#############################" << endl;
        cout << file_name << " can't be open !!" << endl;
        cout << "#############################" << endl;
    }
    file.close();
    cout << file_name << " Updated Successfully !!" << endl;
}

//_______________________
// create id function
// id_maker >> id is the current year + the last 3 digits in the user phone number
string id_maker(const string phone_number)
{
    const string current_year = "2022";
    string id = current_year + phone_number.substr(8, 10);
    return id;
}

//_______________________
// user_name is the part of email existing before the @ symbol
string user_name_maker(string email)
{
    char character_index = email.find('@');
    string user_name = email.substr(0, character_index);
    return user_name;
}

//________________________
// access denied function
void access_denied(string what_to_deny)
{
    while (true)
    {
        cout << "#############################" << endl;
        cout << "!! Access denied !!" << endl;
        cout << "#############################" << endl;
        if (what_to_deny == "id")
        {
            cout << "Id: ";
        }
        else if (what_to_deny == "password")
        {
            cout << "password: ";
        }

        string gibrish;
        getline(cin >> ws, gibrish);
    }
}

//_____________________
void update_old_password(string file_name, string old_info, string new_info)
{
    // encrypt old password
    encrypt(old_info);

    // create a varible of fstream to store the file information
    fstream file;

    // to store all lines from file except the old info
    fstream temp;

    // open the desired file in varible (file)
    file.open(file_name);
    temp.open("./data/temp.txt", ios::app);

    string line;

    // count == 1 to ensure that one line will change only not all line (incase two user's has the same password)
    int count_of_changed = 1;
    // check if the file got open or not
    if (file.is_open())
    {

        // iterate over the line (words)
        while (getline(file, line))
        {
            if ((line == old_info) && (count_of_changed > 0))
            {
                temp << new_info << endl;
                cout << "#############################" << endl;
                cout << "!! " << file_name << " UPDATED SUCCESSFULLY !!" << endl;
                cout << "#############################" << endl;
                count_of_changed = 0;
            }
            else
            {
                temp << line << endl;
            }
        }
    }

    else
    {
        cout << "#############################" << endl;
        cout << "!!" << file_name << " can't be open !!" << endl;
        cout << "can't update " << file_name << "!" << endl;
        cout << "#############################" << endl;
    }
    temp.close();
    file.close();
    remove("./data/Passwords.txt");
    rename("./data/temp.txt", "./data/Passwords.txt");
}
