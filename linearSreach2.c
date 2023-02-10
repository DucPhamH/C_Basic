#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void linearSearch(char *result, int size, char *key){
    int i;
    int k = 0;
    int x = 0;
    int y = 0;
    for (i = 0; i < strlen(result) - 1; i++){
      if ((result[i] == key[k]) && (i < strlen(result)-1)){
         x = i + 1;
         y = k + 1;
         while(y < size){
            if((result[x] == key[y])){
              //printf("ok\n");
              x++;
              y++;
            }else{
                break;
            }  
        }
        // printf("%d\n", y);
            if(y == size){
              printf("%s\n", result);
            }else printf("Key element not found\n");
        //printf("Key element found at i %d\n", i); 
       }else
        printf("Key element not found\n");
    }
}

void readFile(char *filename, char *key, int size){

    FILE *f = fopen(filename, "r");
    if(f == NULL) exit(1);
    char result[30];
    while(fgets(result, 30, f) != NULL){
         linearSearch(result, size, key);
        //  printf("%s", result);
    }
    fclose(f);
}


int main(){
    char filename[] = "vanban.txt";
    char key[30];
    printf("Nhap key can tim: ");
    scanf("%s", key);
    int size = strlen(key);
    //printf("%c", key[0]);
    readFile(filename, key, size);
    return 0;

}