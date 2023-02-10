#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define soNgayKhaoSat 10
struct node {
  char MaCoPhieu[11];
  float GiaMo[soNgayKhaoSat];
  float GiaDong[soNgayKhaoSat];
  struct node *left, *right;
};

struct node *root = NULL;

// Create a node
struct node *newNode(char *MaCoPhieu, int day, float GiaMo, float GiaDong) {
  struct node *temp = calloc(1, sizeof(struct node));
  strcpy(temp->MaCoPhieu, MaCoPhieu);
  temp->GiaMo[day - 1] = GiaMo;
  temp->GiaDong[day - 1] = GiaDong;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

// Inorder Traversal
void inorder(struct node *root, int day) {
  if (root != NULL) {
    inorder(root->left, day);
    printf("%s %.3f %.3f\n",root->MaCoPhieu, root->GiaMo[day - 1], root->GiaDong[day - 1]);
    inorder(root->right, day);
  }
}

void inorderAvg(struct node *root, int totalDay){
   if (root != NULL) {
    inorderAvg(root->left, totalDay);
    // printf("%s %f %f\n",root->MaCoPhieu, root->GiaMo[day - 1], root->GiaDong[day - 1]);
    int ngay = 1;
    float avg = 0.0;
    while(ngay <= totalDay){
        avg += (root->GiaDong[ngay - 1] - root->GiaMo[ngay - 1]);
        ngay++;
    }
    avg /= totalDay;
    printf("%s %.3f\n", root->MaCoPhieu, avg);
    inorderAvg(root->right, totalDay);
  }
}

// Insert a node
struct node *insert(struct node *node, int day, char *MaCoPhieu, float GiaMo, float GiaDong) {
  // Return a new node if the tree is empty
  if (node == NULL) {
      return newNode(MaCoPhieu, day, GiaMo, GiaDong);
  } 
  if(strcmp(MaCoPhieu, node->MaCoPhieu) == 0){
    node->GiaDong[day - 1] = GiaDong;
    node->GiaMo[day - 1] = GiaMo;
    return node;
  }
  // Traverse to the right place and insert the node
  if (strcmp(MaCoPhieu, node->MaCoPhieu) < 0)
   node->left = insert(node->left, day, MaCoPhieu, GiaMo, GiaDong);
  else
   node->right = insert(node->right, day, MaCoPhieu, GiaMo, GiaDong);
  
  return node;
}


void readfile(char *filename){
    struct node *root = NULL;
    char MaCoPhieu[11];
    float GiaMo;
    float GiaDong;
    int soLuong;
    FILE *f = fopen(filename,"r");
    if(f == NULL) exit(1);
    fscanf(f,"%d", &soLuong);
    printf("So Luong:%d\n", soLuong);
    int i = 1, ngay = 1;
    while (fscanf(f, "%s %f %f", MaCoPhieu,&GiaMo,&GiaDong) != EOF) {
        root = insert(root, ngay, MaCoPhieu, GiaMo, GiaDong);
        i++;
        if(i > soLuong){
          i = 1;
          ngay++;
        }
    }
    fclose(f);
    ngay = 1;
    while(ngay <= soNgayKhaoSat){
      printf("Ngay thu %d:\n", ngay);
      inorder(root, ngay);
      ngay++;
    }
    printf("Trung binh:\n");
    inorderAvg(root, soNgayKhaoSat);
    
}

void searchMaCP(){
  struct node *temp = root;
  int ngay = 1;
   
   while(ngay <= soNgayKhaoSat){
      printf("Ngay thu %d:\n", ngay);
      inorder(temp, ngay);
      ngay++;
    }

}

// void writeTree(FILE *fp, struct node *root) {
//   if (root == NULL) {
//     return;
//   }

//   writeTree(fp, root->left);
//   fprintf(fp, "%s %s\n", root->eng, root->viet);
//   writeTree(fp, root->right);
// }

// void writeToFile(struct node *root, char *fileName) {
//   FILE *fp;
//   fp = fopen(fileName, "w+");

//   if (fp == NULL) {
//     printf("Could not open file %s", fileName);
//     return;
//   }

//   writeTree(fp, root);
//   fclose(fp);
// }

void freeTree(struct node *root) {
  if (root == NULL) {
    return;
  }

  freeTree(root->left);
  free(root);
  freeTree(root->right);
  
}



int main()
{
    char filename[] = "data.txt";
    int menu = 0;
    int status = 0;
    while(1){
        printf("Menu\n-----------------------------------\n1. Đọc file\n2. Tìm kiếm theo mã chứng khoán\n3. Tìm kiếm những mã chứng khoán có xu hướng tăng\n4. Tìm mã có số ngày tăng lớn nhất\n5. Thoát\nYour choice (1-5, other to quit): ");
        scanf("%d", &menu);
        getchar();
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
                searchMaCP();
                break;

            case 3: 
               
                 
                break;
            
            case 4:
                break;

            case 5:  
                printf("Ban đã thoát chương trình\n");
                exit(0);
 
            default:
                printf("Vui lòng nhập lại\n");
                break;
        }
    }

}