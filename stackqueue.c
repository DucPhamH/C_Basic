#include <stdio.h> 
#include <string.h> 
#include<stdlib.h>
struct Node{
    char xau[100];
    struct Node *next;
};
struct Node2{
    char xau2[100];
    struct Node2 *next;
};
struct Node *top = NULL;
struct Node2 *front = NULL, *rear = NULL;

void push(const char xau) {
    struct Node *new;
    new = (struct Node *)malloc(sizeof(struct Node));
    snprintf(new->xau, 2, "%c", xau);
    if (top == NULL) {
        new->next = NULL;
    } else {
        new->next = top; // Make the Node as top
    }
    top = new; // top always points to the newly created Node
    printf("Node is Inserted\n\n");
}

struct Node* pop() {
    char xau[100];
    if (top == NULL) {
        printf("\nStack Underflow\n");
    } else {
        struct Node *temp = top;
        strcpy(xau, temp->xau);
        top = top->next;
        free(temp);
        printf("Xoa thanh cong\n");   
    }
}

void display() {
    char *chuoi1 = malloc(100);
    memset(chuoi1, 0, 100);
    // Display the elements of the stack
    if (top == NULL) {
        printf("\nStack Underflow\n");
    } else {
        printf("The stack is \n");
        struct Node *temp = top;
        while (temp->next != NULL) {
            printf("%s\n", temp->xau);
            strcat(chuoi1, temp->xau);
            temp = temp->next;
        }
        printf("%s\n", temp->xau);
         strcat(chuoi1, temp->xau);
        printf("\nChuoi la: %s\n", chuoi1);
    }

    char *chuoi2 = malloc(100);
    memset(chuoi2, 0, 100);
    struct Node2 *temp = front;
    while(temp)
    {
        printf("%s\n", temp->xau2);
        strcat(chuoi2, temp->xau2);
        temp = temp->next;
    }
    printf("Chuoi la: %s\n", chuoi2);

    if(strcmp(chuoi1,chuoi2) == 0){
        printf("OK \n");
    }else{
        printf("Not ok\n");
    }
}

void enqueue(char xau)
{
    struct Node2 *new = malloc(sizeof(struct Node));
    snprintf(new->xau2, 2, "%c", xau);
    new->next = NULL;

    //if it is the first Node
    if(front == NULL && rear == NULL)
        //make both front and rear points to the new Node
        front = rear = new;
    else
    {
        //add new in rear->next
        rear->next = new;

        //make the new Node as the rear Node
        rear = new;
    }
}

void dequeue()
{
    //used to free the first Node after dequeue
    struct Node2 *temp;

    if(front == NULL)
         printf("Queue is Empty. Unable to perform dequeue\n");
    else
    {
        //take backup
        temp = front;

        //make the front Node points to the next Node
        //logically removing the front element
        front = front->next;

        //if front == NULL, set rear = NULL
        if(front == NULL)
            rear = NULL;

       //free the first Node
       free(temp);
    }

}

// void printList(){   
//     char *chuoi2 = malloc(100);
//     memset(chuoi2, 0, 100);
//     struct Node2 *temp = front;
//     while(temp)
//     {
//         printf("%s\n", temp->xau2);
//         strcat(chuoi2, temp->xau2);
//         temp = temp->next;
//     }
//     printf("Chuoi la: %s\n", chuoi2);
// }

int main(){ 
    char a[100];// khai bao chuoi a có toi da 100 ky tu
    printf("Nhap vao chuoi ky tu: "); 
    scanf("%s",a);
    int dem=0;//khai bao bien dem
    for(int i=0; i<strlen(a); i++){
       push(a[i]);
       enqueue(a[i]);
    }

    display();
    //printList();
   
}