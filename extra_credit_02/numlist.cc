#include "numlist.h"

// Partitioning functions
// Serial partition
unsigned int NumList::partition(vector<int>& keys, unsigned int low, 
                                unsigned int high)
{
    // Use the last element as the pivot
    int pivot = keys[high];

    // TODO: Implement the serial partitioning method

    // if value less than pivot is found, send it to the left
    unsigned int i = low;
    for (unsigned int j = low; j < high; j++) {
        if (keys[j] <= pivot) {
            std::swap(keys[i], keys[j]);
            i++;
        }
    }

    // swap the value right after the values less than the pivot, with the pivot
    std::swap(keys[i], keys[high]);
    return i;
}

// Parallel partition
unsigned int NumList:: partition_par(vector<int>& keys, unsigned int low,
                                     unsigned int high)
{
    // Use the last element as the pivot
    int pivot = keys[high];


    // TODO: Implement the parallel partitioning method
    // There should be two #pragmas to parallelize the loop
    // First loop is calculating the lt and gt arrays
    // Second is when the integers are copied to the correct position (i.e.,
    // left or right side of the pivot


    unsigned int n = high - low;

    // indicates if the value is less or greater than the pivot
    vector<int> left(n), right(n);

    #pragma omp parallel for
    for (unsigned int i = 0; i < n; i++) {
        int v = keys[low + i];
        if (v <= pivot) {
            left[i] = 1;
            right[i] = 0;
        } else if (v > pivot) {
            left[i] = 0;
            right[i] = 1;
        }
    }


    // calculate prefix sum
    vector<unsigned int> prefix_left(n), prefix_right(n);
    prefix_left[0] = (unsigned int)left[0];
    prefix_right[0] = (unsigned int)right[0];
    for (unsigned int i = 1; i < n; i++) {
        prefix_left[i] = prefix_left[i - 1] + (unsigned int)left[i];
        prefix_right[i] = prefix_right[i - 1] + (unsigned int)right[i];
    }

    // how many values are less than the pivot
    unsigned int total_less_than = prefix_left[n - 1];



    vector<int> tmp(n + 1);

    // put the pivot in first
    tmp[total_less_than] = pivot;


    // using the prefix sum, we know where the values will go
    #pragma omp parallel for
    for (unsigned int i = 0; i < n; i++) {
        if (left[i] == 1) {
            tmp[prefix_left[i] - 1] = keys[low + i];
        } else if (right[i] == 1) {
            tmp[total_less_than + prefix_right[i]] = keys[low + i];
        }
    }

    // copy to original array
    for (unsigned int i = 0; i <= n; i++) {
        keys[low + i] = tmp[i];
    }

    return low + total_less_than;

}






// Actual qsort that recursively calls itself with particular partitioning
// strategy to sort the list
void NumList::qsort(vector<int>& keys, int low, int high, ImplType opt)
{
    if(low < high) {
        unsigned int pi;
        if(opt == serial) {
            pi = partition(keys, low, high);
        } else {
            pi = partition_par(keys, low, high);
        }
        qsort(keys, low, pi - 1, opt);
        qsort(keys, pi + 1, high, opt);
    }
}

// wrapper for calling qsort
void NumList::my_qsort(ImplType opt)
{
    /* Initiate the quick sort from this function */
    qsort(list, 0, list.size() - 1, opt);
}
// Default constructor
// This should "create" an empty list
NumList::NumList() {
    /* do nothing */
    /* you will have an empty vector */
}
// Contructor
// Pass in a vector and the partitioning strategy to use
NumList::NumList(vector<int> in, ImplType opt) {
    list = in;
    my_qsort(opt);
}
// Destructor
NumList::~NumList() {
    /* do nothing */
    /* vector will be cleaned up automatically by its destructor */
}
// Get the element at index
int NumList::get_elem(unsigned int index)
{
    return list[index];
}
// Print the list
void NumList::print(ostream& os)
{
    for(unsigned int i = 0; i < list.size(); i++) {
        os << i << ":\t" << list[i] << endl;
    }
}
