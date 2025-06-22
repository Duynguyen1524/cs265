#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int mystrlen(char* str){
   const char *ptr = str; // Pointer to traverse the string
    // Increment the pointer until the null terminator is encountered
    while (*ptr) {
        ++ptr;
    }
    // Calculate and return the length of the string
    return (ptr - str);
}
//checked
int mstrcmp(const char *s1, const char *s2) {
  int i = 0;
  while (s1[i] != '\0' && s2[i] != '\0') {
    if (s1[i] != s2[i]) {
      return s1[i] - s2[i];
    }
    i++;
  }
  return s1[i] - s2[i];
}
//checked
void mstrcpy(char *dest, const char *src) {
  int i = 0;
  while ((dest[i] = src[i]) != '\0') {
    i++;
  }
}
//checked
Node *add_g(Node *head, GradeEntry *data) {
  Node *new_node = malloc(sizeof(Node));
  if (!new_node) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
  mstrcpy(new_node->gradeEntry.studentId, data->studentId);
  mstrcpy(new_node->gradeEntry.assignmentName, data->assignmentName);
  new_node->gradeEntry.grade = data->grade;
  new_node->next = NULL;
  if (head == NULL) {
    return new_node;
  }

  Node *temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = new_node;
  return head;
}
Node *delete_g(Node *head, GradeEntry *data) {
    if (head == NULL)
        return NULL;
    Node *temp = head, *prev = NULL;
    // Check if the head node is the one to be deleted
    if (mstrcmp(head->gradeEntry.assignmentName, data->assignmentName) == 0 &&
        mstrcmp(head->gradeEntry.studentId, data->studentId) == 0) {
        head = head->next; // Move head to next node
        free(temp);        // Free old head
        return head;
    }
    // Search for the node to be deleted
    while (temp != NULL && (mstrcmp(temp->gradeEntry.assignmentName, data->assignmentName) != 0 ||
                            mstrcmp(temp->gradeEntry.studentId, data->studentId) != 0)) {
        prev = temp;
        temp = temp->next;
    }
    // If the node was found
    if (temp != NULL) {
        if (prev != NULL)
            prev->next = temp->next; // Unlink the node from the list

        free(temp); // Free the node
    } else {
        printf("Entry not found\n");
    }
    return head;
}

void print_g(Node *head) {
  printf("%-10s | %-20s| %-5s\n", "Student ID", "Assignment Name", "Grade");
  printf("---------------------------------------------------\n");
  Node *temp = head;
  while (temp != NULL) {
    printf("%-10s | %-20s| %-5hu\n", temp->gradeEntry.studentId,
           temp->gradeEntry.assignmentName, temp->gradeEntry.grade);
    temp = temp->next;
  }
}

void stats(Node *head, char *assignmentName) {
  if (head == NULL) {
    printf("No entries found.\n");
    return;
  }

  Node *temp = head;
  int Min = 100;
  int Max = 0;
  int Sum = 0;
  int count = 0;

  while (temp != NULL) {
    if (mstrcmp(temp->gradeEntry.assignmentName, assignmentName) == 0) {
      if (temp->gradeEntry.grade < Min) {
        Min = temp->gradeEntry.grade;
      }
      if (temp->gradeEntry.grade > Max) {
        Max = temp->gradeEntry.grade;
      }
      Sum += temp->gradeEntry.grade;
      count++;
    }
    temp = temp->next;
  }

  if (count == 0) {
    printf("No entries found for %s\n", assignmentName);
    return;
  }

  float Mean = (float)Sum / count; // Ensure float division for accurate mean

  printf("Grade statistics for %s:\n", assignmentName);
  printf("Min: %d\n", Min);
  printf("Max: %d\n", Max);
  printf("Mean: %.2f\n", Mean); // Format mean to two decimal places
}

void clean(Node *head) {
    Node *next;


    while (head != NULL) {
        next = head->next;
        // Assuming each Node contains a GradeEntry pointer that needs to be freed.
        // free(&(head->gradeEntry)); // Free the GradeEntry data pointed to by the node.
        free(head); // Then free the Node itself.
        head = next;
    }

}

int checkdup(Node* head, GradeEntry* data) {
    Node* temp = head;
    while (temp != NULL) {
        if (mstrcmp(temp->gradeEntry.assignmentName, data->assignmentName) == 0 &&
            mstrcmp(temp->gradeEntry.studentId, data->studentId) == 0) {
            // Found a duplicate
            return 1;
        }
        temp = temp->next; // Move to the next node in the list
    }
    // No duplicates found
    return 0;
}

int isDigit(char c) {
    if (c >= '0' && c <= '9')
        return 1; // True
    return 0; // False
}

int is_all_digits(const char* str) {
    while (*str) {
        // Use the custom isDigit function instead of the standard isdigit
        if (!isDigit(*str)) {
            return 0; // False
        }
        str++;
    }
    return 1; // True
}
// int check_format(char* input){
  // char temp[100];
  // mstrcpy(temp, input);
  // temp[sizeof(input)-1]=
// }