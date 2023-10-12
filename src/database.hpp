#pragma once
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>  
#include <cstdlib>
#include <cctype>   
#include <sstream>  

using namespace std;

namespace MyDatabase {

    void clearScreen();
    class Menu;
    class Registration {
    private:
        string name;
        string age;
        string contact;
        string cnic;
        string student_id;
        string student_password;
        string gender;
        string province;


    public:
        bool check_existing_acc(string &);
        void get_registration_details(void);
        void set_registration_password(void);
        bool validate_password(string &);
        void get_new_user_info(void);
        void display_user_details(void);
        void save_user_details(void);
        void write_login_info(string &, string &);
        bool is_numeric(const string &);
        void get_info_from_cnic(const string &);
    };

    class Menu : public Registration {
    public:
        void menu();
    };
}

bool MyDatabase::Registration::is_numeric(const string &str)
{
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

void MyDatabase::Registration::write_login_info(string &cnic, string &password)
{
    ofstream adminFile("Admin.txt", ios::app);

    if (!adminFile)
    {
        cout << "Error! Opening Admin.txt for appending.\n";
        return;
    }

    adminFile << cnic << " " << password << "\n";
    adminFile.close();
}

// Check if an account with the given CNIC exists
bool MyDatabase::Registration::check_existing_acc(string &check_cnic)
{
    string cnic_in_admin;
    ifstream adminFile("Admin.txt");

    if (!adminFile)
    {
        cout << "Error! Opening Admin.txt\n";
        return false;
    }

    bool cnic_found = false;

    while (getline(adminFile, cnic_in_admin))
    {
        istringstream iss(cnic_in_admin);
        iss >> cnic_in_admin;

        if (cnic_in_admin != check_cnic)
        {
            continue;
        }
        else
        {
            cnic_found = true;
            break;
        }
    }

    adminFile.close();

    if (cnic_found)
    {
        return true;
    }
}

// Set a strong password for user registration.
void MyDatabase::Registration::set_registration_password(void)
{
    cout << "\n1. Password must be 8 characters long" << endl
         << "2. Password must have one uppercase character" << endl
         << "3. Password must have one lowercase character" << endl
         << "4. Password must have one special character\n"
         << endl;
    cout << "Set New Password:  ";
    cin >> student_password;
    bool checkPass = validate_password(student_password);
    if (!checkPass)
    {
        set_registration_password();
    }

    string confirm_password;
    cout << "Re-enter password: ";
    cin >> confirm_password;

    while (student_password != confirm_password)
    {
        cout << "Try again:         ";
        cin >> confirm_password;
    }
    cout << "Your password has been set!" << endl;
}

// Validate the strength of a password.
bool MyDatabase::Registration::validate_password(string &pass)
{
    bool has_upper = false, has_lower = false, has_digit = false, has_special = false;

    if (pass.size() < 8)
    {
        return false;
    }

    for (const auto &ch : pass)
    {
        if (isupper(ch))
        {
            has_upper = true;
        }
        else if (islower(ch))
        {
            has_lower = true;
        }
        else if (isdigit(ch))
        {
            has_digit = true;
        }
        else if (!isalnum(ch))
        {
            has_special = true;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

// Get user registration details (name, age, contact).
void MyDatabase::Registration::get_registration_details(void)
{
    cout << "Enter your name:       ";
    cin >> name;
    cout << "Enter your age:        ";
    cin >> age;
    cout << "Enter your contact no: ";
    cin >> contact;
    cout << "Enter your student Id: ";
    cin >> student_id;
}

//collect new user information
void MyDatabase::Registration::get_new_user_info(void)
{
    get_registration_details();
    cout << "Enter your cnic:       ";
    cin >> cnic;
    while (cnic.size() != 13 || !is_numeric(cnic))
    {
        cout << "Not a valid CNIC. Please type your CNIC again: ";
        cin >> cnic;
    }

    bool check_existing_cnic = check_existing_acc(cnic);
    if (!check_existing_cnic)
    {
        get_info_from_cnic(cnic);
        set_registration_password();
        save_user_details();
    }
    else
    {
        cout << "Your account already exists!" << endl;
    }
}

//display user information
void MyDatabase::Registration::display_user_details(void)
{
    string read_cnic, read_pass, readFile, first_cnic, second_password;
    bool cnic_found = false;
    cout << "\n\nEnter your CNIC:   ";
    cin >> read_cnic;
    cout << "Enter your password:   ";
    cin >> read_pass;
    ifstream readAdminFile("Admin.txt");

    if (!readAdminFile)
    {
        cout << "Error opening Admin.txt!" << endl;
        return;
    }

    while (getline(readAdminFile, readFile))
    {
        istringstream iss(readFile);
        iss >> first_cnic;
        iss >> second_password;

        if (first_cnic != read_cnic || second_password != read_pass)
        {
            continue;
        }
        else
        {
            cnic_found = true;
            break;
        }
    }

    readAdminFile.close();

    if (!cnic_found)
    {
        cout << "Your account is not present in our Database\n";
        return;
    }

    ifstream userFile(first_cnic);

    if (!userFile)
    {
        cout << "File does not exist!" << endl;
        return;
    }

    clearScreen();
    //display user info if it exist
    cout << "\n--------------------------------------------------------------------------\n";
    cout << "\t\t\tDISPLAYING USER INFORMATION\n";
    cout << "--------------------------------------------------------------------------\n";    
    while (getline(userFile, readFile))
    {
        cout << readFile << endl;
    }

    userFile.close();
}

//function
void MyDatabase::Registration::get_info_from_cnic(const string &cnic) {
    
    if (cnic[0] == 1) 
        this->province = "KPK";
    else if (cnic[0] == 2) 
        this->province = "FATA";
    else if (cnic[0] == 3) 
        this->province = "Punjab";
    else if (cnic[0] == 4) 
        this->province = "Sindh";
    else if(cnic[0] == 5)
        this->province = "Balochistan";

    //check if last cnic digit is odd then gender is male
    if(cnic[12] & 1)
        gender = "Male";
    else    
        gender = "Female"; //if even then gender is female
}


//save user information in admin.txt file
void MyDatabase::Registration::save_user_details(void)
{
    ofstream user(cnic);
    user << "Name:      " << name << endl;
    user << "Std Id:    " << student_id << '\n';
    user << "Age:       " << age << endl;
    user << "Gender:    " << gender << endl;
    user << "Province:  " << province << endl;
    user << "Contact:   " << contact << endl;
    user << "CNIC:      " << cnic << endl;
    user << "Password:  " << student_password << endl;
    write_login_info(cnic, student_password);
    user.close();
}

//Menu 
void MyDatabase::Menu::menu()
{
    int choice;
    while (true)
    {
        cout << "\n--------------------------------------------------------------------------\n";
        cout << "\t\t\t  DATABASE MENU \n";
        cout << "--------------------------------------------------------------------------\n";
        cout << "\n[1] for Input\n";
        cout << "[2] for display\n";
        cout << "[0] for exit\n";
        cout << ">>> ";
        cin >> choice;

        if (choice == 0)
        {
            clearScreen();
            cout << "\n\t[ Have a Good Day! <3 ]\n";
            break;
        }
        else if (choice == 1)
        {
            clearScreen();
            get_new_user_info();
            clearScreen();
        }
        else if (choice == 2)
        {
            clearScreen();
            display_user_details();
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

//function for clearing screen
void MyDatabase::clearScreen()
{
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}


#endif
