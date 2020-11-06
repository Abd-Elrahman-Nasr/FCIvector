/**********************************************************
 * Course: CS213 - Programming II  - 2019                 *
 * Author: Abdelrahman Nasr                               *
 * Github: https://github.com/Abd-Elrahman-Nasr           *
 **********************************************************/

#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include "FCIvector.h"
#include "FCIvector.cpp"

using namespace std;

/// ===== Global variables =====
int choice; // to take the user's choice
bool isCourse = false; // to determine the display of contents

/// ===== Functions prototypes =====
void vectorType();

template<typename T>
void vectorOperation(FCIvector<T> myList);

int validateInput();

/// ===== Classes definitions =====
class Course
{
    private:
        string courseName;
        string courseCode;
        char courseGrade;
        float coursePoint;
        int courseYear;
        int courseSemester;

    public:
        Course(){}

        void printCourseInfo(){
            cout << "Course Name:     " << courseName << endl;
            cout << "Course Code:     " << courseCode << endl;
            cout << "Course Grade:    " << courseGrade << endl;
            cout << "Course Point:    " << coursePoint << endl;
            cout << "Course Year:     " << courseYear << endl;
            cout << "Course Semester: " << courseSemester << endl;
        }

        friend istream& operator >> (istream& in, Course& c){
            cout << "Course Name: ";
            in.ignore();
            getline(in, c.courseName);

            cout << "Course Code: ";
            getline(in, c.courseCode);

            cout << "Course Grade: ";
            in >> c.courseGrade;

            cout << "Course Point: ";
            in >> c.coursePoint;

            cout << "Course Year: " << endl;
            c.courseYear = validateInput();

            cout << "Course Semester: " << endl;
            c.courseSemester = validateInput();

            return in;
        }
};

class Student
{
    private:
        string sName;
        int sID;
        string sDepartment;
        FCIvector<Course> courses;

    public:
        Student(){}

        void printInfo(){
            cout << "Student name:          " << sName << endl;
            cout << "Student ID:            " << sID << endl;
            cout << "Student department:    " << sDepartment << endl;
        }

        friend istream& operator >> (istream& in, Student& s){
            int numOfCourses;
            Course *crs = new Course;

            cout << "Student name: ";
            in.ignore();
            getline(in, s.sName);

            cout << "Student ID: " << endl;
            s.sID = validateInput();

            cout << "Student department: ";
            in.ignore();
            getline(in, s.sDepartment);

            cout << "Number of courses: ";
            numOfCourses = validateInput();

            for(int n=0; n < numOfCourses; n++){
                cout << "Enter Course #" << n+1 << " info:" << endl;

                in >> *crs;
                s.courses.push_back(*crs);
            }

            delete crs;

            return in;
        }

        friend ostream& operator << (ostream &out, Student &s){

            out << endl;
            s.printInfo();

            /// display courses
            for(int i=0; i < s.courses.size(); i++){
                out << "---------------------" << endl;
                s.courses[i].printCourseInfo();
            }

            out << endl;

            return out;
        }

};

/// ===== lists definitions =====
FCIvector<int> intList;
FCIvector<char> charList;
FCIvector<string> stringList;
FCIvector<float> floatList;
FCIvector<Student> studList;

int main()
{
    vectorType();
    return 0;
}


/* This function is called whenever we need int input from user
 * It prevents the program from crashing and returns the input
 * if and only if the data entered is really int
 */
int validateInput(){
    int choose;
    cout << "> ";
    cin >> choose;

    // input validation
    while(true){
        if( cin.fail() ){
            cin.clear(); // clear the stream
            cin.ignore(INT_MAX,'\n'); // ignore any thing afterwards

            cout << "\nNot valid choice .. please, try again!\n" << endl;

            cout << "> ";
            cin >> choose;
        }

        if( !cin.fail() ) break;
    }

    return choose;
}


/* The first screen in the program which the user see
 * when user chooses a type, it detects the type of the list
 * and pass the predefined list to vectorOpertation template function
 */
void vectorType(){

    /// view options
    cout << "Insert type of vector you would like to create:" << endl;
    cout << "1. list of integer" << endl;
    cout << "2. list of character" << endl;
    cout << "3. list of string" << endl;
    cout << "4. list of float" << endl;
    cout << "5. list of students" << endl;
    cout << "6. Exit" << endl;

    choice = validateInput();

    if (choice > 0 && choice < 6){
        /// will create the object from FCIvector class of this type
        /// each number will create a type and at the end this objectwill be passed
        /// for the next function view options

        cout << endl;

        /// declare list based on type needed
        if     (choice == 1) vectorOperation<int>(intList);
        else if(choice == 2) vectorOperation<char>(charList);
        else if(choice == 3) vectorOperation<string>(stringList);
        else if(choice == 4) vectorOperation<float>(floatList);
        else if(choice == 5) {
            isCourse = true;
            vectorOperation<Student>(studList);
        }

    }
    else if (choice == 6) {
        cout << "\nExiting...\n" << endl;
        exit(0);

    } else {
        cout << "\nNot valid choice .. please, try again!\n" << endl;
        vectorType();
    }
}

