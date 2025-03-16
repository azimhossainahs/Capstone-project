#include<stdio.h>
//udf data type node
typedef struct node
{
    int id;
    struct node *next;
} node;
int main()
{
    node *head = malloc(sizeof(node));
    head->next = NULL;
    if(head == NULL ){
        printf("Memory allocation not possible\n");
        return 1;
    }
    while(1){
        int action;
        printf("1. Enroll(add) student\n2. Remove Student\n3. exit\n");
        printf("Enter your Action: ...");
        scanf("%d", &action);
        if(action == 1){
            int st_id;
            printf("#######Enroll new Student########");
            printf("Enter student id: ");
            scanf("%d", &st_id);
            addStudent(head, st_id);
        }
    }
    
}