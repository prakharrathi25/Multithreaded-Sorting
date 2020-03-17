/* Author1: Prakhar Rathi 
Roll Number: 1810110169 
Author2: Jaskaran Gujral 
Roll Number: 1810110091
*/ 

// Required header files
#include<pthread.h> 
#include<stdio.h> 
#include<stdlib.h> 

// Structure for passing the data to threads
typedef struct {
    int start;          // Specifies the starting index value
    int end;            // Specifies the ending index value
    int *arr;           // Points to the initial array
    int *sorted_array;  // Points towards the array to be sorted
} parameters;

// Used to specify ascending/descending order
int ord;

// Size of the array
int SIZE;

// Sorting Function 
void *sorting_thread(void *params)
{
    // Extracting data from the parameters
    parameters *p = (parameters *)params; 
    int start = p->start; 
    int end = p->end;
    int *arr = p->arr;

    int key, j, i;

    // ASCENDING ORDER SORTING
    if(ord == 0)
    {
        // Insertion Sort
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

    // DESCENDING ORDER SORTING
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
    int *arr = p->arr;
    int *sorted_array = p->sorted_array;

    // Traverse through both the lists simultaenously and compare the numbers
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
    }else if(ord == 1) // DESCENDING SORT
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
    // User inputs the size of the array
    printf("\nEnter the size of the array: ");
    scanf("%d", &SIZE);

    int arr[SIZE]; // Initial array
    int sorted_array[SIZE]; // Array in which sorted values will be stored

    // User inputs the values for the initial array
    printf("\n");
    for(int i = 0; i < SIZE; ++i)
    {
        printf("Enter the value at the %d index: ", i);
        scanf("%d", &arr[i]);
    }

    // Displaying the array before 
    printf("\nArray before being sorted."); 
    display(arr, SIZE); 

    printf("\nEnter 0 for ascending order.\n"
    "Enter 1 for descending order: ");
    scanf("%d", &ord);

    // Creating the parameters for the first half for the first sorting thread
    parameters *list1 = (parameters *) malloc(sizeof(parameters));
    list1->start = 0;
    list1->end = SIZE/2;
    list1->arr = arr;
    list1->sorted_array = sorted_array;

    // Creating the parameters for the second half for the second sorting thread
    parameters *list2 = (parameters *) malloc(sizeof(parameters));
    list2->start = SIZE/2;
    list2->end = SIZE - 1;
    list2->arr = arr;
    list2->sorted_array = sorted_array;

    // Creating the parameters for the merging thread
    parameters *merge_arr = (parameters *) malloc(sizeof(parameters));
    merge_arr->start = list1->start;
    merge_arr->end = list2->end;
    merge_arr->arr = arr;
    merge_arr->sorted_array = sorted_array;

    // Now create the thread passing the data as a parameter
    pthread_t worker_threads[3]; 

    // Create the two sorting threads and join them
    pthread_create(&worker_threads[0], NULL, sorting_thread, list1); 
    pthread_create(&worker_threads[1], NULL, sorting_thread, list2); 
    
    pthread_join(worker_threads[0], NULL); 
    pthread_join(worker_threads[1], NULL);
    
    // Create the merging thread which will wait for the first two to end and then join it
    pthread_create(&worker_threads[2], NULL, merging_thread, merge_arr); 
    pthread_join(worker_threads[2], NULL); 

   // Display the sorted array
    printf("\nAfter sorting the list is:");
    display(arr, SIZE);
    printf("\n");
    
    return(0);
    
}