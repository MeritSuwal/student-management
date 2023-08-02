#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
 
using namespace std;

class Student {
    char name[40];
    char roll_no[13];
    char faculty[15];
    char grade;
    char phone_no[11];
    float marks;

public:
    void getData() {
        cin.ignore();
        cout << "Enter full name: ";
        cin.getline (name, 40);
        
        cout << "Enter roll number: ";
        cin >> roll_no ;

        cout << "Enter Faculty: ";
        cin >> faculty;

        cout << "Enter Phone number:";
        cin >> phone_no;

        cout << "Enter marks secured: ";
        cin >> marks;

        if (marks >= 75)
            grade = 'A';
        else if (marks >= 65)
            grade = 'B';
        else if (marks >= 50)
            grade = 'C';
        else if (marks >= 40)
            grade = 'D';
        else 
            grade = 'F';
    }

    void display() {
        cout << left << setw(40) << name;
        cout << left << setw(15) << roll_no;
        cout << left << setw(15) << faculty;
        cout << left << setprecision(2) << setw(6) << marks;
        cout << left << setw(6) << grade;
        cout << left << setw(12) << phone_no << endl;
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
    //note: there must be Database folder already created inside the current folder
    sprintf(file_name, "./Database/%s.txt", argv[1]);
    
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

    ifstream ifile;
    ofstream ofile;
    ifile.open(file_name, ios::in | ios::binary);
    ofile.open(file_name, ios::out | ios::app | ios::binary);

    if (ifile.fail() || ofile.fail()) {
        cout << "\nError opening the give file." << endl;
    }

    //IF file already exists, check whether the entry with that specific username exists or not
    bool found = false;
    ifile.seekg(0, ios::end);
    int endposition = ifile.tellg();
    if (endposition != 0) {
        ifile.seekg(0);
        while(ifile.read((char*)&tempS, sizeof(tempS))) {
            if (strcmp(tempS.getRoll(), s.getRoll()) == 0) {
                cout << "\nThis Roll Number already exists in the DataBase!" << endl;
                found = true; //entry with the same roll. no already exists!
                ifile.close();
                ofile.close();
                return;
            }
        }
    }

    if (!found) {
        ofile.seekp(0, ios::end);
        ofile.write((char*)&s, sizeof(s));
    }

    ifile.close();
    ofile.close();
}

void modifyUser(char *file_name) {
    //TODO: modify student's complete data
    //checkign chai roll no. le garne
    Student s, tempS1, tempS2;
    fstream file;
    bool match = false;
    int pointerPosition;
    int count = 0;

    char r_no[12];
    cout << "\nEnter the roll number to be modified: ";
    cin >> r_no;

    file.open(file_name, ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);

    while (file.read((char*)&tempS1, sizeof(tempS1))){
        count++;
        if(strcmp(tempS1.getRoll(), r_no) == 0){
            
            s.getData();
            file.seekg(0);
            while(file.read((char*)&tempS2, sizeof(tempS2))) {
                if ((strcmp(s.getRoll(), tempS2.getRoll()) == 0) && (strcmp(s.getRoll(), r_no) != 0)) {
                    cout << "\nThis Roll Number already exists in the DataBase!" << endl;
                    cout << "Could not update the DataBase!" << endl;
                    file.close();
                    return;
                }
            }

            cout << "SIzeof s: " << sizeof(s) << " Count: " << count << endl;
            pointerPosition = sizeof(s) * (count - 1);
            //cout << "pointerposition: " << pointerPosition << endl;
            file.seekp(pointerPosition, ios::beg);
            file.write((char*)&s, sizeof(s));
            cout << "\nThe database record for the roll number \"" << r_no << "\" has been modified successfully. " << endl;
            match = true;
            break;
        }
    }

    if(match == false)
        cout << "\nNo Matches were found for this roll number. ";

    file.close();
} 

void deleteUser(char *file_name) {
    //fin to read the file_name.txt, fout to write the data of file_name.txt except that particular entry
    fstream fin, fout;

    Student s;

    char roll_no[13];
    //check whether the roll no. is in database or not
    bool flag = false;

    cout << "\nEnter the Roll.No. whose entry is to be deleted: " << endl;
    cin >> roll_no;

    fin.open(file_name, ios::in | ios::binary);
    fout.open("./Database/temp.txt", ios::out | ios::binary);

    if (fin.fail() || fout.fail()) {
        cout << "\nError opening the give file." << endl;
    }

    while(!fin.eof()) {
        fin.read((char*)&s, sizeof(s));
        if (strcmp(s.getRoll(), roll_no) == 0)
            //the entry exists and we dont fout.write for this s object
            flag = true;
        else
            fout.write((char*)&s, sizeof(s));
    }

    if (!flag)
        cout << "\nEntry not found!" << endl;
    else 
        cout << "\nRecord Deleted!" << endl;

    fout.close();
    fin.close();

    remove(file_name);
    rename("./Database/temp.txt", file_name);
}

void displayID(char *file_name) {
    Student s;
    bool match = false;
    //roll no. provided by the user
    char r_no[13];

    cout << "\nEnter student's roll no: ";
    cin >> r_no;

    fstream file;
    file.open(file_name, ios::in | ios::binary);

    if (file.fail()) {
        cout << "\nError opening the give file." << endl;
    }

    while (!file.eof()){
        file.read((char*)&s, sizeof(s));
        if (strcmp(s.getRoll(), r_no) == 0){
            cout << "\nRECORD FOUND!\n";

            //Header
            cout << left << setw(40) << "Name";
            cout << left << setw(15) << "Roll No.";
            cout << left << setw(15) << "Faculty";
            cout << left << setprecision(2) << setw(6) << "Marks";
            cout << left << setw(6) << "Grade";
            cout << left << setw(12) << "Phone No." << endl;

            s.display();
            match = true;
            break;
        }
    }

    if (!match)
        cout << "\nRecord for Roll No. \"" << r_no << "\" was not found." << endl;

    file.close();
}

void displayAll(char *file_name) {
    //TODO: display each and every entry for that subject, in proper formatted manner
    Student s;

    ifstream file;
    file.open(file_name, ios::binary);

    if (file.fail()) {
        cout << "\nError opening the give file." << endl;
        cout << "The file is probably not created. Please add some data first" << endl;
    }

    //moving the cursor pointer to the end to check whether there are file contents or not
    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        cout << "\nFile is emptpy. Try adding some data first!" << endl;
        file.close();
        return;
    }

    //Header
    cout << left << setw(40) << "Name";
    cout << left << setw(15) << "Roll No.";
    cout << left << setw(15) << "Faculty";
    cout << left << setprecision(2) << setw(6) << "Marks";
    cout << left << setw(6) << "Grade";
    cout << left << setw(12) << "Phone No." << endl;

    //moving back the cursor pointer to the beginning of the file
    file.seekg(0, ios::beg);
    while (!file.eof()){
    file.read((char*)&s, sizeof(s));
    if (!file.eof()) {  // Check if the end of file is reached
        s.display();
    }
    }

    file.close();
}