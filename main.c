#include <stdio.h>
#include <stdlib.h>
// udf data type node
typedef struct node
{
    int id;
    struct node *next;
} node;

// create a FIle to save infor..
void createfile();
void addStudent();
int main()
{
    node *head = malloc(sizeof(node));
    head->next = NULL;
    if (head == NULL)
    {
        printf("Memory allocation not possible\n");
        return 1;
    }
    while (1)
    {
        int action;
        printf("1. Enroll(add) student\n2. Remove Student\n3. exit\n(4. To create file)\n");
        printf("Enter your Action: ...");
        scanf("%d", &action);
        if (action == 1)
        {
            int st_id;
            printf("#######Enroll new Student########");
            printf("Enter student id: ");
            scanf("%d", &st_id);
        }
        else if (action == 3)
        {
            break;
        }
        else if (action == 4)
        {
            createfile("std.txt");
        }
    }
}
void createfile(char s1[])
{
    FILE *file;
    file = fopen(s1, "w");
    if (file == NULL)
    {
        printf("File not created\n");
    }
    else
    {
        printf("\"%s\" file created successfully\n");
    }
}
void addStudent(head , st_id){
    
    
}