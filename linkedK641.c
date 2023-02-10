#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
    char diaDiem[40];
    int gio;
    int phut;
    struct node *next;
};

struct node *first = NULL;
struct node *last = NULL;

struct node* createnode(char *diaDiem, int gio, int phut){
    struct node *new = (struct node*)malloc(sizeof(struct node));
    strcpy(new->diaDiem, diaDiem);
    new->gio = gio;
    new->phut = phut;
    return new;
}

void insertLast(char *diaDiem, int gio, int phut){
    struct node *new = createnode(diaDiem, gio, phut);
    new->next = NULL;
    if (first == NULL) first = new;
    if (last != NULL) last->next = new;
    last = new;
}

void printAllDiaDiem(){
    struct node *temp = first;
    while(temp != NULL){
        printf("%s %d %d\n", temp->diaDiem, temp->gio, temp->phut);
        temp = temp->next;
    }
}

void readfile(char *filename){
    char diaDiem[40];
    int gio;
    int phut;
    FILE *f = fopen(filename,"r");
    if(f == NULL) exit(1);
    while (fscanf(f,"%s %d %d\n",diaDiem,&gio,&phut) != EOF){ 
        //printf("%s, %s, %d\n", diaDiem, password, status);
        insertLast(diaDiem, gio, phut);
    }
    printf("Doc thanh cong du lieu\n\n");
    fclose(f);
}

struct node* searchThoiGian(int gio, int phut){
    struct node *temp = first;
    while(temp != NULL){
        if((temp->gio == gio)&&(temp->phut == phut)) return temp;
        temp = temp->next;
    }
    return NULL;
}

void thoiGian(){
    int gio;
    int phut;
    while (1) {
      printf("Nhap gio: ");
      scanf("%d", &gio);
      if (gio >= 0 && gio < 24) {
         break;
      }
      printf("Nhap sai gio, hay nhap lai!\n");
   }
    while (1) {
      printf("Nhap phut: ");
      scanf("%d", &phut);
      if (phut >= 0 && phut < 60) {
         break;
      }
      printf("Nhap sai phut, hay nhap lai!\n");
   }
   printf("%d:%d\n", gio, phut);
   struct node *temp = searchThoiGian(gio,phut);
   if(temp!=NULL){
     printf("%s", temp->diaDiem);
   }else printf("KHONG tim thay lịch su di chuyen");

}

void diaDiem(){
    char diaDiem[40];
    int count = 0;
    printf("Nhap dia diem: ");
    fflush(stdin);
    scanf("%s", diaDiem);
    struct node *temp = first;

    while (temp != NULL) {
      if ((strcmp(temp->diaDiem,diaDiem) == 0)){
        printf("%d:%d, ",temp->gio, temp->phut);
        count++;
      }         
      temp = temp->next;
   }  

    if(count == 0){
        printf("Ban chua toi dia diem do\n");
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

void truyVet(){
   char diaDiem[40];
   int gio;
   int phut;
   int count = 0;
    printf("Nhap dia diem: ");
    fflush(stdin);
    scanf("%s", diaDiem);

     while (1) {
      printf("Nhap gio: ");
      scanf("%d", &gio);
      if (gio >= 0 && gio < 24) {
         break;
      }
      printf("Nhap sai gio, hay nhap lai!\n");
   }
    while (1) {
      printf("Nhap phut: ");
      scanf("%d", &phut);
      if (phut >= 0 && phut < 60) {
         break;
      }
      printf("Nhap sai phut, hay nhap lai!\n");
   }

    struct node *temp = first;

    while (temp != NULL) {
      if ((strcmp(temp->diaDiem,diaDiem) == 0)){
        if((temp->gio == gio)&&(temp->phut >= phut)){
            printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!\n");
        }else if(temp->gio > gio){
            printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!\n");
        }else printf("LIch su di chuyen cua ban OK\n");
        count++;
      }         
      temp = temp->next;
   }  

    if(count == 0){
        printf("LIch su di chuyen cua ban OK\n");
        return;
    }
}

int main(){

    char filename[] = "log.txt";
    int menu = 0;
    int status = 0;
    
    while(1){
        printf("\nMenu\n-----------------------------------\n1. Nạp dữ liệu log lịch sử di chuyển\n2. In ra lịch sử di chuyển\n3. Tìm kiếm lịch sử di chuyển theo địa điểm\n4. Tìm kiếm thông tin di chuyển theo thời gian\n5. Kiểm tra truy vết mới nhất\n6. Thoát\nYour choice (1-6, other to quit): ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
                if(status == 0){
                  readfile(filename);
                  status++;
                  break;
                }else{
                    printf("Bạn đã đọc file này rồi\n");
                    break;
                }
            case 2:
                printAllDiaDiem();
                break;

            case 3: 
                diaDiem();
                break;
            case 4: 
                thoiGian();
                break;
            case 5: 
                truyVet();
                break;
            case 6: 
                deleteList();
                printf("Ban đã thoát chương trình\n");
                exit(0);
 
            default:
                printf("Vui lòng nhập lại\n");
                break;
        }
    }

}
