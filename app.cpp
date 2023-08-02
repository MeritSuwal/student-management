#include <iostream>
#include <fstream>
#include <string.h>
#include <cctype>
#include <iomanip>
 
using namespace std;

class Student {
    char name[40];
    char roll_no[13];
    char faculty[15];
    char grade;
    char phone_no[11];

public:
    void getData() {
        cin.ignore();
        cout << "Enter your full name: ";
        cin.getline (name, 40);
        
        cout << "Enter your roll number: ";
        cin >> roll_no ;

        cout << "Enter your Faculty: ";
        cin >> faculty;

        cout << "Enter your Grade: ";
        cin >> grade;

        cout << "Enter Phone number:";
        cin >> phone_no;

    }

    void display() {
        cout << setw(22) << setiosflags(ios::left) << name << setw(12) << setiosflags(ios::left)<< roll_no <<setiosflags(ios::left)<< setw(8) << faculty <<setiosflags(ios::left) << setw(5) <<setiosflags(ios::left)<< grade << setw(15) <<phone_no;
    }

    char* getRoll() {
        return roll_no;
    }
};

void addUser(char *file_name);
void modifyUser(char *file_name);
void deleteUser(char *file_name);
void displayID(char *file_name);
void displayAll(char *file_name);
 
int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Command Usage: ./app.exe <subject-name>" << endl;
        return 1; //invalid number of arguments!
    }

    //checking whether the input subject is valid or not
    char subjects[7][6] = {"OOP", "DL", "TOC", "ECT", "MATHS", "EDC", "EM"};
    bool found = false;
    for (int i = 0; i < 7; i++) {
        if (strcmp(argv[1], subjects[i]) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Enter a valid subject name!" << endl;
        cout << "OOP, DL, TOC, ECT, MATHS, EDC, EM are the valid subjects!" << endl;
        return 2; //invalid subject argument
    }

    //file name:
    char file_name[10];
    sprintf(file_name, "%s.txt", argv[1]);
    
    //what do?
    int n;

    while(1) {
        cout << "\nUser Modes: " << endl;
        cout << "1. Add a Student" << endl;
        cout << "2. Modify a Student's data" << endl;
        cout << "3. Delete a Student's data" << endl;
        cout << "4. Search a Student's data" << endl;
        cout << "5. Display every student's data" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter choice: ";
        cin >> n;

        //operate on these given mode numbers
        switch(n) {
            case 1:
                addUser(file_name);
                break;
            case 2:
                modifyUser(file_name);
                break;
            case 3:
                deleteUser(file_name);
                break;
            case 4:
                displayID(file_name);
                break;
            case 5:
                displayAll(file_name);
                break;
            case 6:
                return 0;
            default:
                cout << "Enter a valid choice!!" << endl;
        }
    }
}

void addUser(char *file_name) {
    Student s, tempS;
    
    cout << "\nEnter the Student's info: " << endl;
    s.getData();

    fstream file;
    file.open(file_name, ios::in | ios::out | ios::app);

    //IF file already exists, check whether the entry with that specific username exists or not
    bool found = false;
    file.seekg(0, ios::end);
    int endposition = file.tellg();
    if (endposition != 0) {
        file.seekg(0);
        while(file.read((char*)&tempS, sizeof(tempS))) {
            if (strcmp(tempS.getRoll(), s.getRoll()) == 0) {
                cout << "This Roll Number already exists in the DataBase!" << endl;
                found = true; //entry with the same roll. no already exists!
                file.close();
                return;
            }
        }
    }

    if (!found)
        file.write((char*)&s, sizeof(s));

    file.close();
}

void modifyUser(char *file_name) {
    //TODO: modify student's complete data
    //checkign chai roll no. le garne
}

void deleteUser(char *file_name) {
    //TODO: delete a studnet's data, given: students' roll no
}

void displayID(char *file_name) {
    Student s;
    bool match = false;
    char r_no[12];

    cout << "Enter student's roll no: ";
    cin >> r_no;

    fstream file;
    file.open(file_name, ios::in);

    while (!file.eof()){
        file.read((char*)&s, sizeof(s));
        if (strcmp(s.getRoll(), r_no) == 0){
            cout << "RECORD FOUND!\n";
            s.display();
            match = true;
            break;
        }
    }

    if (!match)
        cout << "\n Record for " << r_no << "was not found." << endl;

    file.close();
}

void displayAll(char *file_name) {
    //TODO: display each and every entry for that subject, in proper formatted manner
}