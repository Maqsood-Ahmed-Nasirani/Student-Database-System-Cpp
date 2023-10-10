#pragma once
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

using std::cout; 
using std::cin; 
using std::vector; 
using std::string;


namespace MyDatabase {
    class Student {
    public:
        void menu();
        void getStudentInfo();
        void display();
        void clearScreen();

    private:
        vector<Student> saveStudentInfo;
        string name, contact, address, cnic, studentId;
        char grade;
    };
}

//taking the student information
void MyDatabase::Student::getStudentInfo() {
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your contact: ";
    cin >> contact;
    cin.ignore();
    cout << "Enter your address: ";
    getline(cin, address);
    cout << "Enter your cnic: ";
    cin >> cnic;
    cout << "Enter your student Id: ";
    cin >> studentId;
}


//displaying student information
void MyDatabase::Student::display() {
    for (const auto& s : saveStudentInfo) {
        cout << "\n############################################################\n";
        cout << "\nName:       " << s.name;
        cout << "\nContact:    " << s.contact;
        cout << "\nAddress:    " << s.address;
        cout << "\nStudent Id: " << s.studentId;
        cout << "\nCnic:       " << s.cnic << '\n';
    }
}


//menu
void MyDatabase::Student::menu() {
    while (true) {
        int choice;
        cout << "\n[1] for Input\n";
        cout << "[2] for display\n";
        cout << "[0] for exit\n";
        cout << ">>> ";
        cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            clearScreen();
            getStudentInfo();
            saveStudentInfo.push_back(*this); // Save the current student data
            clearScreen();
        } else if (choice == 2) {
            if (!saveStudentInfo.size())
                cout << "There is nothing to display.. Database is empty!\n";
            else {
                clearScreen();
                display();
            }
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void MyDatabase::Student::clearScreen(void) {
    #if _WIN32
        system("cls");
    #else   
        system("clear");
    #endif
}

#endif
