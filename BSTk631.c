// Binary Search Tree operations in C

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node {
  char eng[40];
  char viet[40];
  struct node *left, *right;
};

// Create a node
struct node *newNode(char *eng, char *viet) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  strcpy(temp->eng, eng);
  strcpy(temp->viet, viet);
  temp->left = temp->right = NULL;
  return temp;
}

// Inorder Traversal
void inorder(struct node *root) {
  if (root != NULL) {
    // Traverse left
    //printf("%s %s\n", root->eng, root->viet);
    inorder(root->left);

    // Traverse root
    printf("%s %s\n", root->eng, root->viet);

    // Traverse right
    inorder(root->right);
  }
}

// Insert a node
struct node *insert(struct node *node, char *eng, char *viet) {
  // Return a new node if the tree is empty
  if (node == NULL) return newNode(eng, viet);

  // Traverse to the right place and insert the node
  if (strcmp(eng, node->eng) < 0)
    node->left = insert(node->left, eng, viet);
  else
    node->right = insert(node->right, eng, viet);

  return node;
}

struct node* search(struct node *root, char *eng) {
  if (root == NULL || (strcmp(eng, root->eng) == 0)) {
    return root;
  }

  if (strcmp(eng, root->eng) < 0) {
    return search(root->left, eng);
  }

  return search(root->right, eng);
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, char *eng) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the node to be deleted
  if (strcmp(eng, root->eng) < 0)
    root->left = deleteNode(root->left, eng);
  else if (strcmp(eng, root->eng) > 0)
    root->right = deleteNode(root->right, eng);

  else {
    // If the node is with only one child or no child
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
   // root->key = temp->key;
    strcpy(root->eng, temp->eng);
    strcpy(root->viet, temp->viet);

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->eng);
  }
  return root;
}

void readfile(char *filename, struct node *root){
    char eng[40];
    char viet[40];
    FILE *f = fopen(filename,"r");
    if(f == NULL) exit(1);
    while (fscanf(f,"%s %s\n",eng, viet) != EOF) {
        printf("%s %s\n", eng, viet);
        root = insert(root, eng, viet);
        
    }
    fclose(f);
}

void writeTree(FILE *fp, struct node *root) {
  if (root == NULL) {
    return;
  }

  writeTree(fp, root->left);
  fprintf(fp, "%s %s\n", root->eng, root->viet);
  writeTree(fp, root->right);
}

void writeToFile(struct node *root, char *fileName) {
  FILE *fp;
  fp = fopen(fileName, "w+");

  if (fp == NULL) {
    printf("Could not open file %s", fileName);
    return;
  }

  writeTree(fp, root);
  fclose(fp);
}

void freeTree(struct node *root) {
  if (root == NULL) {
    return;
  }

  freeTree(root->left);
  free(root);
  freeTree(root->right);
  
}




// Driver code
int main() {
    struct node *root = NULL;
    struct node *result = NULL;
    char eng[40];
    char viet[40];
    char vietchange[40];
    
    char eng2[40];
    char viet2[40];
    char filename[] = "dictionary.txt";
    //readfile(filename, root);
    FILE *f = fopen(filename,"r");
    if(f == NULL) exit(1);
    while (fscanf(f,"%s %s\n",eng2, viet2) != EOF) {
       printf("%s %s\n", eng2, viet2);
        root = insert(root, eng2, viet2);
        
    }
    fclose(f);

    int menu = 0;
    
    while(1){
        printf("\nMenu\n-----------------------------------\n1. In các node của cây\n2. Nhập thêm khóa từ\n3. Tìm kiếm từ\n4. Xóa từ\n5. Ghi lại file\n6. Giải phóng cây\n7. Thoát\n Your choice (1-7, other to quit): ");
        scanf("%d", &menu);
        switch(menu){
           
            case 1:
                inorder(root);
                break;

            case 2: 
                printf("Nhap tu tieng anh: ");
                fflush(stdin);
                scanf("%s", eng);
                result = search(root, eng);
                if(result){
                  printf("Nhap tu can thay doi ");
                  fflush(stdin);
                  scanf("%s", vietchange);
                  strcpy(result->viet, vietchange);
                  break;
                }else{
                  printf("Nhap tu phien dich: ");
                  fflush(stdin);
                  scanf("%s", viet);
                  root = insert(root, eng, viet);
                  break;
                }
            
            case 3: 
                 printf("Nhap tu tieng anh: ");
                 fflush(stdin);
                 scanf("%s", eng);
                 result = search(root, eng);
                 if(result){
                  printf("%s %s\n", result->eng,result->viet);
                }else {
                  printf("Khong tim thay tu khoa");
                }
                break;
            
            case 4:
                printf("Nhap tu tieng anh: ");
                fflush(stdin);
                scanf("%s", eng);
                result = deleteNode(root, eng);
                if(result){
                  printf("Xoa thanh cong");
                }else {
                  printf("Khong tim thay tu khoa");
                }
                break;

            case 5:
                writeToFile(root, filename);
                break;

            case 6:  
               freeTree(root);
               break;
            
             case 7:
               printf("Ban đã thoát chương trình\n");
               exit(0);
               break;
 
            default:
                printf("Vui lòng nhập lại\n");
                break;
        }
    }
     
    return 0;
}