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
        
        cout << "Enter your roll number: ";
        cin >> roll_no ;
        cout << "Enter your Faculty: ";
        cin >> faculty;
        cout << " Enter your Grade: ";
        cin >> grade;
        cout << "Enter Phone number:";
        cin >> phone_no;

    }

    void display() {
        cout << setw(22) << setiosflags(ios::left) << name << setw(12) << setiosflags(ios::left)<< roll_no <<setiosflags(ios::left)<< setw(8) << faculty <<setiosflags(ios::left) << setw(5) <<setiosflags(ios::left)<< grade << setw(15) <<phone_no;
    }
};
 
int main(int argc, char* argv[])
{
Student s1;
s1.getData();
s1.display();
}