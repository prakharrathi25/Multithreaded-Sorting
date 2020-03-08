/* Author1: Prakhar Rathi 
Roll Number: 1810110169 
Author2: Jaskaran Gujral 
Roll Number: 1810110091
*/ 

//#include<pthread.h> 
#include<stdio.h> 
#include<stdlib.h> 

void *sorting_thread(void *params); // Thread to perform sorting 
void *merging_thread(void *params); // Thread to merger the sorted threads 

/* Structure for passing the data to threads */ 
typedef struct {
    int start; 
    int end; 
} parameters; 

// Defining our global arrays for easier data access
int arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
int sorted_array[10]; 

// Comparator Function 
int cmpfunc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

// Sorting Function which uses an in-built sorting function 
int sort(int list[], int n)
{
    qsort(list, n, sizeof(int), cmpfunc);
    return 0; 
}

// Display Function 
void display(int list[], int n)
{
    printf("\nThe array is as follows: "); 
    for(int i = 0; i < n; i++)
        printf("%d ", list[i]); 
    printf("\n"); 
}

// Merge Function 
void merge(int arr1[], int arr2[])
{
    for(int ) 
}

// Main Function 
int main()
{
    printf("\nArray before being sorted."); 
    display(arr, 10); 

    sort(arr, 10); 

    printf("\nAfter sorting the list is:");
    display(arr, 10); 
    
    return(0);
}