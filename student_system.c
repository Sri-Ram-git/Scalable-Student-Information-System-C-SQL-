#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Function to execute SQL
void executeSQL(sqlite3 *db, const char *sql) {
    char *errMsg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        printf("SQL Error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

// Add student
void addStudent(sqlite3 *db) {
    int roll;
    char name[50];
    float marks;
    char sql[200];

    printf("Roll: ");
    scanf("%d", &roll);

    printf("Name: ");
    scanf(" %[^\n]", name);

    printf("Marks: ");
    scanf("%f", &marks);

    sprintf(sql,
        "INSERT INTO students VALUES (%d, '%s', %.2f);",
        roll, name, marks);

    executeSQL(db, sql);
    printf("Student added successfully.\n");
}

// View students
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    printf("Roll: %s | Name: %s | Marks: %s\n",
           argv[0], argv[1], argv[2]);
    return 0;
}

void viewStudents(sqlite3 *db) {
    char *errMsg = 0;
    sqlite3_exec(db, "SELECT * FROM students;", callback, 0, &errMsg);
}

// Search student
void searchStudent(sqlite3 *db) {
    int roll;
    char sql[100];

    printf("Enter roll number: ");
    scanf("%d", &roll);

    sprintf(sql,
        "SELECT * FROM students WHERE roll = %d;", roll);

    sqlite3_exec(db, sql, callback, 0, NULL);
}

// Delete student
void deleteStudent(sqlite3 *db) {
    int roll;
    char sql[100];

    printf("Enter roll to delete: ");
    scanf("%d", &roll);

    sprintf(sql,
        "DELETE FROM students WHERE roll = %d;", roll);

    executeSQL(db, sql);
    printf("Student deleted.\n");
}

int main() {
    sqlite3 *db;
    int choice;

    sqlite3_open("students.db", &db);

    // Create table if not exists
    executeSQL(db,
        "CREATE TABLE IF NOT EXISTS students ("
        "roll INTEGER PRIMARY KEY, "
        "name TEXT, "
        "marks REAL);");

    while (1) {
        printf("\n1.Add  2.View  3.Search  4.Delete  5.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(db); break;
            case 2: viewStudents(db); break;
            case 3: searchStudent(db); break;
            case 4: deleteStudent(db); break;
            case 5: sqlite3_close(db); exit(0);
            default: printf("Invalid choice\n");
        }
    }
}
