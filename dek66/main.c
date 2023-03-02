#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

//linked
struct node{
    char bienSo[12];
    int gio, phut, giay, ngay, thang, nam;
    int loai;
    struct node *next;
};

struct node *first = NULL;
struct node *last = NULL;

struct node* createnode(char *bienSo, int gio, int phut, int giay, int ngay, int thang, int nam, int loai){
    struct node *new = (struct node*)malloc(sizeof(struct node));
    strcpy(new->bienSo, bienSo);
    new->gio = gio;
    new->phut = phut;
    new->giay = giay;
    new->ngay = ngay;
    new->thang = thang;
    new->nam = nam;
    new->loai = loai;
    return new;
}

void insertLast(char *bienSo, int gio, int phut, int giay, int ngay, int thang, int nam, int loai){
    struct node *new = createnode(bienSo, gio, phut, giay, ngay, thang, nam, loai);
    new->next = NULL;
    if (first == NULL) first = new;
    if (last != NULL) last->next = new;
    last = new;
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

void printAll(){
    struct node *temp = first;
    while(temp != NULL){
        printf("%4d-%02d-%02d %02d:%02d:%02d %s %d\n", temp->nam, temp->thang, temp->ngay, temp->gio, temp->phut, temp->giay, temp->bienSo, temp->loai);
        temp = temp->next;
    }
}

void readfile(char *filename){
    char bienSo[12];
    int gio, phut, giay, ngay, thang, nam;
    int loai;
    FILE *f = fopen(filename,"r");
    if(f == NULL) exit(1);
    while (fscanf(f,"%d-%d-%d %d:%d:%d %s %d\n",&nam, &thang, &ngay, &gio, &phut, &giay, bienSo, &loai) != EOF) {
        insertLast(bienSo, gio, phut, giay, ngay, thang, nam, loai);
    }
    fclose(f);
}

void historyLog(){
    char ngayThang[40];
    int ngay, thang, nam;
    int total = 0;
    int in = 0;
    int out = 0;
    struct node *temp = first;
    printf("Nhap ngay thang nam can tra cuu: ");
    scanf("%s", ngayThang);
    getchar();
    sscanf(ngayThang, "%d-%d-%d", &nam, &thang, &ngay );
  //  printf("Nam la: %4d, Thang la: %02d, Ngay la: %02d\n", nam, thang, ngay );
    

    while(temp!=NULL){
        if(temp->thang == thang && temp->ngay == ngay){
            total++;
            if(temp->loai == 1){
               in++;
            }else if(temp->loai == 0){
                out++;
            }
        }
        
        temp = temp->next;
    }

    printf("Date %4d-%02d-%02d Total %d, In %d, Out %d\n", nam, thang, ngay, total, in, out);


}

void historyCar(){
    int count = 0;
    char bienSo[12];
    printf("Nhap bien so can tim: ");
    scanf("%s", bienSo);
    struct node *temp = first;
    while(temp!=NULL){
        if(strcmp(temp->bienSo, bienSo)==0){
            printf("%4d-%02d-%02d %02d:%02d:%02d %s %d\n", temp->nam, temp->thang, temp->ngay, temp->gio, temp->phut, temp->giay, temp->bienSo, temp->loai);
            count++;
        }
        temp = temp->next;
    }
    if(count == 0){
        printf("Bien so %s Xe khong gui tai bai xe", bienSo);
    }


}





//Cay nhi phan
struct tree{
    char bienSo[12];
    int gio, phut, giay, ngay, thang, nam;
    int loai;
    struct tree *left, *right;
};

struct tree *root = NULL;

struct tree *newTree(char *bienSo, int gio, int phut, int giay, int ngay, int thang, int nam, int loai) {
  struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
   strcpy(temp->bienSo, bienSo);
    temp->gio = gio;
    temp->phut = phut;
    temp->giay = giay;
    temp->ngay = ngay;
    temp->thang = thang;
    temp->nam = nam;
    temp->loai = loai;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct tree *root) {
  if (root != NULL) {
    // Traverse left
    //printf("%s %s\n", root->user, root->viet);
    inorder(root->left);

    // Traverse root
    printf("%4d-%02d-%02d %02d:%02d:%02d %s %d\n",root->nam,root->thang,root->ngay,root->gio,root->phut,root->giay,root->bienSo,root->loai);

    // Traverse right
    inorder(root->right);
  }
}

struct tree *insert(struct tree *root, char *bienSo, int gio, int phut, int giay, int ngay, int thang, int nam, int loai) {
  // Return a new node if the tree is empty
  if (root == NULL) return newTree(bienSo, gio, phut, giay, ngay, thang, nam, loai);

  // Traverse to the right place and insert the node
  if (strcmp(bienSo, root->bienSo) < 0)
    root->left = insert(root->left, bienSo, gio, phut, giay, ngay, thang, nam, loai);
  else
    root->right = insert(root->right, bienSo, gio, phut, giay, ngay, thang, nam, loai);

  return root;
}



void info(){
    struct node *temp = first->next;
    struct node *cur = first;
    while(temp != NULL){
       if(cur->thang < temp->thang){
           cur = temp;
       }
     temp = temp->next;
    }
   

   int count = 0;
   struct node* t = NULL;
    while(cur != NULL){
        t = cur->next;
        while(t != NULL){
            if(strcmp(cur->bienSo, t->bienSo) == 0 || cur->loai == 0){
                 count++;
            }   
             t = t->next;  
        }
        if(count == 0){
            //printf("%4d-%02d-%02d %02d:%02d:%02d %s %d\n",cur->nam,cur->thang,cur->ngay,cur->gio,cur->phut,cur->giay,cur->bienSo,cur->loai);
            root = insert(root, cur->bienSo, cur->gio, cur->phut, cur->giay, cur->ngay, cur->thang, cur->nam, cur->loai);
        }
        cur = cur->next;
        count = 0;
    }
   
}

struct tree* search(struct tree *root, char *bienSo) {
  if (root == NULL || (strcmp(bienSo, root->bienSo) == 0)) {
    return root;
  }

  if (strcmp(bienSo, root->bienSo) < 0) {
    return search(root->left, bienSo);       
    }


  return search(root->right, bienSo);
}

void guiXe(){
    char bienSo[12];
    printf("Nhap bien so can gui: ");
    scanf("%s", bienSo);
    struct tree *temp = search(root, bienSo);
    if(temp != NULL){
        printf("Loi bien so da ton tai");
    }else{
        time_t rawtime;
        struct tm * timeinfo;

    // Lấy thời gian hiện tại
        time(&rawtime);
        timeinfo = localtime(&rawtime);

    // Lưu các giá trị ngày, tháng, năm, giờ, phút, giây vào các biến
        int ngay = timeinfo->tm_mday;
        int thang = timeinfo->tm_mon + 1; // Tháng bắt đầu từ 0, cộng thêm 1 để đưa về đúng tháng
        int nam = timeinfo->tm_year + 1900; // Năm bắt đầu từ 1900
        int gio = timeinfo->tm_hour;
        int phut = timeinfo->tm_min;
        int giay = timeinfo->tm_sec;
        
    // In ra các giá trị của các biến
    root = insert(root, bienSo, gio, phut, giay, ngay, thang, nam, 1);
    }
}

struct tree *minValueNode(struct tree *node) {
  struct tree *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a node
struct tree *deleteNode(struct tree *root, char *bienSo) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the node to be deleted
  if (strcmp(bienSo, root->bienSo) < 0)
    root->left = deleteNode(root->left, bienSo);
  else if (strcmp(bienSo, root->bienSo) > 0)
    root->right = deleteNode(root->right, bienSo);

  else {
    // If the node is with only one child or no child
    if (root->left == NULL) {
      struct tree *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct tree *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct tree *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
   // root->key = temp->key;
    strcpy(root->bienSo, temp->bienSo);
    root->gio = temp->gio;
    root->phut = temp->phut;
    root->giay = temp->giay;
    root->ngay = temp->ngay;
    root->thang = temp->thang;
    root->nam = temp->nam;
    root->loai = temp->loai;
    

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->bienSo);
  }
  return root;
}

void layXe(){
    struct tree* result = NULL;
    char bienSo[12];
    printf("Nhap bien so can gui: ");
    scanf("%s", bienSo);
    struct tree *temp = search(root, bienSo);
    if(temp != NULL){
        result = deleteNode(root, bienSo);
        if(result){
        printf("Lay xe thanh cong\n");
        }
    }else{
        printf("Lay xe khong thanh cong\n");
    }

}

void writeTree(FILE *fp, struct tree *root) {
  if (root == NULL) {
    return;
  }

  writeTree(fp, root->left);
  fprintf(fp,"%d-%d-%d %d:%d:%d %s %d\n",root->nam, root->thang, root->ngay, root->gio, root->phut, root->giay, root->bienSo, root->loai);
  writeTree(fp, root->right);
}

void writeToFile(struct tree *root, char *fileName) {
  FILE *fp;
  fp = fopen(fileName, "w+");

  if (fp == NULL) {
    printf("Could not open file %s", fileName);
    return;
  }

  writeTree(fp, root);
  fclose(fp);
}


int main()
{
   
    int menu = 0;
    int status = 0;
    char filename[] = "log_input.txt";
    char filename2[] = "log_persent.txt";
    int i;
    char filename[] = "log_input.txt";
    while(1){
        printf("Chuong trinh quan li bai xe\nVui long chon mot trong cac chuc nang sau\n[1] Doc du lieu tu file log \n[2] Tra cuu so luong xe gui/lay theo ngay trong qua khu\n[3] Thong tin cac xe trong bai hien tai\n[4] Gui them xe moi\n[5] Tra xe\n[6] Cap nhat Log du lieu\n[7] Luu danh sach xe dang co trong bai ra file\n[8] Thoat\nYour choice (1-8, other to quit): ");
        scanf("%d", &menu);
        getchar();
        switch(menu){
            case 1:
                if(status == 0){
                  readfile(filename);
                  printAll();
                    status++;
                    break;
                }else{
                   printf("Bạn đã đọc file này rồi\n");
                   break;
                }
                break;

            case 2:
                // i = length();
                // printf("%d\n", i);
                historyLog();
                // historyCar();
                break;

            case 3: 
               info();
               inorder(root);

                 
                break;
            case 4: 
               guiXe();
               inorder(root);
                 
                break;
            case 5: 
                
                layXe();
                inorder(root);
                break;

            case 6: 
               
                 
                break;

            case 7: 
               
                writeToFile(root, filename2);
                break;

            case 8:  
                printf("Ban đã thoát chương trình\n");
                exit(0);
 
            default:
                printf("Vui lòng nhập lại\n");
                break;
        }
    }

}