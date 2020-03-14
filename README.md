# Multithreaded-Sorting

A list of integers is divided into two smaller lists of equal size. Two separate threads (which we
will term sorting threads) sort each sublist using a sorting algorithm of your choice. The two
sublists are then merged by a third thread – a merging thread – which merges the two sublists
into a single sorted list. Because global data are shared cross all threads, perhaps the easiest way
to set up the data is to create a global array. Each sorting thread will work on one half of this
array. A second global array of the same size as the unsorted integer array will also be
established. The merging thread will then merge the two sublists into this second array. 


## Walk through the code

The following code contains two thread functions. 

* Sorting_thread(): This function uses an insertion sort method to sort the subarray that is passed to it. The function takes three arguments passed t it through a single data structure called parameters. 

    1. *start*: starting index of the subarray
    2. *end*: ending index of the subarray
    3. *order*: 0 for ascending and 1 for descending. 

* Merging_thread(): This function merges the subarrays that have been provided to it. The function takes three arguments passed t it through a single data structure called parameters. 

    1. *start*: starting index of the subarray
    2. *end*: ending index of the subarray
    3. *order*: 0 for ascending and 1 for descending.

Three threads are created: two sorting_threads and one merging_thread. The threads are created using the pthread_create function(). 

The array creation is dynamic and the user inputs the array size as well as the array inputs. The user can also select how they want the function to sort the array: ascending or descending order. 