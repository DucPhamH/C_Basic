#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct sinhVien{
    char mssv[10];
    char hoTen[30];
    float diem; 
};
typedef struct sinhVien SV;

void writeFile(char *filename, char *finish){
    struct sinhVien member;
    FILE *f= fopen(filename, "a+");
    if(f == NULL) exit(1);
        printf("Nhap MSSV: ");
        fflush(stdin);
        scanf("%s", member.mssv);

        printf("Nhap ho ten: ");
        fflush(stdin);
        scanf("%s", member.hoTen);
        if(strcmp(member.hoTen, finish) == 0){
            printf("Bạn đã dừng quá trình nhập!\n");
             return;
        }
               
        printf("Nhap diem: ");
        fflush(stdin);
        scanf("%f", &member.diem);   
        if(member.diem < 0 || member.diem > 10){
            printf("Bạn dã nhap sai!\n");
            return;
        }

        fprintf(f,"\n%s %s %f",member.mssv, member.hoTen, member.diem);
        fclose(f);
}

int binarySearch(SV arr[], int l, int r, char *x)
{   
    for(int i = 0; i<r+1; i++){
         printf("%s %s %f\n",arr[i].mssv,arr[i].hoTen,arr[i].diem);
    }
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle
		// itself
		if (strcmp(arr[mid].mssv,x) == 0)
			return mid;

		// If element is smaller than mid, then
		// it can only be present in left subarray
		if (strcmp(arr[mid].mssv,x) > 0)
			return binarySearch(arr, l, mid - 1, x);

		// Else the element can only be present
		// in right subarray
		return binarySearch(arr, mid + 1, r, x);
	}

	// We reach here when element is not
	// present in array
	return -1;
}

void search( SV arr[], int size )
{
	int low, high, mid;
    char searchkey[10];

    for(int i = 0; i<size; i++){
         printf("%s %s %f\n",arr[i].mssv,arr[i].hoTen,arr[i].diem);
    }

	printf("Enter a student number to search: \n");
    fflush(stdin);
	scanf("%s", searchkey);

       low = 0;
       high = size - 1;
       while (low <= high) {
           mid = (low+high)/2;
           if (strcmp(searchkey,arr[mid].mssv) < 0)
               high = mid + 1;
           else if (strcmp(searchkey,arr[mid].mssv) > 0)
               low = mid + 1;
           else if (strcmp(searchkey,arr[mid].mssv) == 0) {   /* found match */
              printf(" %s %f\n", arr[mid].hoTen, arr[mid].diem);
              break;
           }else
			   printf("Search Key not found\n");
       }
        
   

}


int main() {
    SV members[100];
    int choice, i,j, result;
    float diem; 
    int n = 0;
    int size = 0;
    char mssv[10], tempmssv[10], ysearch[10];
    char hoTen[30], temphoten[30];
    char filename[] = "sv.txt";
    char finish[] = "###";
    FILE *f;
   

    printf("\nHay chon menu: \n");
    while (1) {
        printf("1. Nhap thong tin sinh vien\n2. Doc du lieu file ra mot mang\n3. Sap xep mang theo mssv\n4. Tim kiem mssv\n5. Exit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            writeFile(filename, finish);
            break;
        case 2:
            f = fopen(filename,"r");
            if(f == NULL) exit(1);
            while (fscanf(f,"%s %s %f\n",mssv, hoTen, &diem) != EOF) {
                //printf("%s %s %f\n", mssv, hoTen, diem);
                strcpy(members[n].mssv, mssv);
                strcpy(members[n].hoTen, hoTen);
                members[n].diem= diem;
                n++;
            }
            for(i = 0; i<n; i++){
                printf("%s %s %f\n", members[i].mssv, members[i].hoTen, members[i].diem);
            }
            size = n;
            n = 0;
            fclose(f);
            break;
        case 3:
             printf("%d\n", size);
             for (int i = 0; i < size; i++) {
                for (int j = i + 1; j < size; j++) {
                    if (members[i].diem < members[j].diem) {
                        
                        float tempdiem = members[i].diem;
                        members[i].diem = members[j].diem;
                        members[j].diem = tempdiem;
                        
                        strcpy(tempmssv, members[i].mssv);
                        strcpy(members[i].mssv, members[j].mssv);
                        strcpy(members[j].mssv, tempmssv);

                        strcpy(temphoten, members[i].hoTen);
                        strcpy(members[i].hoTen, members[j].hoTen);
                        strcpy(members[j].hoTen, temphoten);
                    }
                }
            }
             for (int i = 0; i < size; i++) {
               printf("%s %s %f\n", members[i].mssv, members[i].hoTen, members[i].diem);
             }
            break;
        case 4:
            printf("Nhap MSSV: ");
            fflush(stdin);
            scanf("%s", ysearch);
            int result = binarySearch(members, 0, size-1, ysearch);
            printf("%d\n", result);
            // search(members, size);
            break;
         case 5:
            exit(0);
            break;
        default:
            printf("\nWrong Choice\n");
        }
    }
}
