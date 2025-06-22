#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <stdio.h>
#include <stdlib.h>
struct GradeEntry {
    char studentId[11];      // 10 digit ID with space for \0
    char assignmentName[21]; // max 20 char name with space for \0
    unsigned short grade;    // use format specifer %hu to print
};
struct Node {
    struct GradeEntry gradeEntry;
    struct Node* next;
};
typedef struct Node Node;
typedef struct GradeEntry GradeEntry;
Node* add_g(Node *head,GradeEntry* data);
Node* delete_g(Node *head,GradeEntry* data);
void print_g(Node *head);
void stats(Node *head, char name[21]);
int mstrcmp(const char *s1, const char *s2);
void mstrcpy(char *dest, const char *src);
void saveAndExit(Node* head, char* originalFilename);
void clean(Node *head);
int checkdup(Node* head,GradeEntry *data);
int mystrlen(char* str);
int is_all_digits(const char* str);
int isDigit(char c);
#endif