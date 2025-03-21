#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

#define MAX_COURSES 40
#define MAX_STUDENTS 100
#define MAX_EMPLOYEES 10
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

// Data Structures like course, student, Employee
typedef struct
{
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char instructor[MAX_NAME_LENGTH];
    int capacity;
    int enrolled;
} Course;

typedef struct
{
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char courses[MAX_COURSES][MAX_ID_LENGTH];
    int courseCount;
} Student;

typedef struct
{
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} Employee;

// Global Variables
Course courses[MAX_COURSES];
int courseCount = 0;
Student students[MAX_STUDENTS];
int studentCount = 0;
Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;
char waitlists[MAX_COURSES][MAX_STUDENTS][MAX_ID_LENGTH];
int waitlistCounts[MAX_COURSES] = {0};

// Function Prototypes
void managerMenu();
void employeeMenu();
void studentMenu();
int login(int userType); // 1: Manager, 2: Employee
void viewCourses();
void addEmployee();
void addCourse();
void dropCourse();
void enrollStudentManager();
void enrollStudentEmployee();
void viewEnrolledStudents();
void searchStudent();
void checkStudentStatus();
void generateReports();
void saveStudentRecords();
void loadStudentRecords();
void saveCourseRecords();
void loadCourseRecords();
void saveEmployeeRecords();
void loadEmployeeRecords();
int findStudent(char studentId[]);
int findCourse(char courseId[]);
void requestEnrollment();
void checkPersonalEnrollmentStatus(char studentId[]);
void downloadEnrollmentDetails(char studentId[]);
void viewWaitlistedStudents();
void addToWaitlist(int courseIndex, char studentId[]);
void processWaitlist(int courseIndex);
void dropCourseStudent(char studentId[], char courseId[]);
void viewEnrolledStudentsInCourse(char courseId[]);

