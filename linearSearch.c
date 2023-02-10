#include<stdio.h>


void linearSearch(int arr[], int size, int key){
    int index;
    for (index = 0; index < size; index++){
      if ((arr[index] == key)&&(index < size)) // comparing each element with the key element
        printf("Key element found at index %d\n", index); // printing the index if key found
     else
        printf("Key element not found");
    }
     // cursor out of the loop when a key element found

    // if (index < size) // condition to check whether previous loop partially traversed or not
    //   printf("Key element found at index %d", index); // printing the index if key found
    // else
    //   printf("Key element not found");
}

int main() {
  // declaration of the array and other variables
  int arr[20], size, key, i, index;
  printf("Number of elements in the list: ");
  scanf("%d", &size);

  printf("Enter elements of the list: ");
  // loop for the input of elements from 0 to number of elements-1
  for (i = 0; i < size; i++)
    scanf("%d", &arr[i]);

  printf("Enter the element to search ie. key element: ");
  scanf("%d", &key);

  linearSearch(arr, size, key);

  // loop for traversing the array from 0 to the number of elements-1
 

  return 0;
}
