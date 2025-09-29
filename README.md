# Student Attendance Management System

## 📌 Overview

This is a **C++ console-based Student Attendance Management System** that allows teachers to manage students’ attendance records **subject-wise, month-wise, semester-wise, and with theory/practical distinction**. It uses **file handling (binary files)** for persistent storage of student records.

## ✨ Features

* 👨‍🏫 **Teacher Login System** (Default: `username = teacher`, `password = 1234`)
* ➕ Add New Students (with option to erase old records)
* 📖 Mark Attendance

  * Subject-wise (Biology, Chemistry, Physics)
  * Theory/Practical distinction
  * Monthly records
* 📊 Reports

  * Overall Attendance
  * Monthly Report (overall/specific student)
  * Subject-wise Monthly Report (overall/specific)
  * Theory/Practical Report (overall/specific)
  * Semester-wise Report (overall/specific)
* 🗑 Remove / Undo Attendance for a specific student
* ❌ Remove Student by Roll Number
* 💾 Data stored permanently in `attendance.dat`

---

## ⚙️ How It Works

1. **Login as Teacher**

   ```
   Username: teacher
   Password: 1234
   ```
2. **Choose an Option** from the main menu:

   ```
   1. Add New Student
   2. Mark Subject-wise Attendance
   3. View Overall Attendance
   4. Generate Monthly Report
   5. Generate Subject-wise Monthly Report
   6. Generate Theory/Practical Report
   7. Generate Semester-wise Report
   8. Remove/Undo Attendance
   9. Exit
   10. Remove Student by Roll Number
   ```

---

## 📂 File Structure

```
📁 Attendance-System
 ┣ 📜 main.cpp        # Main program file
 ┣ 📜 attendance.dat  # Binary file storing student records (auto-generated)
 ┗ 📜 README.md       # Project documentation
```

---

## 🛠 Requirements

* C++ Compiler (g++, clang++, or MSVC)
* Any IDE or text editor (VS Code, Code::Blocks, DevC++, etc.)

---

## ▶️ How to Run

### On Linux/Mac:

```bash
g++ main.cpp -o attendance
./attendance
```

### On Windows (MinGW/VS Code):

```bash
g++ main.cpp -o attendance.exe
attendance.exe
```

---

## 🔐 Default Credentials

* **Username:** `teacher`
* **Password:** `1234`

---

## 📊 Example Usage

```
===== TEACHER LOGIN =====
Username: teacher
Password: 1234
Login successful!

===== STUDENT ATTENDANCE SYSTEM =====
1. Add New Student
2. Mark Subject-wise Attendance
...
Enter choice: 1
Do you want to erase all previous data? (Y/N): N
Enter Name: John Doe
Enter Roll Number: 101
Student Added Successfully!
```

---

## 🚀 Future Improvements

* Add **multiple teacher logins**
* Add **GUI interface**
* Export reports to **CSV/PDF**
* Implement **percentage-based attendance warning system**

---

## 👨‍💻 Author

Developed as a **C++ project** for learning:

* File Handling
* Object-Oriented Programming
* Data Persistence
* Error Handling

---
