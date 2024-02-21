#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    char name[90];
    int age;
    float grade;
    struct student* next;
};
void addStudent( struct student** head, char* name,int age,float grade){
    struct student* newStudent = (struct student*) malloc(sizeof(struct student));
    if(newStudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newStudent->name,name);
    newStudent->age = age;
    newStudent->grade = grade;
    newStudent->next = NULL;
    if(*head == NULL) {
        *head = newStudent;
    } else {
        struct student* current = *head;
        while(current != NULL) {
            current=current->next;
        }
        current->next = newStudent;
    }

}
void displayStudents(struct student* head) {
    printf("student list:\n");
    while(head != NULL){
        printf("Name: %s, Age: %d, Grade: %.2f\n",head->name,head->age,head->grade);
        head = head->next;
    }
}
void freeStudents(struct student* head) {
    struct student* temp;
    while(head != NULL) {
        temp = head;
        head = head -> next;
        free(temp);
    }
}

int main() {
    struct student* head = NULL;

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