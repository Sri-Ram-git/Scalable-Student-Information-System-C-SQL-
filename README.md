# Scalable Student Information System (C, SQL)

This project is a menu-driven Student Information System developed in C with SQL-based data persistence using SQLite.

## Features
- Add, view, search, and delete student records
- Persistent storage using an embedded SQLite database
- Menu-driven console interface
- Executed and tested in Linux (WSL) environment

## Technologies Used
- C
- SQLite
- GCC
- Linux (WSL)

## How to Run
1. Install dependencies:

    sudo apt install gcc sqlite3 libsqlite3-dev

2. Compile the program:

   gcc student_system.c -lsqlite3 -o student_system


3. Run the program:

   ./student_system

