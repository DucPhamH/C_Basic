#include<stdio.h>
#include<string.h>
#include<stdlib.h>




int main()
{
   
    int menu = 0;
    
    while(1){
        printf("Menu\n-----------------------------------\n1. \n2. \n3. \n4. Thoat\nYour choice (1-4, other to quit): ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
               
                break;

            case 2:
                
                break;

            case 3: 
               
                 
                break;

            case 4:  
                printf("Ban đã thoát chương trình\n");
                exit(0);
 
            default:
                printf("Vui lòng nhập lại\n");
                break;
        }
    }

}