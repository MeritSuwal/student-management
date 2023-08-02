#include <iostream>
#include <fstream>
#include <string.h>
#include <cctype>
 
using namespace std;

class Student {
    char name[40];
    char roll_no[13];
    char faculty[15];
    char grade;
    char phone_no[11];

public:
    void getData() {

    }

    void display() {

    }
};
 
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
    
}