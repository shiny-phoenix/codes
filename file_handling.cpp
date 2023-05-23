#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    int rollno;
    string name;
    string division;
    string address;
};

void addStudent(const Student& student) {
    ofstream file("students.txt", ios::app);
    if (file.is_open()) {
        file << student.rollno << " "
             << student.name << " "
             << student.division << " "
             << student.address << endl;
        file.close();
        cout << "Student added successfully." << endl;
    } else {
        cout << "Unable to open the file." << endl;
    }
}

void deleteStudent(int rollno) {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    bool deleted = false;
    if (inFile.is_open() && outFile.is_open()) {
        Student student;
        while (inFile >> student.rollno >> student.name >> student.division >> student.address) {
            if (student.rollno != rollno) {
                outFile << student.rollno << " "
                        << student.name << " "
                        << student.division << " "
                        << student.address << endl;
            } else {
                deleted = true;
            }
        }
        inFile.close();
        outFile.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (deleted) {
            cout << "Student deleted successfully." << endl;
        } else {
            cout << "Student not found." << endl;
        }
    } else {
        cout << "Unable to open the file." << endl;
    }
}

void insertStudent(int position, const Student& student) {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    if (inFile.is_open() && outFile.is_open()) {
        int count = 0;
        Student temp;
        while (inFile >> temp.rollno >> temp.name >> temp.division >> temp.address) {
            if (count == position) {
                outFile << student.rollno << " "
                        << student.name << " "
                        << student.division << " "
                        << student.address << endl;
            }
            outFile << temp.rollno << " "
                    << temp.name << " "
                    << temp.division << " "
                    << temp.address << endl;
            count++;
        }
        inFile.close();
        outFile.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        cout << "Student inserted successfully." << endl;
    } else {
        cout << "Unable to open the file." << endl;
    }
}

void searchStudent(int rollno) {
    ifstream file("students.txt");
    if (file.is_open()) {
        Student student;
        bool found = false;
        while (file >> student.rollno >> student.name >> student.division >> student.address) {
            if (student.rollno == rollno) {
                cout << "Roll No: " << student.rollno << endl;
                cout << "Name: " << student.name << endl;
                cout << "Division: " << student.division << endl;
                cout << "Address: " << student.address << endl;
                found = true;
                break;
            }
        }
        file.close();
        if (!found) {
            cout << "Student not found." << endl;
        }
    } else {
        cout << "Unable to open the file." << endl;
    }
}

int main() {
    int choice;
    Student student;
    int position, rollno;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Insert Student\n";
        cout << "4. Search Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Roll No: ";
                cin >> student.rollno;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, student.name);
                cout << "Enter Division: ";
                getline(cin, student.division);
                cout << "Enter Address: ";
                getline(cin, student.address);
                addStudent(student);
                break;
            case 2:
                cout << "Enter Roll No of the student to delete: ";
                cin >> rollno;
                deleteStudent(rollno);
                break;
            case 3:
                cout << "Enter Position: ";
                cin >> position;
                cin.ignore();
                cout << "Enter Roll No: ";
                cin >> student.rollno;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, student.name);
                cout << "Enter Division: ";
                getline(cin, student.division);
                cout << "Enter Address: ";
                getline(cin, student.address);
                insertStudent(position, student);
                break;
            case 4:
                cout << "Enter Roll No of the student to search: ";
                cin >> rollno;
                searchStudent(rollno);
                break;
            case 5:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
