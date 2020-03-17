/* Author1: Prakhar Rathi 
Roll Number: 1810110169
Author2: Jaskaran Gujral 
Roll Number: 1810110091
*/ 

#include<pthread.h> 
#include<stdio.h> 
#include<stdlib.h> 

/* Structure for passing the data to threads */ 
typedef struct {
    int start; 
    int end; 
} parameters; 

// Size of the array as a global variable to be accessed by all threads 
int SIZE = 10; 
int ord = 0; 

// Defining our global arrays for easier data access
int arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
int sorted_array[10]; 

// Sorting Function which uses an in-built sorting function 
void *sorting_thread(void *params)
{
    /* Extracting data from the parameters */ 
    parameters *p = (parameters *)params; 
    int start = p->start; 
    int end = p->end; 

    int key, j, i;

    /* ASCENDING ORDER SORTING */ 
    if(ord == 0)
    {
        /* Insertion Sort */
        for(i = start+1; i <= end; i++)
        {
            key = arr[i]; 
            j = i - 1; 

            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j]; 
                j = j - 1; 
            }
            arr[j + 1] = key; 
        }
    }

    /* DESCENDING ORDER SORTING */ 
    else if(ord == 1)
    {
        /* Insertion Sort */
        for(i = start+1; i <= end; i++)
        {
            key = arr[i]; 
            j = i - 1; 

            while (j >= 0 && arr[j] < key)
            {
                arr[j + 1] = arr[j]; 
                j = j - 1; 
            }
            arr[j + 1] = key; 
        }
    }
    

    pthread_exit(NULL);
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
void *merging_thread(void *params)
{
    parameters *p = (parameters *)params; 
    int start = p->start; 
    int end = p->end; 

    /* Traverse through both the lists simultaenously and compare the numbers */ 
    if(ord == 0) //ASCENDING SORT
    {
        int l1 = 0, l2 = SIZE/2; 
        for(int i = start; i <= end; i++)
        {
            if(arr[l1] <= arr[l2] && l1 < 5) // 5 can be replaced with SIZE/2
            {
                sorted_array[i] = arr[l1]; 
                l1++; 
            }else
            {
                sorted_array[i] = arr[l2]; 
                l2++; 
            }
        }
    }else if(ord == 1)
    {
        int l1 = 0, l2 = SIZE/2; 
        for(int i = start; i <= end; i++)
        {
            if(arr[l1] >= arr[l2] && l1 < 5) // 5 can be replaced with SIZE/2
            {
                sorted_array[i] = arr[l1]; 
                l1++; 
            }else
            {
                sorted_array[i] = arr[l2]; 
                l2++; 
            }
        }
    }

    pthread_exit(NULL); 
}

// Main Function 
int main()
{
    // Displaying the array before 
    printf("\nArray before being sorted."); 
    display(arr, 10); 

    // Input the order of sorting 
    printf("\nEnter the order of sorting- 0. Ascending 1. Descending: "); 
    scanf("%d", &ord); 

    /* Creating the parameters for the first half for the first sorting thread */ 
    parameters *list1 = (parameters *) malloc(sizeof(parameters));
    list1->start = 0;
    list1->end = 5; 

    /* Creating the parameters for the second half for the second sorting thread */ 
    parameters *list2 = (parameters *) malloc(sizeof(parameters));
    list2->start = 5;
    list2->end = 9;

    /* Create parameters for the merging thread */ 
    parameters *merge_arr = (parameters *) malloc(sizeof(parameters));
    merge_arr->start = list1->start;
    merge_arr->end = list2->end;

    /* Now create the thread passing it data as a parameter */
    pthread_t worker_threads[3]; 

    /* create the two sorting threads and join them */ 
    pthread_create(&worker_threads[0], NULL, sorting_thread, list1); 
    pthread_create(&worker_threads[1], NULL, sorting_thread, list2); 
    
    pthread_join(worker_threads[0], NULL); 
    pthread_join(worker_threads[1], NULL);
    
    /* Create the merging thread which will wait for the first two to end and then join it */ 
    pthread_create(&worker_threads[2], NULL, merging_thread, merge_arr); 
    pthread_join(worker_threads[2], NULL); 

   // Testing the sort function and merging function 
    
    printf("\nAfter sorting the list is:");
    display(arr, 10); 
    
    return(0);
    
}
