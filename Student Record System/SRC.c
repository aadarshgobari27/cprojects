#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void modifyStudent();

int main() {
    int choice;
    while(1) {
        printf("\n---- Student Record System ----\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Modify Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: modifyStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Function to add a student
void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

// Function to display all students
void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    printf("\n%-10s %-20s %-10s\n", "Roll No", "Name", "Marks");
    printf("---------------------------------------------\n");

    while(fread(&s, sizeof(s), 1, fp)) {
        printf("%-10d %-20s %-10.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

// Function to search a student by roll number
void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.roll == roll) {
            printf("Record Found:\n");
            printf("Roll No: %d\nName: %s\nMarks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Student with Roll %d not found!\n", roll);

    fclose(fp);
}

// Function to delete a student by roll number
void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.roll != roll)
            fwrite(&s, sizeof(s), 1, temp);
        else
            found = 1;
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("Student deleted successfully.\n");
    else
        printf("Student with Roll %d not found.\n", roll);
}

// Function to modify student details
void modifyStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to Modify: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.roll == roll) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            printf("Record updated successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Student with Roll %d not found.\n", roll);

    fclose(fp);
}
