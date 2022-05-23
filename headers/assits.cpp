#include <iostream>
#include "min_functions.h"

//________________________
using namespace std;

//_______User_struct_________

//________________________
struct user
{
    string first_name;
    string last_name;
    string age;
    string phone_number;
    string email;
    string password;
    string user_name;
    string id;
};

//_______Display_menu_function_________

//_________________________
// display function takes choice from user and return it back
void display(string &choice, bool first_time)
{
    if (first_time)
    {
        cout << "!! welcome !!" << endl;
    }

    cout << "1- Regieter a new user\n2- Login\n3- Change password\n4- Exit" << endl;
    cout << "Your choice: ";
    cin >> ws >> choice;
}

//_______Saving_user_information_function_________

//___________________________
void save_user(string first_name, string last_name, string user_name, string id, string age, string phone_number, string email, string password)
{
    // save first_name in FirstNames.txt file
    save_user_info("./data/FirstNames.txt", first_name);

    // save last_names in LastNames.txt file
    save_user_info("./data/LastNames.txt", last_name);

    // saving age in Ages.txt file
    save_user_info("./data/Ages.txt", age);

    // saving phone_number in PhoneNumber.txt
    save_user_info("./data/PhoneNumber.txt", phone_number);

    // saving email in Emails.txt
    save_user_info("./data/Emails.txt", email);

    // saving password to Password.txt
    save_user_info("./data/Passwords.txt", password);

    // saving user_name to user_names.txt
    save_user_info("./data/User_names.txt", user_name);

    // saving id to id.txt
    save_user_info("./data/Id.txt", id);
}

//_______Checkers_________

//___________________________
void check_name(string what_to_check, string &name)
{
    while (!matching_name(name))
    {
        cout << "#############################" << endl;
        cout << "!! invalid name !!" << endl;
        cout << "#############################" << endl;
        if (what_to_check == "first_name")
        {
            cout << "First_name (Names can't contain digits or special characters) : ";
            cin >> ws >> ws >> name;
        }
        else if (what_to_check == "last_name")
        {
            cout << "Last_name (Names can't contain digits or special characters) : ";
            cin >> ws >> name;
        }
    }
}

//___________________________
void check_phone_number(string &phone_number)
{
    while (!matching_phone_number(phone_number))
    {
        cout << "#############################" << endl;
        cout << "!! invalid Phone_number !!" << endl;
        cout << "#############################" << endl;
        cout << "Phone_number (Comprisd of 11 digits, Usually starst with 010 or 011 or 012 or 015): ";
        cin >> ws >> phone_number;
    }
}

//____________________________
void check_age(string &age)
{
    while (!mathcing_age(age))
    {
        cout << "#############################" << endl;
        cout << "!! invalid age !!" << endl;
        cout << "#############################" << endl;
        cout << "Age (only 2 digits) : ";
        cin >> ws >> age;
    }
}

//____________________________
void check_password(string &password)
{
    while (!is_it_strong_password(password))
    {
        cout << "#############################" << endl;
        cout << "!! Not A strong Password !!" << endl;
        cout << "#############################" << endl;
        cout << "Password (At Minimum eight characters, at least one letter and one number): ";
        password = convert_password_into_astirisks();
    }
}

//____________________________
void check_email(string &email)
{
    while ((!mathcing_email(email)) || (in_emails(email)))
    {
        if (!mathcing_email(email))
        {
            cout << "#############################" << endl;
            cout << "!! invalid email !!" << endl
                 << "!! Email is Restircted to [lowerL, upperL, digits, _]@gmail.com !!" << endl;
            cout << "#############################" << endl;
            cout << "Email: ";
        }
        else if (in_emails(email))
        {
            cout << "#############################" << endl;
            cout << "!! invalid email !!" << endl;
            cout << "!! Already exits !!" << endl;
            cout << "#############################" << endl;
            cout << "Email: ";
        }
        cin >> ws >> email;
    }
}

//_______Checkers_from_user_________

