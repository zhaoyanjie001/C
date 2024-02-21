#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义学生结构体
struct Student {
    char name[50];
    int age;
    float grade;
    struct Student* next; // 指向下一个学生节点的指针
};

// 函数声明
void addStudent(struct Student** head, char* name, int age, float grade);
void displayStudents(struct Student* head);
void freeStudents(struct Student* head);

int main() {
    struct Student* head = NULL;

    // 添加学生信息
    addStudent(&head, "Alice", 20, 85.5);
    addStudent(&head, "Bob", 22, 76.0);
    addStudent(&head, "Charlie", 21, 92.3);

    // 显示学生信息
    displayStudents(head);

    // 释放内存
    freeStudents(head);

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
    printf("Student List:\n");
    while (head != NULL) {
        printf("Name: %s, Age: %d, Grade: %.2f\n", head->name, head->age, head->grade);
        head = head->next;
    }
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