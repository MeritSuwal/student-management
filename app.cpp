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

public:
    void getData() {
        cout << "Enter your full name: ";
        cin.getline (name, 40);
        cin.ignore();
        cout << "\nEnter your roll number: ";
        cin >> roll_no ;
        cout << "\nEnter your Faculty: ";
        cin >> faculty;
        cout << "\n Enter your Grade: ";
        cin >> grade;
        cout << "\Enter Phone number:";
        cin >> phone_no;

    }

    void display() {
        cout << 
    }
};
 
int main(int argc, char* argv[])
{

}