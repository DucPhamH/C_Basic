#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

struct sinhVien{
    char mssv[10];
    char hoTen[30];
    float diem;
};
typedef struct sinhVien SV;

SV intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

SV peek(){
   return intArray[front];
}

bool isEmpty(){
   return itemCount == 0;
}

bool isFull(){
   return itemCount == MAX;
}

int size(){
   return itemCount;
}  

void insert(SV data){

   if(!isFull()){
	
      if(rear == MAX-1){
         rear = -1;            
      }       

      intArray[++rear] = data;
      itemCount++;
   }
}

SV removeData(){
   SV data = intArray[front++];
	
   if(front == MAX){
      front = 0;
   }
	
   itemCount--;
   return data;  
}

int main() {

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
            if(isFull()){
                printf("Hang doi (Queue) da day!\n");   
            }
            SV data;
            printf("Nhap MSSV: ");
            fflush(stdin);
            scanf("%s", mssv);
            printf("Nhap ho ten: ");
            fflush(stdin);
            scanf("%s", hoTen);
            printf("Nhap diem: ");
            fflush(stdin);
            scanf("%f", &diem);
            strcpy(data.mssv, mssv);
            strcpy(data.hoTen, hoTen);
            data.diem = diem;
            insert(data);
            break;
        case 2:
            removeData();
            break;

        case 3:
            for(int i = 0; i < size(); i++){
                printf("%s %s %f\n",intArray[i].mssv, intArray[i].hoTen, intArray[i].diem );
            }
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\nWrong Choice\n");
        }
    }
   

   

   // xoa mot phan tu 
   
}