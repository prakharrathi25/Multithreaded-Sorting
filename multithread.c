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
    int *arr;
    int *sorted_array;
    int SIZE;
} parameters;

// Sorting Function which uses an in-built sorting function 
void *sorting_thread(void *params)
{
    /* Extracting data from the parameters */ 
    parameters *p = (parameters *)params; 
    int start = p->start; 
    int end = p->end;
    int *arr = p->arr; 

    int key, j, i;

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
    int *arr = p->arr;
    int *sorted_array = p->sorted_array;
    int SIZE = p->SIZE;

    /* Traverse through both the lists simultaenously and compare the numbers */ 
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

    pthread_exit(NULL); 
}

// Main Function 
int main()
{
    //User inputted size
    int SIZE;
    printf("Enter the size of the array: ");
    scanf("%d", &SIZE);

    int arr[SIZE];
    int sorted_array[SIZE];

    //User inputted values for the global array
    for(int i = 0; i < SIZE; ++i)
    {
        printf("Enter the value at the %d index: ", i);
        scanf("%d", &arr[i]);
    }

    // Displaying the array before 
    printf("\nArray before being sorted."); 
    display(arr, SIZE); 

    /* Things to do 

    1. Take an input from user for array size and array input. 
    2. Split the array into two halfs and use pthread_function to create to threads to sort them using the sort() function 
        and the parameters for start and end 
    3. Use the merge function to merge them back into the sorted array list. 

    */ 

    /* Creating the parameters for the first half for the first sorting thread */ 
    parameters *list1 = (parameters *) malloc(sizeof(parameters));
    list1->start = 0;
    list1->end = SIZE/2;
    list1->arr = arr;
    list1->sorted_array = sorted_array;
    list1->SIZE = SIZE;

    /* Creating the parameters for the second half for the second sorting thread */ 
    parameters *list2 = (parameters *) malloc(sizeof(parameters));
    list2->start = SIZE/2;
    list2->end = SIZE - 1;
    list2->arr = arr;
    list2->sorted_array = sorted_array;
    list2->SIZE = SIZE;

    /* Create parameters for the merging thread */ 
    parameters *merge_arr = (parameters *) malloc(sizeof(parameters));
    merge_arr->start = list1->start;
    merge_arr->end = list2->end;
    merge_arr->arr = arr;
    merge_arr->sorted_array = sorted_array;
    merge_arr->SIZE = SIZE;

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
    display(arr, SIZE); 
    
    return(0);
    
}