// check password from login
void check_password_from_login(string &password, bool check_old_password)
{
    if (!check_old_password)
    {
        // user have 4 trails to enter password
        int trails = 4;

        // take password from use
        while ((!in_passwords(password)))
        {
            trails -= 1;
            if (trails > 0)
            {
                cout << "#############################" << endl;
                cout << "!! invalid password (" << trails << " trails left) !!" << endl;
                cout << "#############################" << endl;
            }
            else if (trails <= 0)
            {
                access_denied("password");
            }

            cout << "Password: ";
            password = convert_password_into_astirisks();
        }
    }

    if (check_old_password)
    {
        while ((!in_passwords(password)))
        {

            cout << "#############################" << endl;
            cout << "!! invalid password !!" << endl;
            cout << "#############################" << endl;
            cout << "Old password: ";
            password = convert_password_into_astirisks();
        }
    }
}

//____________________________
void check_id_from_login(string &id)
{
    // user have 3 trails to enter id
    int trails = 4;

    // take id from use
    while ((!in_id(id)))
    {
        trails -= 1;
        if (trails > 0)
        {
            cout << "#############################" << endl;
            cout << "!! invalid id (" << trails << " trails left) !!" << endl;
            cout << "#############################" << endl;
        }
        else if (trails <= 0)
        {
            access_denied("id");
        }

        cout << "Id: ";
        getline(cin >> ws, id);
    }
}

//_______Main_functions_________

//_____________________
void registeration()
{
    user user_;
    // take first_name
    cout << "First_name: ";
    cin >> ws >> user_.first_name;
    check_name("first_name", user_.first_name);

    // take last_name
    cout << "Last_name: ";
    cin >> ws >> user_.last_name;
    check_name("last_name", user_.last_name);

    // take age
    cout << "Age: ";
    cin >> ws >> user_.age;
    check_age(user_.age);

    // take phone_number
    cout << "Phone_number: ";
    cin >> ws >> user_.phone_number;
    check_phone_number(user_.phone_number);

    // take email
    cout << "Email: ";
    cin >> ws >> user_.email;
    check_email(user_.email);

    // create_user_name based on the email
    user_.user_name = user_name_maker(user_.email);

    // id_maker
    user_.id = id_maker(user_.phone_number);

    // take password
    cout << "Password: ";
    user_.password = convert_password_into_astirisks();
    check_password(user_.password);
    re_password(user_.password);
    encrypt_a_password(user_.password);

    // save the user information into the prepared files
    save_user(user_.first_name, user_.last_name, user_.user_name, user_.id, user_.age, user_.phone_number, user_.email, user_.password);
    cout << user_.first_name << " " << user_.last_name << " ADDED SUCCESSFULLY TO DATA BASE !!!!" << endl;
    cout << "#############################" << endl;
    cout << "!! WELCOME " << user_.first_name << " " << user_.last_name << " !!" << endl;
    cout << "#############################" << endl;
    cout << "Your user_name: " << user_.user_name << endl;
    cout << "Your id: " << user_.id << endl;
    cout << "#############################" << endl;
}

//_________________________
// login function (3 trails for password and id)
void login()
{
    // take id from the user
    cout << "Id: ";
    string id;
    cin >> ws >> id;

    // check if id in database
    check_id_from_login(id);

    // take password from user
    cout << "Password: ";
    string password;
    password = convert_password_into_astirisks();
    check_password_from_login(password, false);

    // welcome message
    cout << "#############################" << endl;
    cout << "!! Successful login, welcome " << id << " !!" << endl;
    cout << "#############################" << endl;
}

//________________________
// change password
void change_password()
{
    // first user have to login
    login();

    // enter the old password
    cout << "Old password: ";
    string old_password = convert_password_into_astirisks();

    // check if the password is the old one (in Passwords.txt)
    check_password_from_login(old_password, true);

    // take password
    cout << "Password: ";
    string new_password;
    new_password = convert_password_into_astirisks();
    check_password(new_password);
    re_password(new_password);
    encrypt_a_password(new_password);

    // update old Password with the new one
    update_old_password("./data/Passwords.txt", old_password, new_password);
}
