#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int studentID;
    char name[50];
    int age;
    char gender;
    char course[50];
};

typedef struct Student Student;

void loadFromFile(Student students[], int *count) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return;
    }

    *count = 0;
    while (fscanf(file, "%d %49s %d %c %49s", &students[*count].studentID, students[*count].name, &students[*count].age, &students[*count].gender, students[*count].course) == 5) {
        (*count)++;
    }

    fclose(file);
}

void saveToFile(Student students[], int count) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Could not open file\n");
        return;
    }
    
    int i;

    for (i = 0; i < count; i++) {
        fprintf(file, "%d %s %d %c %s\n", students[i].studentID, students[i].name, students[i].age, students[i].gender, students[i].course);
    }

    fclose(file);
}

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("The list is full.\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &students[*count].studentID);
    printf("Enter Name: ");
    getchar(); 
    fgets(students[*count].name, 50, stdin);
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0'; 
    printf("Enter Age: ");
    scanf("%d", &students[*count].age);
    printf("Enter Gender (M/F): ");
    scanf(" %c", &students[*count].gender);
    printf("Enter Course: ");
    scanf("%s", students[*count].course);

    (*count)++;
}

void displayStudents(Student students[], int count) {
    if (count == 0) {
        printf("No students information saved.\n");
        return;
    }
    
    int i;

    for (i = 0; i < count; i++) {
        printf("Student ID: %d\n", students[i].studentID);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Gender: %c\n", students[i].gender);
        printf("Course: %s\n\n", students[i].course);
    }
}

int searchStudent(Student students[], int count, int id) {
    int i;
	for ( i = 0; i < count; i++) {
        if (students[i].studentID == id) {
            return i;
        }
    }
    return -1;
}

void updateStudent(Student students[], int count, int id) {
    int index = searchStudent(students, count, id);
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    printf("Enter new details for Student ID %d:\n", id);
    printf("Enter Name: ");
    getchar(); // To consume the newline character left by previous input
    fgets(students[index].name, 50, stdin);
    students[index].name[strcspn(students[index].name, "\n")] = '\0'; // Remove the newline character from fgets
    printf("Enter Age: ");
    printf("Enter Age: ");
    scanf("%d", &students[index].age);
    printf("Enter Gender (M/F): ");
    scanf(" %c", &students[index].gender);
    printf("Enter Course: ");
    scanf("%s", students[index].course);
}

void deleteStudent(Student students[], int *count, int id) {
    int index = searchStudent(students, *count, id);
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    
    int i;

    for ( i = index; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }
    (*count)--;
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    loadFromFile(students, &count);

    while (1) {
        printf("Student Information Management System\n");
        printf("1. Add New Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n======== Add Student ========\n");
                addStudent(students, &count);
                saveToFile(students, count);
                break;
            case 2:
                printf("\n======== All Students ========\n");
                displayStudents(students, count);
                break;
            case 3: {
                int id;
                printf("\n======== Search Student ========\n");
                printf("Enter Student ID to search: ");
                scanf("%d", &id);
                int index = searchStudent(students, count, id);
                if (index != -1) {
                    printf("Student ID: %d\n", students[index].studentID);
                    printf("Name: %s\n", students[index].name);
                    printf("Age: %d\n", students[index].age);
                    printf("Gender: %c\n", students[index].gender);
                    printf("Course: %s\n", students[index].course);
                } else {
                    printf("Student with ID %d not found.\n", id);
                }
                break;
            }
            case 4: {
                int id;
                printf("\n======== Update Student ========\n");
                printf("Enter Student ID to update: ");
                scanf("%d", &id);
                updateStudent(students, count, id);
                saveToFile(students, count);
                break;
            }
            case 5: {
                int id;
                printf("\n======== Delete Student ========\n");
                printf("Enter Student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(students, &count, id);
                saveToFile(students, count);
                break;
            }
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("Press any key to return to the main menu...\n");
        getchar(); getchar(); // To pause the screen
    }

    return 0;
}

