#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义学生结构体
struct Student {
    char name[50];
    int age;
    float grade;
    struct Student* next;
};

// 函数声明
void addStudent(struct Student** head, char* name, int age, float grade);
void displayStudents(struct Student* head);
void saveStudentsToFile(struct Student* head, const char* filename);
void loadStudentsFromFile(struct Student** head, const char* filename);
void freeStudents(struct Student* head);

int main() {
    struct Student* head = NULL;

    // 添加学生信息
    addStudent(&head, "Alice", 20, 85.5);
    addStudent(&head, "Bob", 22, 76.0);
    addStudent(&head, "Charlie", 21, 92.3);

    // 显示学生信息
    printf("Student Information:\n");
    displayStudents(head);

    // 保存学生信息到文件
    saveStudentsToFile(head, "student_data.txt");

    // 释放内存
    freeStudents(head);

    // 从文件中加载学生信息
    struct Student* loadedHead = NULL;
    loadStudentsFromFile(&loadedHead, "student_data.txt");

    // 显示从文件中加载的学生信息
    printf("\nStudent Information (Loaded from File):\n");
    displayStudents(loadedHead);

    // 释放从文件中加载的学生信息内存
    freeStudents(loadedHead);

    return 0;
}

// 添加学生信息到链表
void addStudent(struct Student** head, char* name, int age, float grade) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->grade = grade;
    newStudent->next = NULL;

    if (*head == NULL) {
        *head = newStudent;
    } else {
        struct Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
}

// 显示学生信息
void displayStudents(struct Student* head) {
    while (head != NULL) {
        printf("Name: %s, Age: %d, Grade: %.2f\n", head->name, head->age, head->grade);
        head = head->next;
    }
}

// 保存学生信息到文件
void saveStudentsToFile(struct Student* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }

    while (head != NULL) {
        fprintf(file, "%s %d %.2f\n", head->name, head->age, head->grade);
        head = head->next;
    }

    fclose(file);
}

// 从文件中加载学生信息
void loadStudentsFromFile(struct Student** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        exit(1);
    }

    char name[50];
    int age;
    float grade;

    while (fscanf(file, "%s %d %f", name, &age, &grade) == 3) {
        addStudent(head, name, age, grade);
    }

    fclose(file);
}

// 释放学生链表内存
void freeStudents(struct Student* head) {
    struct Student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
