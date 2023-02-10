#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

struct node{
    int ID;       
    char CPU[5];
    int Ram;
    struct node *next;
};

struct node *first = NULL;
struct node *last = NULL;

struct node* createnode(int ID, char *CPU, int Ram){
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->ID = ID;
    strcpy(new->CPU, CPU);
    new->Ram = Ram;
    return new;
}

void insertLast(int ID, char *CPU, int Ram){
    struct node *new = createnode(ID, CPU, Ram);
    new->next = NULL;
    if (first == NULL) first = new;
    if (last != NULL) last->next = new;
    last = new;
}

void printAll(){
    struct node *temp = first;
    while(temp != NULL){
        printf("%d %s %d\n", temp->ID, temp->CPU, temp->Ram);
        temp = temp->next;
    }
}

int length(){
   int length = 0;
   struct node *temp;
	
   for(temp = first; temp != NULL; temp = temp->next)
	{
      length++;
   }
	
   return length;
}


struct node* searchID(int ID){
    struct node *temp = first;
    while(temp != NULL){
        if(temp->ID == ID) return temp;
        temp = temp->next;
    }
    return NULL;
}

struct node* searchCPU(char *CPU){
    struct node *temp = first;
    while(temp != NULL){
        if(strcmp(temp->CPU,CPU) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

struct node* searchRam(int Ram){
    struct node *temp = first;
    while(temp != NULL){
        if(temp->Ram == Ram) return temp;
        temp = temp->next;
    }
    return NULL;
}


void uploadCPUNext(struct node *temp){
    char CPU[5];
    char name1[] = "I7";
    char name2[] = "I5";
    char name3[] = "I3";
    char key[] = "STOP";

     while(temp != NULL){
        printf("%d %s %d\n", temp->ID, temp->CPU, temp->Ram);
        while (1) {
            printf("Upload CPU tiep theo: ");
            scanf("%s",CPU);
            if((strcmp(CPU,key)==0)){
                printf("Bạn đã dừng\n");
                break;
            }else if ((strcmp(CPU,name1)==0)||(strcmp(CPU,name2)==0)||(strcmp(CPU,name3)==0)) {
                strcpy(temp->CPU,CPU);
                break;
            }
            printf("Nhap sai ten CPU, hay nhap lai!\n");
        }
        if((strcmp(CPU,key)==0)){
            break;
        }
        temp = temp->next;
    }
}

void uploadCPU(){
    int ID;
    int size = length();
    char CPU[5];
    char name1[] = "I7";
    char name2[] = "I5";
    char name3[] = "I3";
    while (1) {
      printf("Nhap ID cua may: ");
      scanf("%d",&ID);
      if (ID > 0 && ID <= size) {
         break;
      }
      printf("Nhap sai ID, hay nhap lai!\n");
   }

    struct node *temp = searchID(ID);
    if(temp != NULL){
        while (1) {
        printf("Upload CPU cua may: ");
        scanf("%s",CPU);
        if ((strcmp(CPU,name1)==0)||(strcmp(CPU,name2)==0)||(strcmp(CPU,name3)==0)) {
            strcpy(temp->CPU,CPU);
            temp = temp->next;
            break;
        }
        printf("Nhap sai ten CPU, hay nhap lai!\n");
    }
    uploadCPUNext(temp);
 }
}

void uploadRamNext(struct node *temp){
    char Ram[10];
    
    char key[] = "STOP";

     while(temp != NULL){
        printf("%d %s %d\n", temp->ID, temp->CPU, temp->Ram);
        while (1) {
            printf("Upload Ram tiep theo: ");
            scanf("%s",Ram);
            if((strcmp(Ram,key)==0)){
                printf("Bạn đã dừng\n");
                break;
            }else if ((atoi(Ram) == 1)||(atoi(Ram) == 2)||(atoi(Ram) == 4)||(atoi(Ram) == 8)||(atoi(Ram) == 16)||(atoi(Ram) == 32)) {
                temp->Ram = atoi(Ram);
                break;
            }
            printf("Nhap sai Ram, hay nhap lai!\n");
        }
        if((strcmp(Ram,key)==0)){
            break;
        }
        temp = temp->next;
    }
}

void uploadRam(){
    int ID;
    int size = length();
    int Ram;
    
    while (1) {
      printf("Nhap ID cua may: ");
      scanf("%d",&ID);
      if (ID > 0 && ID <= size) {
         break;
      }
      printf("Nhap sai ID, hay nhap lai!\n");
   }

    struct node *temp = searchID(ID);
    if(temp != NULL){
        while (1) {
        printf("Upload Ram cua may: ");
        scanf("%d",&Ram);
        if ((Ram == 1)||(Ram == 2)||(Ram == 4)||(Ram == 8)||(Ram == 16)||(Ram == 32)) {
            temp->Ram = Ram;
            temp = temp->next;
            break;
        }
        printf("Nhap sai Ram, hay nhap lai!\n");
    }
    uploadRamNext(temp);
 }
}

void search(){
    char result[10];
    printf("Nhap từ can search: ");
    scanf("%s", result);
    struct node *temp = searchCPU(result);

    if(temp != NULL){
        while (temp != NULL) {
            if ((strcmp(temp->CPU,result) == 0)){
                printf("%s %d\n ",temp->CPU, temp->Ram);
            }         
            temp = temp->next;
        }  
    }else {
        struct node *temp2 = searchRam(atoi(result));
        if(temp2 != NULL){
        while (temp2 != NULL) {
            if (temp2->Ram == atoi(result)){
                printf("%s %d\n ",temp2->CPU, temp2->Ram);
            }         
            temp2 = temp2->next;
        }
     }else printf("Ban da nhap sai\n");
    }
}

void deleteList() {
   struct node* current = first;
   struct node* next;
   while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
   }
   first = NULL;
}



int main()
{   
    
    int ID = 0;       
    char CPU[5];
    int Ram;
    int soLuong;
    FILE *f;
    char filename[30];
    int menu = 0;
    int count;
    while(1){
        printf("Menu\n-----------------------------------\n1. Load Data Files\n2. Update CPU info\n3. Update Ram info\n4. Search\n5. Quit\nYour choice (1-5, other to quit): ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
                printf("Nhap ten file: ");
                scanf("%s", filename);
                f = fopen(filename,"r");
                if(f == NULL){
                    printf("File không tồn tại");
                    exit(1);
                }
                fscanf(f,"%d\n", &soLuong);
                printf("So Luong:%d\n", soLuong);
                while ((fscanf(f,"%s %d\n",CPU, &Ram) != EOF)&&(ID<20)){ 
                    ID = ID + 1;
                    insertLast(ID, CPU, Ram);
                }
                
                if(ID>=20){
                    printf("Danh sach da day, khong them duoc");
                }else printf("Doc thanh cong du lieu\n\n");

                fclose(f);
                break;

            case 2:
                uploadCPU();
                printAll();
                break;

            case 3: 
                uploadRam();
                printAll();
                break;
            case 4: 
                search();
                break;
            case 5:  
                deleteList();
                printf("Ban đã thoát chương trình\n");
                exit(0);
 
            default:
                printf("Vui lòng nhập lại\n");
                break;
        }
    }

}