#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct account{
    char username[30];
    char password[30];
    int status;
    int count;
    struct account *next;
};
struct account *head = NULL;
struct account *last = NULL;

struct account* createAcc(char *username, char *password){
    struct account *link = (struct account*)malloc(sizeof(struct account));
    strcpy(link->username, username);
    strcpy(link->password, password);
    link->status = 2;
    link->count = 0;
    return link;
}

void readfile(char *filename){
    char username[30], password[30];
    int status;
    FILE *f = fopen(filename,"r");
    if(f == NULL) exit(1);
    while (fscanf(f,"%s %s %d\n",username, password, &status) != EOF){ 
        //printf("%s, %s, %d\n", username, password, status);
        insertHead(username, password, status);
    }
    fclose(f);
}

struct account* searchName(char *username){
    struct account *temp = head;
    while(temp != NULL){
        if(strcmp(temp->username,username) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}


struct account* searchAcc(char *username, char *password){
    struct account *temp = head;
    while(temp != NULL){
        if((strcmp(temp->username,username) == 0) && (strcmp(temp->password,password) == 0) && (temp->status == 2)) return temp;
        temp = temp->next;
    }
    return NULL;
}

void signIn(int *loginStatus, char *username, char *filename){
    char password[30];
    int error = 0;
    struct account *temp = searchName(username);

    if(temp != NULL){
    switch(temp->status){

        case 0:
        printf("Account is blocked\n\n");
        *loginStatus = 0;
        return;

        case 1:
        printf("Password: ");
        scanf("%s",password);

        while(strcmp(password, temp->password) != 0){
            error++;
            if(error == 3) {
                temp->status = 0;
                rewriteFile(filename);
                *loginStatus = 0;
                printf("Password is incorrect. Account is blocked\n\n");
                return;
            }
            printf("Password is incorrect\nPassword: ");
            scanf("%s",password);
        }
            printf("Hello %s\n\n",username);
            *loginStatus = 1;
            return;

        case 2:
         printf("Account is not active\n\n");
        *loginStatus = 0;
         return;
        }
    } 
    printf("Cannot find account\n\n");
    *loginStatus = 0;
}


void changePass(char *username, char *newPass, char *filename){
    char password[30];
    
    struct account *temp = searchName(username);

    if(temp != NULL){
    switch(temp->status){

        case 0:
        printf("Account is blocked\n\n");
        return;

        case 1:
        printf("Password: ");
        scanf("%s",password);
        printf("New password: ");
        scanf("%s",newPass);

        while(strcmp(password, temp->password) != 0){
            printf("Password is incorrect\nPassword: ");
            scanf("%s",password);
             printf("New password: ");
             scanf("%s",newPass);
        }
        if(strcmp(temp->password, newPass) != 0){
            strcpy(temp->password, newPass);
            rewriteFile(filename);
            printf("Password is changed\n\n");
        } else printf("Pass and new Pass are the same\n");

        return;   

        case 2:
         printf("Account is not active\n\n");
         return;
        }
    
} 
    printf("Cannot find account\n\n");
   
}

void activeAccount(char *filename, char *trueCode){
    char username[30],password[30], code[30];
    printf("Username: ");
    scanf("%s",username);

    printf("Password: ");
    scanf("%s",password);

    printf("Code: ");
    scanf("%s",code);

    struct account *temp = searchAcc(username, password);
    if(searchAcc(username, password) != NULL) {

         if(strcmp(code, trueCode) != 0){
            temp->count++;
            if(temp->count == 5){
                temp->status = 0;
                rewriteFile(filename);
                printf("Activation code is incorrect.Account is blocked\n");
                temp->count = 0;
                return;
            }printf("Account is not activated\n");
            return;
         } 
         
            temp->status = 1;
            rewriteFile(filename);
            printf("Account is activated\n");
            temp->count = 0;
            
    }else printf("Can't find account or account is actived or blocked\n");

}

void insertHead(char *username, char *password, int status)
{
   struct account *link = createAcc(username, password);
   link->status = status;
   link->next = head;
   head = link;
}



void rewriteFile(char *filename){
    FILE *f = fopen(filename, "w+");
    if(f == NULL) exit(1);
    struct account *temp = head;
    while(temp != NULL){
        if(temp->next != NULL) fprintf(f,"%s %s %d\n\n",temp->username, temp->password, temp->status);
        else fprintf(f,"%s %s %d",temp->username, temp->password, temp->status);
        temp = temp->next;
    }
    fclose(f);
}


void registerAccount(char *filename){
    char username[30],password[30];
    printf("Username: ");
    scanf("%s",username);

    if(searchName(username) != NULL) {
        printf("Account existed\n\n");
        return;
    }

    printf("Password: ");
    scanf("%s",password);

    insertHead(username, password, 2);
    rewriteFile(filename);
    printf("Successful registration. Activation required.\n\n");
}

void search(){
    char username[30];
    printf("Username: ");
    scanf("%s",username);
    struct account *temp = searchName(username);
    
    if(temp != NULL){
         switch(temp->status){
             case 0:
                printf("Account is blocked\n\n");
                return;

             case 1:
                printf("Account is active\n\n");
                return;
             case 2:
                printf("Account is not active\n\n");
                return;
         }
    }
    printf("Cannot find account\n\n");
    
}

int main()
{
    char username[30], filename[] = "account.txt", trueCode[] = "20194516", userLogOut[30];
    char password[30], newPass[30];
    int menu,loginStatus = 0;
    readfile(filename);
    while(1){
        printf("USER MANAGEMENT PROGRAM\n-----------------------------------\n1. Register\n2. Activate\n3. Sign in\n4. Search\n5. Change password\n6. Sign out\nYour choice (1-6, other to quit): ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
                printf("-----------------------------------\n");
                printf("\033[0;31m"); 
                loginStatus = 0;
                registerAccount(filename);
                printf("\033[0m");
                printf("-----------------------------------\n");
                break;

            case 2:
                printf("-----------------------------------\n");
                printf("\033[0;31m"); 
                loginStatus = 0;
                activeAccount(filename, trueCode);
                printf("\033[0m");
                printf("-----------------------------------\n");
                break;

            case 3: 
                printf("-----------------------------------\n");
                printf("\033[0;31m"); 
                loginStatus = 0;
                printf("Username: ");
                scanf("%s",username);
                signIn(&loginStatus, username, filename);
                printf("\033[0m");
                printf("-----------------------------------\n");    
                break;

            case 4:   
                printf("-----------------------------------\n");
                printf("\033[0;31m"); 
                if(loginStatus == 0) {
                    printf("Account is not logged in\n\n");
                    printf("\033[0m");
                    printf("-----------------------------------\n");
                    break;
                }
                search();
                printf("\033[0m");
                printf("-----------------------------------\n");
                break;

            case 5:
                printf("-----------------------------------\n");
                printf("\033[0;31m"); 
                if(loginStatus == 0) {
                    printf("Account is not logged in\n\n");
                    printf("\033[0m");
                    printf("-----------------------------------\n");
                    break;
                }
                printf("Username: ");
                scanf("%s",username);
                changePass(username, newPass, filename);
                printf("\033[0m");
                printf("-----------------------------------\n");    
                break;
                

            case 6:
                printf("-----------------------------------\n");
                printf("\033[0;31m"); 
                printf("Username: ");
                scanf("%s",userLogOut);
                
                if(loginStatus == 0) {
                    printf("Account is not logged in\n\n");
                    printf("\033[0m");
                    printf("-----------------------------------\n");
                    break;
                }

                if (strcmp(username, userLogOut) == 0){
                    loginStatus = 0;
                     printf("Goodbye %s\n", username);  
                }else printf("Cannot find account\n");
               
                printf("\033[0m");
                printf("-----------------------------------\n");    
                break;
                

            default:
                exit(0);
        }
    }

}