/* This function displays the options of the operations the user can do
 * each option calls a related FCIvector function that can do the operation needed
 * myList: FCIvector of type T that represent each FCIvectors of each type
 * that are defined in "lists definitions" section above
 */
template<typename T>
void vectorOperation(FCIvector<T> myList){
    T data;
    int pos, status;
    string strChoice;

    /// view options
    cout << "What kind of operation would you like to perform?" << endl;
    cout << "1.  Add element" << endl;
    cout << "2.  Remove last element" << endl;
    cout << "3.  Insert element at certain position" << endl;
    cout << "4.  Erase element from a certain position" << endl;
    cout << "5.  Clear" << endl;
    cout << "6.  Display first element" << endl;
    cout << "7.  Display last element" << endl;
    cout << "8.  Display element at certain position" << endl;
    cout << "9.  Display vector size" << endl;
    cout << "10. Display vector capacity" << endl;
    cout << "11. Is empty?" << endl;

    choice = validateInput();

    if (choice > 0 && choice < 12){
        int option;

        /***** Add element *****/
        if(choice == 1){
            cout << "\nHow many elements you would like to add?" << endl;
            option = validateInput();

            /// take elements from user
            cout << "\nEnter elements:" << endl;
            cout << "-----------------" << endl;

            for(int i=0; i < option; i++){

                if(!isCourse){
                    cout << "> ";
                } else {
                    cout << endl;
                }

                cin >> data;
                myList.push_back(data);
            }

        }

        /***** Remove last element *****/
        else if(choice == 2){
            if(myList.size() > 0) myList.pop_back();
            else {
                status = 1;
            }
        }

        /***** Insert element at certain position *****/
        else if(choice == 3){
            cout << "position: " << endl;
            pos = validateInput();

            if(!isCourse) cout << "value: ";

            /// insert in closed boundaries and non-negative index
            if(pos <= myList.size()&& pos >= 0){
                cin >> data;
                myList.insert(myList.begin() + pos, data);
            } else {
                status = 1;
            }

        }

        /***** Erase element from a certain position *****/
        else if(choice == 4){
            cout << "position: " << endl;
            pos = validateInput();

            /// erase only available elements and non-negative index
            if(pos < myList.size()&& pos >= 0){
                myList.erase(myList.begin() + pos);
            } else {
                status = 1;
            }

        }

        /***** Clear *****/
        else if(choice == 5){
            myList.clear();
        }

        /***** Display first element *****/
        else if(choice == 6){
            if(myList.size() != 0){
                cout << "\n" << myList.front() << endl;
            } else {
                status = 0;
            }
        }

        /***** Display last element *****/
        else if(choice == 7){
            if(myList.size() != 0){
                cout << "\n" << myList.back() << endl;
            } else {
                status = 0;
            }
        }

        /***** Display element at certain position *****/
        else if(choice == 8){
            cout << "position: " << endl;
            pos = validateInput();

            if(myList.size() != 0 && pos <= myList.size() - 1 && pos >= 0){
                cout << "\n" << myList[pos] << endl;
            } else {
                status = 0;
            }
        }

        /***** Display vector size *****/
        else if(choice == 9){
            cout << "\n" << myList.size() << "\n" << endl;
        }

        /***** Display vector capacity *****/
        else if(choice == 10){
            cout << "\n" << myList.capacity() << "\n" << endl;
        }

        /***** Is empty? *****/
        else if(choice == 11){
            if(myList.empty()){
                cout << "\nThe list is empty\n" << endl;
            } else {
                cout << "\nThe list is not empty\n" << endl;
            }
        }

        /// Error alerts
        if(status == 0){
            cout << endl;
            cout << "*************************************" << endl;
            cout << "* There is no elements to be viewed *" << endl;
            cout << "*************************************" << endl;

            status = 2; /// reset

        }
        else if (status == 1){
            cout << endl;
            cout << "****************************" << endl;
            cout << "* Position is out of range *" << endl;
            cout << "****************************" << endl;
            cout << endl;

            status = 2; /// reset
        }


        /// redirections
        cout << "\nWould you like to perform other operations? (Y/N)" << endl;
        cin.ignore();

        while(true){
            cout << "> ";
            getline(cin, strChoice);
            cout << endl;

            if(strChoice == "Y"){
                vectorOperation<T>(myList);
            }
            else if (strChoice == "N"){
                if(isCourse) isCourse = false;
                vectorType();
            }
        }

    } else {
        cout << "\nNot valid choice .. please, try again!\n" << endl;
        vectorOperation<T>(myList);
    }
}
