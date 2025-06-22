#include "function.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // open file
  if (argc != 2) {
    printf("Usage: %s DATAFILE\n", argv[0]);
    return 1;
  }
  FILE *fp = fopen(argv[1], "r");//open file and check the if the file is open
  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }
  // declare necessary variables to read the file
  size_t nbyte1;
  ssize_t nchar1 = 0;
  char *line1 = NULL;
  Node *head = NULL;
  GradeEntry *data1 = malloc(sizeof(GradeEntry));
  if (data1 == NULL) {
    printf("Fail to allocate memory\n");
    fclose(fp);
    exit(1);
  }

  // read the file line by line
  while (1) {
    nchar1 = getline(&line1, &nbyte1, fp);
    if ( line1 == NULL) { // out of memory
            fclose(fp);
            free(data1);
            clean(head);
            exit(1);
        }
    if (nchar1 == -1) { // end of file reached
            break;
        }
    if (line1[nchar1 - 1] == '\n') {
            line1[nchar1 - 1] = '\0'; // remove newline
            nchar1--; // newline removed
        }
    int nmatch1 = sscanf(line1, "%10[^:]:%20[^:]:%hd", data1->studentId,
                         data1->assignmentName, &data1->grade);
    // seperate data one by one
    if (nmatch1 == 3) {
      int z = mystrlen(data1->studentId);        // check if the right format
      if(z==10&&is_all_digits(data1->studentId)==1&&data1->grade>=0&&data1->grade<=100){
        head = add_g(head, data1);}
      else{printf("invalid entry in the file\n");
      free(data1);
      fclose(fp);
      free(line1);
      clean(head);
      exit(1);

      }
    } else {
      printf(" There is an invalid input\n");
      free(data1);
      fclose(fp);
      free(line1);
      clean(head);
      exit(1);

    }
  }
  free(line1);//free the buffer
  free(data1);
  // declare necessary variables to read from stdin
  size_t nbyte;
  ssize_t nchar = 0;
  char *line = NULL;
  // char *inputLine = NULL;
  // read from stdin
  GradeEntry *data = malloc(sizeof(GradeEntry));
  // error check
  if (data == NULL) {
    printf("Fail to allocate memory\n");
    fclose(fp);
    clean(head);
    exit(1);
  }
  char action[11];



  //while stdin

  while (1) {
    nchar = getline(&line, &nbyte, stdin);
    if ( line == NULL) { // out of memory
            fclose(fp);
            free(data);
            clean(head);
            exit(1);
        }
    if (nchar == -1) { // end of file reached
            break;
        }
    if (line[nchar - 1] == '\n') {
            line[nchar - 1] = '\0'; // remove newline
            nchar--; // newline removed
        }
    // seperate the action
    int nmatch = sscanf(line, "%s", action);
    if (nmatch == 1) {
      if (mstrcmp(action, "print") == 0 ) {
          print_g(head);
      }

      else if (mstrcmp(action, "stats") == 0) {
        int nmatch1 = sscanf(line, "%*s %20[^\n]", data->assignmentName);
        if (nmatch1 == -1) {
          printf("Invalid input\n");
          continue;
        }
        stats(head, data->assignmentName);
      }

      else if (mstrcmp(action, "add") == 0) {
        int nFieldsParsed =sscanf(line, "%*s %10[^:]:%20[^:]:%hd", data->studentId,data->assignmentName, &(data->grade));
        if (nFieldsParsed == 3) { // Ensure all fields were parsed
          //check if the student ID already exist if not dup then add
          int x = mystrlen(data->studentId);
          if(x==10&&is_all_digits(data->studentId)==1){
            if(data->grade>=0&&data->grade<=100){
              if(checkdup(head, data)==0){head = add_g(head, data);}
              else{printf("Stats already exist. Try again.\n");}
            }
            else{printf("grade cannot be less than 0 or more than 100\n");}
          }
          else{printf("Not a valid student ID\n");}
        }
        else {
          printf("Invalid output\n");
        }
      }


      else if (mstrcmp(action, "remove") == 0) {
        int nFieldsParsed1 = sscanf(line, "%*s %10[^:]:%20[^\n]", data->studentId,data->assignmentName);
        if (nFieldsParsed1 == 2) { // Ensure all fields were parsed
          int m = mystrlen(data->studentId);
          if(m==10 &&is_all_digits(data->studentId)==1)
          head = delete_g(head, data);
          else
            printf("Not valid ID\n");
        }
        else
          printf("Invalid input\n");
      }
      else
      printf("Invalid input\n");
    }
  }
  //update the file
  char tempFilename[] = "XXXXXX";
    FILE *tempFile;
    if (mkstemp(tempFilename) == -1) {
        perror("Error creating temporary file");
        fclose(fp);
        free(line);
        free(data);
        clean(head);
        exit(1);
    }
    tempFile = fopen(tempFilename, "w");
    if (!tempFile) {
        perror("Error opening temporary file for writing");
        clean(head);
        free(line);
        free(data);
        fclose(fp);
        remove(tempFilename); // Cleanup
        exit(1);
    }
    Node * current = head;
    while (current != NULL) {
      int y = mystrlen(current->gradeEntry.studentId);
      if(y==10&&is_all_digits(current->gradeEntry.studentId)==1&&current->gradeEntry.grade>=0&&current->gradeEntry.grade<=100){
      fprintf(tempFile, "%s:%s:%hu\n", current->gradeEntry.studentId, current->gradeEntry.assignmentName, current->gradeEntry.grade);
      current = current->next;}
      else{printf("there is something wrong");
            fclose(tempFile);
            remove(tempFilename);
            free(line);
            fclose(fp);
            clean(head);
            free(data);
            exit(1);}
    }
    fclose(tempFile);
    if (rename(tempFilename, argv[1]) != 0) {
        perror("Error replacing the original file");
        if(remove(tempFilename)!=0){// Cleanup
        perror("Error deleting file");}
        free(line);
        fclose(fp);
        clean(head);
        free(data);
        exit(1);
    }
  free(line);
  fclose(fp);
  clean(head);
  free(data);
  return 0;
}
// End of main.c         