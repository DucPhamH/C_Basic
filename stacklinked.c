#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct sinhVien{
    char mssv[10];
    char hoTen[30];
    float diem;
    struct sinhVien *next;
};
struct sinhVien *top = NULL;

void push(char *mssv, char *hoTen, float diem) {
    struct sinhVien *new;
    new = (struct sinhVien *)malloc(sizeof(struct sinhVien));

    strcpy(new->mssv, mssv);
    strcpy(new->hoTen, hoTen);
    new->diem = diem; // assign value to the sinhVien
    if (top == NULL) {
        new->next = NULL;
    } else {
        new->next = top; // Make the sinhVien as top
    }
    top = new; // top always points to the newly created sinhVien
    printf("sinhVien is Inserted\n\n");
}

struct sinhVien* pop() {
    char mssv[10];
    char hoTen[30];
    float diem;
    if (top == NULL) {
        printf("\nStack Underflow\n");
    } else {
        struct sinhVien *temp = top;
        strcpy(mssv, temp->mssv);
        strcpy(hoTen, temp->hoTen);
        diem = temp->diem;
        top = top->next;
        free(temp);
        printf("Xoa thanh cong\n");   
    }
}

void display() {
    // Display the elements of the stack
    if (top == NULL) {
        printf("\nStack Underflow\n");
    } else {
        printf("The stack is \n");
        struct sinhVien *temp = top;
        while (temp->next != NULL) {
            printf("%s %s %f\n", temp->mssv, temp->hoTen, temp->diem);
            temp = temp->next;
        }
        printf("%s %s %f\n", temp->mssv, temp->hoTen, temp->diem);
    }
}


int main(){
    int choice;
    char mssv[10];
    char hoTen[30];
    char filename[] = "sinhvien.txt";
    float diem;

    printf("\nImplementation of Stack using Linked List\n");
    while (1) {
        printf("1. Push\n2. Pop\n3. Display\n4. Exit\n");
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
            push(mssv, hoTen, diem);
            break;
        case 2:
            pop();
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\nWrong Choice\n");
        }
    }
}