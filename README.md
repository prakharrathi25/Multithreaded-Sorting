# Multithreaded-Sorting

A list of integers is divided into two smaller lists of equal size. Two separate threads (which we
will term sorting threads) sort each sublist using a sorting algorithm of your choice. The two
sublists are then merged by a third thread – a merging thread – which merges the two sublists
into a single sorted list. Because global data are shared cross all threads, perhaps the easiest way
to set up the data is to create a global array. Each sorting thread will work on one half of this
array. A second global array of the same size as the unsorted integer array will also be
established. The merging thread will then merge the two sublists into this second array. 

Method followed:- 

* Establish a maximum number of threads. Believe me, the last thing you want happening is spinning a thread for each partition. a sequence of 1024 values has 1023 partitions if you crunch the math hard enough. that many threads is not a solution. Establish some boundaries.

* Establish a minimum partition size that you're willing to spin a thread for. This is as important as the first item above. Just like you don't want to be spinning 1023 threads to sort a 1024-slot sequence, you also don't want to be spinning a thread just to sort a sequence that has two items. There is zero benefit and much cost.

* Have a solid merge algorithm. There are many efficient ways to do it, but do something simple and enhance it later. Right now we're just interested in getting the general threading down right. There is always time to enhance this with a fancy merge algorithm (like in-place, which believe me is harder than it sounds).

Having the above the idea is this:

* The merge sort algorithm will have three parameters: a starting pointer, a length, and a thread-depth. For our purposes the thread depth will be N in a situation where we are using at-most 2N-1 threads. (more on that later, but trust me, it makes it easier to do the math this way).

* If the thread depth has reached zero OR the sequence length is below a minimum threshold *we set), do not setup and run a new thread. Just recurse into our function again.

* Otherwise, split the partition. Setup a structure that holds a partition definition (which for us will be a starting point and a length as well as the thread depth which will be N/2), launch a thread with that parameter block, then do NOT launch another thread. instead use the current thread to recurse into merge_sort_mt() for the "other" half.

* Once the current thread returns from its recursion is must wait on the other thread via a join. once that is done both partitions will be done and they can be merged using your trivial merge algorithm.
