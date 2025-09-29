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
        cout << "Semester " << semester << " Attendance: " << attended << "/" << total;
        if(total > 0)
            cout << " => " << (attended * 100.0 / total) << "%\n";
        else
            cout << " => 0%\n";
    }

    void saveToFile()
    {
        ofstream fout("attendance.dat", ios::binary | ios::app);
        fout.write((char*)this, sizeof(*this));
        fout.close();
    }

    static bool isRollExist(int roll)
    {
        ifstream fin("attendance.dat", ios::binary);
        Student temp;
        while(fin.read((char*)&temp, sizeof(temp)))
        {
            if(temp.getRollNo() == roll)
            {
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }

    static void readFromFile()
    {
        ifstream fin("attendance.dat", ios::binary);
        Student temp;
        cout << "\n===== STUDENT ATTENDANCE =====\n";
        bool empty = true;
        while(fin.read((char*)&temp, sizeof(temp)))
        {
            temp.displayAttendance();
            cout << "---------------------------\n";
            empty = false;
        }
        if(empty) cout << "No students found!\n";
        fin.close();
    }

    static void removeStudentByRoll()
    {
        int roll;
        cout << "Enter Roll Number of student to remove: ";
        cin >> roll;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ifstream fin("attendance.dat", ios::binary);
        ofstream fout("temp.dat", ios::binary);

        Student temp;
        bool found = false;

        while(fin.read((char*)&temp, sizeof(temp)))
        {
            if(temp.getRollNo() == roll)
            {
                found = true;
                cout << "Removing student:\n";
                temp.displayPerson();
                continue;
            }
            fout.write((char*)&temp, sizeof(temp));
        }

        fin.close();
        fout.close();

        if(found)
        {
            remove("attendance.dat");
            rename("temp.dat", "attendance.dat");
            cout << "Student removed successfully!\n";
        }
        else
        {
            remove("temp.dat");
            cout << "Student not found!\n";
        }
    }

    static void markAttendanceForSubject(int sub, int month)
    {
        fstream file("attendance.dat", ios::binary|ios::in|ios::out);
        if(!file) { cout << "No students found!\n"; return; }

        Student temp;
        totalSubjectClasses[sub]++;
        totalSubjectMonthly[sub][month-1]++;
        totalClassesMonth[month-1]++;
        totalClasses++;

        while(file.read((char*)&temp, sizeof(temp)))
        {
            cout << "\nMark attendance for:\n";
            temp.displayPerson();

            char choice;
            while(true)
            {
                cout << "Present (P/p) or Absent (A/a)? ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(choice=='P'||choice=='p'||choice=='A'||choice=='a') break;
                cout << "Invalid input! Enter P/p or A/a.\n";
            }

            if(choice=='P'||choice=='p')
            {
                char type;
                while(true)
                {
                    cout << "Theory (T/t) or Practical (P/p)? ";
                    cin >> type;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if(type=='T'||type=='t'||type=='P'||type=='p') break;
                    cout << "Invalid input! Enter T/t or P/p.\n";
                }

                if(type=='T'||type=='t') temp.theoryAttendance[sub][month-1]++;
                else temp.practicalAttendance[sub][month-1]++;

                temp.subjectAttendance[sub]++;
                temp.subjectMonthlyAttendance[sub][month-1]++;
                temp.attendance++;
                temp.monthlyAttendance[month-1]++;
            }

            int pos = -1 * (int)sizeof(temp);
            file.seekp(pos, ios::cur);
            file.write((char*)&temp, sizeof(temp));
            file.flush();
        }

        cout << "Attendance updated!\n";
        file.close();
    }

    // ===== FIXED UNDO FUNCTION =====
    static void undoAttendanceForSubject(int sub, int month)
    {
        fstream file("attendance.dat", ios::binary|ios::in|ios::out);
        if(!file) { cout << "No students found!\n"; return; }

        int roll;
        cout << "Enter Roll Number of student to undo attendance: ";
        cin >> roll;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Student temp;
        bool found=false;
        while(file.read((char*)&temp, sizeof(temp)))
        {
            if(temp.getRollNo()==roll)
            {
                char type;
                cout << "Was attendance for Theory (T/t) or Practical (P/p)? ";
                cin >> type;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if((type=='T'||type=='t') && temp.theoryAttendance[sub][month-1]>0)
                    temp.theoryAttendance[sub][month-1]--;
                if((type=='P'||type=='p') && temp.practicalAttendance[sub][month-1]>0)
                    temp.practicalAttendance[sub][month-1]--;
                if(temp.subjectMonthlyAttendance[sub][month-1]>0)
                    temp.subjectMonthlyAttendance[sub][month-1]--;
                if(temp.subjectAttendance[sub]>0)
                    temp.subjectAttendance[sub]--;
                if(temp.attendance>0)
                    temp.attendance--;
                if(temp.monthlyAttendance[month-1]>0)
                    temp.monthlyAttendance[month-1]--;

                int pos=-1*(int)sizeof(temp);
                file.seekp(pos, ios::cur);
                file.write((char*)&temp, sizeof(temp));
                file.flush();
                found = true;
                cout << "Attendance undone successfully!\n";
                break;
            }
        }
        if(!found) cout << "Student not found!\n";
        file.close();
    }

    static void generateMonthlyReport(int month)
    {
        ifstream fin("attendance.dat", ios::binary);
        Student temp;
        cout << "\n===== MONTHLY ATTENDANCE REPORT =====\n";
        cout << "Do you want report for all students or specific student? (all/specific): ";
        string choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(choice=="all")
        {
            while(fin.read((char*)&temp, sizeof(temp)))
            {
                temp.displayMonthlyReport(month);
                cout << "------------------------\n";
            }
        }
        else
        {
            int roll;
            cout << "Enter Roll Number: ";
            cin >> roll;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool found=false;
            while(fin.read((char*)&temp, sizeof(temp)))
            {
                if(temp.getRollNo()==roll)
                {
                    temp.displayMonthlyReport(month);
                    found=true;
                    break;
                }
            }
            if(!found) cout << "Student not found!\n";
        }
        fin.close();
    }

    static void generateSubjectWiseReport(int month)
    {
        ifstream fin("attendance.dat", ios::binary);
        Student temp;
        cout << "\n===== SUBJECT-WISE REPORT =====\n";
        cout << "Do you want report for all students or specific student? (all/specific): ";
        string choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(choice=="all")
        {
            while(fin.read((char*)&temp, sizeof(temp)))
            {
                temp.displaySubjectWiseReport(month);
                cout << "------------------------\n";
            }
        }
        else
        {
            int roll;
            cout << "Enter Roll Number: ";
            cin >> roll;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool found=false;
            while(fin.read((char*)&temp, sizeof(temp)))
            {
                if(temp.getRollNo()==roll)
                {
                    temp.displaySubjectWiseReport(month);
                    found=true;
                    break;
                }
            }
            if(!found) cout << "Student not found!\n";
        }
        fin.close();
    }

    static void generateTheoryPracticalReport(int month)
    {
        ifstream fin("attendance.dat", ios::binary);
        Student temp;
        cout << "\n===== THEORY/ PRACTICAL REPORT =====\n";
        cout << "Do you want report for all students or specific student? (all/specific): ";
        string choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(choice=="all")
        {
            while(fin.read((char*)&temp, sizeof(temp)))
            {
                temp.displayTheoryPracticalReport(month);
                cout << "------------------------\n";
            }
        }
        else
        {
            int roll;
            cout << "Enter Roll Number: ";
            cin >> roll;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool found=false;
            while(fin.read((char*)&temp, sizeof(temp)))
            {
                if(temp.getRollNo()==roll)
                {
                    temp.displayTheoryPracticalReport(month);
                    found=true;
                    break;
                }
            }
            if(!found) cout << "Student not found!\n";
        }
        fin.close();
    }

    static void generateSemesterReport(int semester)
    {
        ifstream fin("attendance.dat", ios::binary);
        Student temp;
        cout << "\n===== SEMESTER REPORT =====\n";
        cout << "Do you want report for all students or specific student? (all/specific): ";
        string choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(choice=="all")
        {
            while(fin.read((char*)&temp, sizeof(temp)))
            {
                temp.displaySemesterReport(semester);
                cout << "------------------------\n";
            }
        }
        else
        {
            int roll;
            cout << "Enter Roll Number: ";
            cin >> roll;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool found=false;
            while(fin.read((char*)&temp, sizeof(temp)))
            {
                if(temp.getRollNo()==roll)
                {
                    temp.displaySemesterReport(semester);
                    found=true;
                    break;
                }
            }
            if(!found) cout << "Student not found!\n";
        }
        fin.close();
    }
};

int Student::totalClasses = 0;
int Student::totalClassesMonth[12] = {0};
int Student::totalSubjectClasses[3] = {0};
int Student::totalSubjectMonthly[3][12] = {0};

// ===== MAIN FUNCTION =====
int main()
{
    // ===== Teacher Login =====
    string username, password;
    cout << "===== TEACHER LOGIN =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if(username!="teacher" || password!="1234")
    {
        cout << "Invalid credentials! Exiting...\n";
        return 0;
    }

    cout << "Login successful!\n";

    int choice;
    do {
        cout << "\n===== STUDENT ATTENDANCE SYSTEM =====\n";
        cout << "1. Add New Student\n";
        cout << "2. Mark Subject-wise Attendance\n";
        cout << "3. View Overall Attendance\n";
        cout << "4. Generate Monthly Report (Overall/Specific)\n";
        cout << "5. Generate Subject-wise Monthly Report (Overall/Specific)\n";
        cout << "6. Generate Theory/Practical Report (Overall/Specific)\n";
        cout << "7. Generate Semester-wise Report (Overall/Specific)\n";
        cout << "8. Remove/Undo Attendance\n";
        cout << "9. Exit\n";
        cout << "10. Remove Student by Roll Number\n";

        while(true)
        {
            cout << "Enter choice: ";
            cin >> choice;
            if(cin.fail() || choice<1 || choice>10)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a number between 1 and 10.\n";
            } else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); break; }
        }

        if(choice==1)
        {
            char eraseChoice;
            cout << "Do you want to erase all previous data? (Y/N): ";
            cin >> eraseChoice;
            if(eraseChoice=='Y'||eraseChoice=='y')
            {
                ofstream fout("attendance.dat", ios::binary | ios::trunc);
                fout.close();
                Student::totalClasses=0;
                for(int i=0;i<12;i++) Student::totalClassesMonth[i]=0;
                for(int i=0;i<3;i++)
                    for(int j=0;j<12;j++) Student::totalSubjectMonthly[i][j]=0;
                for(int i=0;i<3;i++) Student::totalSubjectClasses[i]=0;
                cout << "All previous data erased!\n";
            }

            Student s;
            s.inputPerson();
            if(Student::isRollExist(s.getRollNo()))
                cout << "Student already exists!\n";
            else
            {
                s.saveToFile();
                cout << "Student Added Successfully!\n";
            }
        }
        else if(choice==2)
        {
            int sub, month;
            cout << "Select Subject:\n1. Biology\n2. Chemistry\n3. Physics\nEnter choice: ";
            cin >> sub;
            cout << "Enter month (1-12): ";
            cin >> month;
            if(sub<1||sub>3||month<1||month>12) { 
                cout << "Invalid input!\n"; 
                continue; 
            }
            Student::markAttendanceForSubject(sub-1, month);
        }
        else if(choice==3) { Student::readFromFile(); }
       else if(choice==4)
        {
            int month;
            cout << "Enter month (1-12): ";
            cin >> month;
            if(month<1||month>12) { cout << "Invalid month!\n"; continue; }
            Student::generateMonthlyReport(month);
        }
        else if(choice==5)
        {
            int month;
            cout << "Enter month (1-12): ";
            cin >> month;
            if(month<1||month>12) { cout << "Invalid month!\n"; continue; }
            Student::generateSubjectWiseReport(month);
        }
        else if(choice==6)
        {
            int month;
            cout << "Enter month (1-12): ";
            cin >> month;
            if(month<1||month>12) { cout << "Invalid month!\n"; continue; }
            Student::generateTheoryPracticalReport(month);
        }
        else if(choice==7)
        {
            int sem;
            cout << "Enter semester (1 or 2): ";
            cin >> sem;
            if(sem!=1&&sem!=2) { cout << "Invalid semester!\n"; continue; }
            Student::generateSemesterReport(sem);
        }
        else if(choice==8)
        {
            int sub, month;
            cout << "Select Subject to undo:\n1. Biology\n2. Chemistry\n3. Physics\nEnter choice: ";
            cin >> sub;
            cout << "Enter month (1-12): ";
            cin >> month;
            if(sub<1||sub>3||month<1||month>12) { cout << "Invalid input!\n"; continue; }
            Student::undoAttendanceForSubject(sub-1, month);
        }
        else if(choice==10) { Student::removeStudentByRoll(); }
        else if(choice==9) { cout << "Exiting system...\n"; }

    } while(choice!=9);

    return 0;
}
