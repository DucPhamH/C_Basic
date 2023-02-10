#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

struct sinhVien{
    char mssv[10];
    char hoTen[30];
    float diem;
};
typedef struct sinhVien SV;

struct stack{
    int top;
    SV A[MAX];
};
typedef struct stack STACK;

void Init (STACK *s){
    //gan phan tu top cua stack bang -1 de khoi tao
    (*s).top=-1;
}
int Empty (STACK s){
    //neu phan tu top bang -1 thi stack rong va return 1
    if (s.top == -1){
        return 1;
    }
    //nguoc lai return 0
    return 0;
}
int IsFull (STACK s){
    //neu phan tu top cua stack bang MAX - 1 thi stack da day thi return 1
    if (s.top==MAX-1){
        return 1;
    }
    //nguoc lai return 0
    return 0;
}
void Push(STACK *s,SV x){
    // neu stack chua day thi thuc hien push
    if(IsFull(*s)==0){ 
        //tang chi so top len 1 don vi
        (*s).top++;
        //gan phan tu mang tai vi tri top bang gia tri x
        (*s).A[(*s).top]=x;
    }
}
SV Pop(STACK *s){
    //khai bao bien x de chua du lieu
    SV x;
     // neu stack khac rong
    if(!Empty(*s)){
        //thuc hien gan phan tu cuoi cua stack bang x
        x = (*s).A[(*s).top];
        //giam so luong phan tu mang di 1 don vi
        (*s).top--;
    }
    //tra ve x duoc gan bang phan tu cuoi cung cua stack
    return x;
}

SV Top(STACK s){
    //khai bao bien x de chua du lieu
    SV x;
     // stack khac rong
    if(!Empty(s)){
        //thuc hien gan phan tu cuoi bang x
        x = s.A[s.top];
        //tra ve x duoc gan bang phan tu cuoi cung cua mang
        return x;
    }else{ //neu stack do rong thi tra ve NULL
        exit(1);
    }
}


void Input(STACK *s, char *filename){
    float diem ;
    char mssv[10];
    char hoTen[30];
    FILE *f = fopen(filename,"r");
    if(f == NULL) exit(1);
    while (fscanf(f,"%s %s %f\n",mssv, hoTen, &diem) != EOF) {
       // printf("%s %s %f\n", mssv, hoTen, diem);
        SV x;
        strcpy(x.mssv, mssv);
        strcpy(x.hoTen, hoTen);
        x.diem = diem;
        Push(s,x);
    }
    fclose(f);   
}

void Output(STACK s, char *filename){
    FILE *f = fopen(filename, "w+");
    if(f == NULL) exit(1);
    //duyet tu phan tu top ve phan tu cuoi trong stack
    for(int i = s.top; i > -1; i--){
        //hien thi ra ket qua
        fprintf(f,"%s %s %f\n",s.A[i].mssv, s.A[i].hoTen, s.A[i].diem);
        printf("%s %s %f\n",s.A[i].mssv, s.A[i].hoTen, s.A[i].diem);
    }
    fclose(f);
}
int main(){
    //tao mot stack s
    STACK s;
    char filename[] = "sinhvien.txt";
    char filename2[] = "sinhvien2.txt";
    //khoi tao stack s
    Init(&s);
    //goi ham nhap n phan tu vao stack
    Input(&s,filename);
    //goi ham xuat cac phan tu o tron stact
    printf("Stack vua nhap la: \n");
    Output(s, filename2);
    //lay phan tu top cua stack ra nhung khong xoa
    //printf("Top cua stack voi ham top %d",Top(s));
    //lay phan tu top cua stack ra va xoa
    //printf("\nTop cua stack voi ham pop %d \n",Pop(&s));
    //printf("Stack sau khi pop la\n");
    //Output(s);
}