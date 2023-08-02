#include <fstream>
#include <iostream>
#include <string.h>
 
using namespace std;

class Student {
    string name;
    string roll_no;
    float gpa;
    long int phone_no;
    int* course_id;
    int size;

public:
    Student(string name=" ", string roll_no = 0, float gpa = 0.0 , long int phone_no = 0 , int array[] = 0, int n =0){

        this-> name = name;
        this-> roll_no = roll_no;
        this-> gpa = gpa;
        this-> phone_no;
        size = n;
        course_id = new int[size];
        for (int i=0; i<size; i++){
            course_id[i] = array[i];
        }
    }

    void disp(){
        cout << name << roll_no;
        for (int i = 0; i<size; i++){
        cout << course_id[i];
    }

    }

};
 
int main()
{
    int course_num=2;
    int *arr = new int[course_num];
    string name;
    cout << "Enter:";
    cin >>name;

    for (int i = 0; i<course_num; i++){
        cin >> arr[i];
    }

    Student s1 (name, "67", 99, 90990, arr, course_num);
    s1.disp();

    delete[] arr;


}