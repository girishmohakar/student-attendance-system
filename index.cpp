#include <iostream>
#include <fstream>
#include <limits>
#include <string.h>
using namespace std;

class Person 
{
protected:
    char name[50];
    int rollNo;

public:
    Person()
    {
        strcpy(name, "Unknown");
        rollNo = 0;
    }

    void inputPerson() 
    {
        cout << "Enter Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(name, 50);

        while(true) {
            cout << "Enter Roll Number: ";
            cin >> rollNo;
            if(cin.fail() || rollNo <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid number.\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
    }

    void displayPerson()
    {
        cout << "Name: " << name << "\nRoll No: " << rollNo << endl;
    }

    int getRollNo() { return rollNo; }
    char* getName() { return name; }
};

class Student : public Person
{
private:
    int attendance;
    int monthlyAttendance[12];
    int subjectAttendance[3];
    int subjectMonthlyAttendance[3][12];
    int theoryAttendance[3][12];
    int practicalAttendance[3][12];

public:
    static int totalClasses;
    static int totalClassesMonth[12];
    static int totalSubjectClasses[3];
    static int totalSubjectMonthly[3][12];

    Student()
    {
        attendance = 0;
        for(int i = 0; i < 12; i++)
            monthlyAttendance[i] = 0;

        for(int s = 0; s < 3; s++)
        {
            subjectAttendance[s] = 0;
            for(int m = 0; m < 12; m++) {
                subjectMonthlyAttendance[s][m] = 0;
                theoryAttendance[s][m] = 0;
                practicalAttendance[s][m] = 0;
            }
        }
    }

    float getAttendancePercentage()
    {
        if(totalClasses == 0) return 0;
        return (attendance * 100.0) / totalClasses;
    }

    float getMonthlyPercentage(int month)
    {
        if(totalClassesMonth[month-1] == 0) return 0;
        return (monthlyAttendance[month-1] * 100.0) / totalClassesMonth[month-1];
    }

    void displayAttendance()
    {
        displayPerson();
        cout << "Total Classes Attended: " << attendance
             << "/" << totalClasses << endl;
        cout << "Attendance %: " << getAttendancePercentage() << "%" << endl;
    }

    void displayMonthlyReport(int month)
    {
        displayPerson();
        cout << "Classes Attended in month " << month << ": " << monthlyAttendance[month-1]
             << "/" << totalClassesMonth[month-1] << endl;
        cout << "Attendance %: " << getMonthlyPercentage(month) << "%" << endl;
    }

    void displaySubjectWiseReport(int month)
    {
        string subjects[3] = {"Biology", "Chemistry", "Physics"};
        displayPerson();
        for(int s = 0; s < 3; s++)
        {
            cout << subjects[s] << ": " << subjectMonthlyAttendance[s][month-1]
                 << "/" << totalSubjectMonthly[s][month-1] << "  =>  ";

            if(totalSubjectMonthly[s][month-1] == 0)
                cout << "0%\n";
            else
                cout << (subjectMonthlyAttendance[s][month-1]*100.0/totalSubjectMonthly[s][month-1]) << "%\n";
        }
    }

    void displayTheoryPracticalReport(int month)
    {
        string subjects[3] = {"Biology", "Chemistry", "Physics"};
        displayPerson();
        for(int s = 0; s < 3; s++)
        {
            cout << subjects[s] << " - Theory: " << theoryAttendance[s][month-1]
                 << ", Practical: " << practicalAttendance[s][month-1] << endl;
        }
    }

    void displaySemesterReport(int semester)
    {
        int start = (semester == 1) ? 0 : 6;
        int end = (semester == 1) ? 6 : 12;
        int total = 0, attended = 0;

        for(int i = start; i < end; i++)
        {
            total += totalClassesMonth[i];
            attended += monthlyAttendance[i];
        }

        displayPerson();
        cout << "Semester " << semester << " Attendance: " << attended