// Main Function
int main()
{
    loadCourseRecords();
    loadStudentRecords();
    loadEmployeeRecords();

    int choice;
    while (1)
    {
        printf("\nStudent Management System\n");
        printf("1. Manager Login\n");
        printf("2. Employee Login\n");
        printf("3. Student Menu\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (login(1) == 1)
            {
                managerMenu();
            }
            break;
        case 2:
            if (login(2) == 1)
            {
                employeeMenu();
            }
            break;
        case 3:
            studentMenu();
            break;
        case 4:
            saveCourseRecords();
            saveStudentRecords();
            saveEmployeeRecords();
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

// Function Implementations
int login(int userType)
{
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (userType == 1 && strcmp(username, "manager") == 0 && strcmp(password, "123") == 0)
    {
        return 1; // Manager login
    }
    else if (userType == 2)
    {
        for (int i = 0; i < employeeCount; i++)
        {
            if (strcmp(employees[i].username, username) == 0 && strcmp(employees[i].password, password) == 0)
            {
                return 1; // Employee login
            }
        }
    }
    printf("Invalid credentials.\n");
    return 0;
}

void managerMenu()
{
    int choice;
    char courseId[MAX_ID_LENGTH]; // Declare here
    while (1)
    {
        printf("\nManager Menu\n");
        printf("1. View Courses\n");
        printf("2. Add Employee\n");
        printf("3. Add Course\n");
        printf("4. Drop Course\n");
        printf("5. Enroll Student\n");
        printf("6. View Enrolled Students\n");
        printf("7. Search Student\n");
        printf("8. Check Student Status\n");
        printf("9. Generate Reports\n");
        printf("10. Back to Main Menu\n");
        printf("11. View Waitlisted Students\n");
        printf("12. View Enrolled Students in a Course\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewCourses();
            break;
        case 2:
            addEmployee();
            break;
        case 3:
            addCourse();
            break;
        case 4:
            dropCourse();
            break;
        case 5:
            enrollStudentManager();
            break;
        case 6:
            viewEnrolledStudents();
            break;
        case 7:
            searchStudent();
            break;
        case 8:
            checkStudentStatus();
            break;
        case 9:
            generateReports();
            break;
        case 10:
            return;
        case 11:
            viewWaitlistedStudents();
            break;
        case 12:
            printf("Enter Course ID: ");
            scanf("%s", courseId);
            viewEnrolledStudentsInCourse(courseId);
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void employeeMenu()
{
    int choice;
    char courseId[MAX_ID_LENGTH]; // Declare here
    while (1)
    {
        printf("\nEmployee Menu\n");
        printf("1. View Courses\n");
        printf("2. Enroll Student\n");
        printf("3. View Enrolled Students\n");
        printf("4. View Waitlisted Students\n");
        printf("5. Check Student Status\n");
        printf("6. Back to Main Menu\n");
        printf("7. View Enrolled Students in a Course\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewCourses();
            break;
        case 2:
            enrollStudentEmployee();
            break;
        case 3:
            viewEnrolledStudents();
            break;
        case 4:
            viewWaitlistedStudents();
            break;
        case 5:
            checkStudentStatus();
            break;
        case 6:
            return;
        case 7:
            printf("Enter Course ID: ");
            scanf("%s", courseId);
            viewEnrolledStudentsInCourse(courseId);
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void studentMenu()
{
    int choice;
    char studentId[MAX_ID_LENGTH];
    char courseId[MAX_ID_LENGTH]; // Declare here
    printf("Enter your Student ID: ");
    scanf("%s", studentId);
    while (1)
    {
        printf("\nStudent Menu\n");
        printf("1. View Courses\n");
        printf("2. Request Enrollment\n");
        printf("3. Check Personal Enrollment Status\n");
        printf("4. Download Enrollment Details\n");
        printf("5. Back to Main Menu\n");
        printf("6. Drop Course\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewCourses();
            break;
        case 2:
            requestEnrollment();
            break;
        case 3:
            checkPersonalEnrollmentStatus(studentId);
            break;
        case 4:
            downloadEnrollmentDetails(studentId);
            break;
        case 5:
            return;
        case 6:
            printf("Enter Course ID to drop: ");
            scanf("%s", courseId);
            dropCourseStudent(studentId, courseId);
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void viewCourses()
{
    printf("\nCourses:\n");
    for (int i = 0; i < courseCount; i++)
    {
        printf("ID: %s, Name: %s, Instructor: %s, Capacity: %d, Enrolled: %d\n",
               courses[i].id, courses[i].name, courses[i].instructor, courses[i].capacity, courses[i].enrolled);
    }
}

void addEmployee()
{
    printf("\nAdd Employee\n");
    if (employeeCount < MAX_EMPLOYEES)
    {
        printf("Username: ");
        scanf("%s", employees[employeeCount].username);
        printf("Password: ");
        scanf("%s", employees[employeeCount].password);
        employeeCount++;
        saveEmployeeRecords();
        printf("Employee added successfully.\n");
    }
    else
    {
        printf("Maximum employees reached.\n");
    }
}

void addCourse()
{
    printf("\nAdd Course\n");
    if (courseCount < MAX_COURSES)
    {
        printf("ID: ");
        scanf("%s", courses[courseCount].id);
        printf("Name: ");
        scanf("%s", courses[courseCount].name);
        printf("Instructor: ");
        scanf("%s", courses[courseCount].instructor);
        printf("Capacity: ");
        scanf("%d", &courses[courseCount].capacity);
        courses[courseCount].enrolled = 0;
        waitlistCounts[courseCount] = 0; // Initialize waitlist count for the new course
        courseCount++;
        saveCourseRecords();
        printf("Course added successfully.\n");
    }
    else
    {
        printf("Maximum courses reached.\n");
    }
}

void dropCourse()
{
    char courseId[MAX_ID_LENGTH];
    printf("Enter Course ID to drop: ");
    scanf("%s", courseId);

    int courseIndex = findCourse(courseId);
    if (courseIndex == -1)
    {
        printf("Course not found.\n");
        return;
    }

    // Remove the course
    for (int i = courseIndex; i < courseCount - 1; i++)
    {
        courses[i] = courses[i + 1];
    }
    courseCount--;
    saveCourseRecords();
    printf("Course dropped successfully.\n");
}

void enrollStudentManager()
{
    char studentId[MAX_ID_LENGTH];
    char courseId[MAX_ID_LENGTH];

    printf("Enter Student ID: ");
    scanf("%s", studentId);
    printf("Enter Course ID: ");
    scanf("%s", courseId);

    int courseIndex = findCourse(courseId);
    int studentIndex = findStudent(studentId);

    if (courseIndex == -1)
    {
        printf("Course not found.\n");
        return;
    }

    if (studentIndex == -1)
    {
        printf("Student not found.\n");
        return;
    }

    if (courses[courseIndex].enrolled < courses[courseIndex].capacity)
    {
        // Enroll student in course
        courses[courseIndex].enrolled++;
        strcpy(students[studentIndex].courses[students[studentIndex].courseCount], courseId);
        students[studentIndex].courseCount++;
        saveStudentRecords();
        saveCourseRecords();
        printf("Student enrolled in course successfully.\n");
    }
    else
    {
        // Add to waitlist
        addToWaitlist(courseIndex, studentId);
    }
}

void enrollStudentEmployee()
{
    char studentId[MAX_ID_LENGTH];
    char courseId[MAX_ID_LENGTH];

    printf("Enter Student ID: ");
    scanf("%s", studentId);
    printf("Enter Course ID: ");
    scanf("%s", courseId);

    int courseIndex = findCourse(courseId);
    int studentIndex = findStudent(studentId);

    if (courseIndex == -1)
    {
        printf("Course not found.\n");
        return;
    }

    if (studentIndex == -1)
    {
        printf("Student not found.\n");
        return;
    }

    if (courses[courseIndex].enrolled < courses[courseIndex].capacity)
    {
        // Enroll student in course
        courses[courseIndex].enrolled++;
        strcpy(students[studentIndex].courses[students[studentIndex].courseCount], courseId);
        students[studentIndex].courseCount++;
        saveStudentRecords();
        saveCourseRecords();
        printf("Student enrolled in course successfully.\n");
    }
    else
    {
        // Add to waitlist
        addToWaitlist(courseIndex, studentId);
    }
}

void viewEnrolledStudents()
{
    printf("\nEnrolled Students:\n");
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].courseCount > 0)
        {
            printf("Student ID: %s, Name: %s\n", students[i].id, students[i].name);
            printf("Enrolled in Courses: ");
            for (int j = 0; j < students[i].courseCount; j++)
            {
                printf("%s ", students[i].courses[j]);
            }
            printf("\n");
        }
    }
}

void viewEnrolledStudentsInCourse(char courseId[])
{
    int courseIndex = findCourse(courseId);
    if (courseIndex == -1)
    {
        printf("Course not found.\n");
        return;
    }
    printf("\nEnrolled Students in Course %s:\n", courses[courseIndex].name);
    for (int i = 0; i < studentCount; i++)
    {
        for (int j = 0; j < students[i].courseCount; j++)
        {
            if (strcmp(students[i].courses[j], courseId) == 0)
            {
                printf("Student ID: %s, Name: %s\n", students[i].id, students[i].name);
                break; // Prevent duplicate printing of student info
            }
        }
    }
}

void searchStudent()
{
    char studentId[MAX_ID_LENGTH];
    printf("Enter Student ID to search: ");
    scanf("%s", studentId);

    int studentIndex = findStudent(studentId);
    if (studentIndex == -1)
    {
        printf("Student not found.\n");
    }
    else
    {
        printf("Student ID: %s, Name: %s\n", students[studentIndex].id, students[studentIndex].name);
        printf("Enrolled in Courses: ");
        for (int j = 0; j < students[studentIndex].courseCount; j++)
        {
            printf("%s ", students[studentIndex].courses[j]);
        }
        printf("\n");
    }
}

void checkStudentStatus()
{
    char studentId[MAX_ID_LENGTH];
    printf("Enter Student ID: ");
    scanf("%s", studentId);

    int studentIndex = findStudent(studentId);
    if (studentIndex == -1)
    {
        printf("Student not found.\n");
    }
    else
    {
        printf("Student ID: %s, Name: %s\n", students[studentIndex].id, students[studentIndex].name);
        printf("Enrolled in %d courses.\n", students[studentIndex].courseCount);
        if (students[studentIndex].courseCount > 0)
        {
            printf("Enrolled in courses: ");
            for (int i = 0; i < students[studentIndex].courseCount; i++)
            {
                printf("%s ", students[studentIndex].courses[i]);
            }
            printf("\n");
        }
    }
}

void generateReports()
{
    printf("\nCourse Report:\n");
    for (int i = 0; i < courseCount; i++)
    {
        printf("Course ID: %s, Name: %s, Enrolled: %d/%d\n", courses[i].id, courses[i].name, courses[i].enrolled, courses[i].capacity);
    }

    printf("\nStudent Report:\n");
    for (int i = 0; i < studentCount; i++)
    {
        printf("Student ID: %s, Name: %s, Enrolled in %d courses\n", students[i].id, students[i].name, students[i].courseCount);
    }
}

int findStudent(char studentId[])
{
    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].id, studentId) == 0)
        {
            return i;
        }
    }
    return -1;
}

int findCourse(char courseId[])
{
    for (int i = 0; i < courseCount; i++)
    {
        if (strcmp(courses[i].id, courseId) == 0)
        {
            return i;
        }
    }
    return -1;
}

void saveStudentRecords()
{
    FILE *file = fopen("students.txt", "w");
    if (file)
    {
        for (int i = 0; i < studentCount; i++)
        {
            fprintf(file, "%s %s %d", students[i].id, students[i].name, students[i].courseCount);
            for (int j = 0; j < students[i].courseCount; j++)
            {
                fprintf(file, " %s", students[i].courses[j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
    else
    {
        printf("Error saving student records.\n");
    }
}

void loadStudentRecords()
{
    FILE *file = fopen("students.txt", "r");
    if (file)
    {
        while (fscanf(file, "%s %s %d", students[studentCount].id, students[studentCount].name, &students[studentCount].courseCount) != EOF)
        {
            for (int j = 0; j < students[studentCount].courseCount; j++)
            {
                fscanf(file, "%s", students[studentCount].courses[j]);
            }
            studentCount++;
        }
        fclose(file);
    }
    else
    {
        printf("Error loading student records.\n");
    }
}

void saveCourseRecords()
{
    FILE *file = fopen("courses.txt", "w");
    if (file)
    {
        for (int i = 0; i < courseCount; i++)
        {
            fprintf(file, "%s %s %s %d %d\n", courses[i].id, courses[i].name, courses[i].instructor, courses[i].capacity, courses[i].enrolled);
        }
        fclose(file);
    }
    else
    {
        printf("Error saving course records.\n");
    }
}

void loadCourseRecords()
{
    FILE *file = fopen("courses.txt", "r");
    if (file)
    {
        while (fscanf(file, "%s %s %s %d %d", courses[courseCount].id, courses[courseCount].name, courses[courseCount].instructor, &courses[courseCount].capacity, &courses[courseCount].enrolled) != EOF)
        {
            courseCount++;
        }
        fclose(file);
    }
    else
    {
        printf("Error loading course records.\n");
    }
}
void addToWaitlist(int courseIndex, char studentId[]) {
    if (courseIndex < 0 || courseIndex >= courseCount) {
        printf("Invalid Course Index.\n");
        return;
    }
    if (waitlistCounts[courseIndex] < MAX_STUDENTS) {
        strcpy(waitlists[courseIndex][waitlistCounts[courseIndex]], studentId);
        waitlistCounts[courseIndex]++;
        printf("You have been added to the waitlist for %s.\n", courses[courseIndex].name);
    } else {
        printf("Waitlist for %s is full.\n", courses[courseIndex].name);
    }
}
void checkPersonalEnrollmentStatus(char studentId[]) {
    int studentIndex = findStudent(studentId);
    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("\nEnrollment Status for Student ID: %s\n", studentId);
    if (students[studentIndex].courseCount == 0) {
        printf("Not enrolled in any courses.\n");
    } else {
        printf("Enrolled in the following courses:\n");
        for (int i = 0; i < students[studentIndex].courseCount; i++) {
            int courseIndex = findCourse(students[studentIndex].courses[i]);
            if (courseIndex != -1) {
                printf("Course ID: %s, Course Name: %s\n", courses[courseIndex].id, courses[courseIndex].name);
            }
        }
    }
}
void downloadEnrollmentDetails(char studentId[]) {
    int studentIndex = findStudent(studentId);
    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    FILE *file = fopen("enrollment_details.txt", "w");
    if (file) {
        fprintf(file, "Enrollment Details for Student ID: %s\n", studentId);
        if (students[studentIndex].courseCount == 0) {
            fprintf(file, "Not enrolled in any courses.\n");
        } else {
            fprintf(file, "Enrolled in the following courses:\n");
            for (int i = 0; i < students[studentIndex].courseCount; i++) {
                int courseIndex = findCourse(students[studentIndex].courses[i]);
                if (courseIndex != -1) {
                    fprintf(file, "Course ID: %s, Course Name: %s\n", courses[courseIndex].id, courses[courseIndex].name);
                }
            }
        }
        fclose(file);
        printf("Enrollment details downloaded to enrollment_details.txt\n");
    } else {
        printf("Error downloading enrollment details.\n");
    }
}
void dropCourseStudent(char studentId[], char courseId[]) {
    int studentIndex = findStudent(studentId);
    int courseIndex = findCourse(courseId);

    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }
    if (courseIndex == -1) {
        printf("Course not found.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < students[studentIndex].courseCount; i++) {
        if (strcmp(students[studentIndex].courses[i], courseId) == 0) {
            found = 1;
            // Shift courses to remove the dropped course
            for (int j = i; j < students[studentIndex].courseCount - 1; j++) {
                strcpy(students[studentIndex].courses[j], students[studentIndex].courses[j + 1]);
            }
            students[studentIndex].courseCount--;
            courses[courseIndex].enrolled--; // Decrement the enrolled count for the course.
            saveStudentRecords();
            saveCourseRecords();
            printf("Course dropped successfully.\n");

            // Process the waitlist for the course.
            processWaitlist(courseIndex);
            break;
        }
    }
    if (!found) {
        printf("Student is not enrolled in this course.\n");
    }
}
void loadEmployeeRecords() {
    FILE *file = fopen("employees.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s", employees[employeeCount].username, employees[employeeCount].password) != EOF) {
            employeeCount++;
        }
        fclose(file);
    } else {
        printf("Error loading employee records.\n");
    }
}
void requestEnrollment() {
    char studentId[MAX_ID_LENGTH];
    char courseId[MAX_ID_LENGTH];

    printf("Enter your Student ID: ");
    scanf("%s", studentId);
    printf("Enter Course ID to request enrollment: ");
    scanf("%s", courseId);

    int courseIndex = findCourse(courseId);
    int studentIndex = findStudent(studentId);

    if (courseIndex == -1) {
        printf("Course not found.\n");
        return;
    }
    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    if (courses[courseIndex].enrolled < courses[courseIndex].capacity) {
        // Enroll student in course
        courses[courseIndex].enrolled++;
        strcpy(students[studentIndex].courses[students[studentIndex].courseCount], courseId);
        students[studentIndex].courseCount++;
        saveStudentRecords();
        saveCourseRecords();
        printf("You have been enrolled in the course.\n");
    } else {
        // Add to waitlist
        addToWaitlist(courseIndex, studentId);
    }
}
void saveEmployeeRecords() {
    FILE *file = fopen("employees.txt", "w");
    if (file) {
        for (int i = 0; i < employeeCount; i++) {
            fprintf(file, "%s %s\n", employees[i].username, employees[i].password);
        }
        fclose(file);
    } else {
        printf("Error saving employee records.\n");
    }
}
void processWaitlist(int courseIndex) {
    if (courseIndex < 0 || courseIndex >= courseCount) {
        printf("Invalid Course Index.\n");
        return;
    }
    if (waitlistCounts[courseIndex] > 0 && courses[courseIndex].enrolled < courses[courseIndex].capacity) {
        char studentId[MAX_ID_LENGTH];
        strcpy(studentId, waitlists[courseIndex][0]); // Get the first student in the waitlist.

        // Remove the first student from the waitlist and shift the rest of the queue.
        for (int i = 0; i < waitlistCounts[courseIndex] - 1; i++) {
            strcpy(waitlists[courseIndex][i], waitlists[courseIndex][i + 1]);
        }
        waitlistCounts[courseIndex]--;

        int studentIndex = findStudent(studentId);
        if (studentIndex != -1) {
            // Enroll the student
            courses[courseIndex].enrolled++;
            strcpy(students[studentIndex].courses[students[studentIndex].courseCount], courses[courseIndex].id);
            students[studentIndex].courseCount++;
            saveStudentRecords();
            saveCourseRecords();
            printf("Student %s has been enrolled in %s from the waitlist.\n", students[studentIndex].name, courses[courseIndex].name);
        } else {
            printf("Error: Student ID %s not found in the student database.\n", studentId);
        }
    } else if (courses[courseIndex].enrolled >= courses[courseIndex].capacity) {
        printf("Course %s is still full.\n", courses[courseIndex].name);
    } else {
        printf("Waitlist for %s is empty.\n", courses[courseIndex].name);
    }
}
void viewWaitlistedStudents() {
    printf("\nWaitlisted Students:\n");
    for (int i = 0; i < courseCount; i++) {
        if (waitlistCounts[i] > 0) {
            printf("Course: %s\n", courses[i].name);
            for (int j = 0; j < waitlistCounts[i]; j++) {
                int studentIndex = findStudent(waitlists[i][j]);
                if (studentIndex != -1) {
                    printf("  Student ID: %s, Student Name: %s\n", waitlists[i][j], students[studentIndex].name);
                }
            }
        }
    }
}