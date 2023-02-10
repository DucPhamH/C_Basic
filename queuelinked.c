#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct sinhVien{
    char mssv[10];
    char hoTen[30];
    float diem;
    struct sinhVien *next;
};

struct sinhVien *front = NULL, *rear = NULL;

void enqueue(char *mssv, char *hoTen, float diem)
{
    struct sinhVien *new = malloc(sizeof(struct sinhVien));
    strcpy(new->mssv, mssv);
    strcpy(new->hoTen, hoTen);
    new->diem = diem; 
    new->next = NULL;

    //if it is the first sinhVien
    if(front == NULL && rear == NULL)
        //make both front and rear points to the new sinhVien
        front = rear = new;
    else
    {
        //add new in rear->next
        rear->next = new;

        //make the new sinhVien as the rear sinhVien
        rear = new;
    }
}

void dequeue()
{
    //used to free the first sinhVien after dequeue
    struct sinhVien *temp;

    if(front == NULL)
         printf("Queue is Empty. Unable to perform dequeue\n");
    else
    {
        //take backup
        temp = front;

        //make the front sinhVien points to the next sinhVien
        //logically removing the front element
        front = front->next;

        //if front == NULL, set rear = NULL
        if(front == NULL)
            rear = NULL;

       //free the first sinhVien
       free(temp);
    }

}

void printList()
{
    struct sinhVien *temp = front;

    while(temp)
    {
        printf("%s %s %f\n", temp->mssv, temp->hoTen, temp->diem);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    char mssv[10];
   char hoTen[30];
   char filename[] = "sinhvien.txt";
   float diem;

   int choice;
    while (1) {
        printf("1. Insert\n2. Pop\n3. Display\n4. Exit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Nhap MSSV: ");
            fflush(stdin);
            scanf("%s", mssv);
            printf("Nhap ho ten: ");
            fflush(stdin);
            scanf("%s", hoTen);
            printf("Nhap diem: ");
            fflush(stdin);
            scanf("%f", &diem);
            enqueue(mssv, hoTen, diem);
            break;
        case 2:
            dequeue();
            break;

        case 3:
            printList();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\nWrong Choice\n");
        }
    }

    
}