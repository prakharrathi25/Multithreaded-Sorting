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

// Size of the array as a global variable to be accessed by all threads 
int SIZE = 10; 

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
    
}

// Main Function 
int main()
{

    /* Things to do 

    1. Take an input from user for array size and array input. 
    2. Split the array into two halfs and use pthread_function to create to threads to sort them using the sort() function 
        and the parameters for start and end 
    3. Use the merge function to merge them back into the sorted array list. 

    */ 

    /* Taking the input from the user */ 
    printf("\n Enter the size of the array: "); 
    scanf("%d", &SIZE); 

    int e; 
    if(SIZE % 2 == 0)
        e = SIZE / 2; 
    else
        e = SIZE/2 + 1; 

    // Parameters for list one ( first half )
    parameters *list1 = (parameters *) malloc(sizeof(parameters));
    list1->start = 0;
    list1->end = e ;

    // Parameters for list one ( first half )
    parameters *list2 = (parameters *) malloc(sizeof(parameters));
    list2->start = e ;
    list2->end = SIZE - 1;

    /* Now create the thread passing it data as a parameter */
   // Testing the sort function and 
    printf("\nArray before being sorted."); 
    display(arr, 10); 

    sort(arr, 10); 

    printf("\nAfter sorting the list is:");
    display(arr, 10); 
    
    return(0);


}