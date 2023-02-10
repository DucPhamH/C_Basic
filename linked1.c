#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct sinhVien{
    char mssv[10];
    char hoTen[30];
    float diem;
    struct sinhVien *next;
};


struct sinhVien *first = NULL;
struct sinhVien *last = NULL;

struct sinhVien* createsinhVien(char *mssv, char *hoTen, float diem){
    struct sinhVien *new = (struct sinhVien*)malloc(sizeof(struct sinhVien));
    strcpy(new->mssv, mssv);
    strcpy(new->hoTen, hoTen);
    new->diem = diem;
    return new;
}
void insertLast(char *mssv, char *hoTen, float diem){
    struct sinhVien *new = createsinhVien(mssv, hoTen, diem);
    new->next = NULL;
    if (first == NULL) first = new;
    if (last != NULL) last->next = new;
    last = new;
}

void printAllSinhVien(){
    struct sinhVien *temp = first;
    while(temp != NULL){
        printf("MSSV: %s\nHo Ten: %s\nDiem: %f\n\n", temp->mssv, temp->hoTen, temp->diem);
        temp = temp->next;
    }
}

    struct sinhVien* searchMssv(char *mssv){
    struct sinhVien *temp = first;
    while(temp != NULL){
        if(strcmp(temp->mssv,mssv) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}


void searchSinhVien(){
    struct sinhVien *temp;
    char mssv[10];
    printf("Nhap mssv can tim: ");
    scanf("%s", mssv);
    temp = searchMssv(mssv);
    if (temp != NULL){
        printf("MSSV: %s\nHo Ten: %s\nDiem: %f\n\n", temp->mssv, temp->hoTen, temp->diem);
    }else {
        printf("Khong tim thay mssv");
    }

}

int length(){
   int length = 0;
   struct sinhVien *temp;
	
   for(temp = first; temp != NULL; temp = temp->next)
	{
      length++;
   }
	
   return length;
}

struct sinhVien *deleteSinhVien(char *mssv){
    struct sinhVien *temp = first;
    struct sinhVien *pre = NULL;

    if(first == NULL){
        return NULL;
    }

    while(strcmp(temp->mssv,mssv) != 0){
        if(temp->next == NULL){
            return NULL;
        }else{
            pre = temp;
            temp = temp->next;
        }
    }

    if(temp == first) {
      first = first->next;
    }else {
      pre->next = temp->next;
    }    
	
    return temp;

}

void sort(){

   int i, j, k;
   float tempDiem ;
   char tempMssv[10];
   char tempHoTen[30];
   struct sinhVien *temp;
   struct sinhVien *next;
	
   int size = length();
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      temp = first;
      next = first->next;
		
      for ( j = 1 ; j < k ; j++ ) {   
		
         if ( (temp->diem) > (next->diem) ) {
            tempDiem = temp->diem ;
            temp->diem = next->diem;
            next->diem = tempDiem ;

            strcpy(tempMssv, temp->mssv);
            strcpy(temp->mssv, next->mssv);
            strcpy(next->mssv, tempMssv);

            strcpy(tempHoTen, temp->hoTen);
            strcpy(temp->hoTen, next->hoTen);
            strcpy(next->hoTen, tempHoTen);
         }
			
         temp = temp->next;
         next = next->next;                        
      }
   }   
}
void rewriteFile(char *filename){
    FILE *f = fopen(filename, "w+");
    if(f == NULL) exit(1);
    struct sinhVien *temp = first;
    while(temp != NULL){
        if(temp->next != NULL) fprintf(f,"%s %s %f\n\n",temp->mssv, temp->hoTen, temp->diem);
        else fprintf(f,"%s %s %f",temp->mssv, temp->hoTen, temp->diem);
        temp = temp->next;
    }
    fclose(f);
}

void readfile(char *filename){
    float diem ;
    char mssv[10];
    char hoTen[30];
    FILE *f = fopen(filename,"r");
    if(f == NULL) exit(1);
    while (fscanf(f,"%s %s %f\n",mssv, hoTen, &diem) != EOF) {
        printf("%s %s %f\n", mssv, hoTen, diem);
        //insertLast(username, password, status);
    }
    fclose(f);
}

int main( ){
    int n;
    char mssv[10];
    char hoTen[30];
    char filename[] = "sinhvien.txt";
    float diem;

    int menu = 0;
    
    while(1){
        printf("\nMenu\n-----------------------------------\n1. Nhap thong tin sinh vien\n2. Tim kiem sinh vien\n3. Xoa sinh vien\n4. In danh sách sinh vien\n5. Ghi thông tin\n6. Đọc thông tin\n7. Thoát\n Your choice (1-7, other to quit): ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
                // printf("Nhap n : ");
                // scanf("%d", &n);
                // if(n<2 || n>10){
                //     printf("Ban da nhap sai\n");
                //     exit(1);
                // }
                // fflush(stdin);

               // for (int i = 0; i < n; i++){
                    printf("Nhap MSSV: ");
                    scanf("%s", mssv);
                    printf("Nhap ho ten: ");
                    scanf("%s", hoTen);
                    // fgets(hoTen, sizeof(hoTen), stdin);
                    printf("Nhap diem: ");
                    scanf("%f", &diem);
                    insertLast(mssv, hoTen, diem);
                    
               // }
                break;

            case 2:
                searchSinhVien();
                break;

            case 3: 
                printf("Nhap mssv can xoa: ");
                scanf("%s", mssv);
                struct sinhVien *temp = deleteSinhVien(mssv);
                if (temp == NULL){
                    printf("Xóa thất bại, không tìm thấy mssv");
                    break;
                }else {
                    printf("Xóa thành công");
                    break;
                }
            
            case 4: 
                sort();
                printAllSinhVien();
                break;
            
            case 5:
                rewriteFile(filename);
                break;

            case 6:
                readfile(filename);
                break;

            case 7:  
                printf("Ban đã thoát chương trình\n");
                exit(0);
 
            default:
                printf("Vui lòng nhập lại\n");
                break;
        }
    }
     
    return 0;
}