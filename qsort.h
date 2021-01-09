/*
 * Three implementations of QuickSort:
 *
 *    qsort1: standard recursive version.
 *    qsort2: tail recursion removed.
 *    qsort3: iterative version.
 *
 * Author: Quintin Bucheit
 */

#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

// Rearranges the elements of a subarray with specified starting and ending indices in 
// linear time. The first element of the subarray is used as the pivot. Upon completion,
// all values to the left of the pivot are smaller (or equal), and all values to the 
// right are larger. Returns the index of the pivot after partitioning.
int partition(int a[], int lo, int hi) {
	int pivot = a[lo];

	// Index of the larger of the two elements where the indices are currently located.
	int index_hi = hi + 1; 
	
	// Travereses array a from highest to second lowest element where i is the index of the
	// smaller of the two elements where the indices are currently located.
	for (int i = hi; i > lo; i--) {
		
		// If the smaller of the two elements where the indices are currently located
		// is greater than the pivot, decrease the index of the larger element by 1
		// and swap the two.
		if (a[i] > pivot) {
			
			index_hi--; // decrease the index of the larger element by 1
			swap(a[index_hi], a[i]);
		}
	}

	// Swap the pivot with the element to the left of the one lecated at index_hi so that
	// the pivot is now in its correct location.
	swap(a[index_hi - 1], a[lo]); 
	return index_hi - 1; // return location of pivot
}

// Standard recursive implementation of QuickSort.
void qsort1(int a[], int lo, int hi) {
	if (lo < hi) {
		int l = partition(a, lo, hi); // location of the pivot used in this partition
		qsort1(a, lo, l - 1); // recursively quicksort the first half
		qsort1(a, l + 1, hi); // recursively quicksort the second half
	}
}

// QuickSort with tail recursion removed.
void qsort2(int a[], int lo, int hi) {
	while (lo < hi) {
		int l = partition(a, lo, hi); // location of the pivot used in this partition

		// Recurse on the smaller array between the two separated by the pivot l from the
		// previous partition. The larger one will be handled by the next iteration of the
		// loop.
		if ((l - lo) < (hi - l)) {
			// recurse on left side
			qsort2(a, lo, l - 1);

			// Set lo to the lo end of the array on the right side so that after checking
			// the array on the left side the array on the right side is checked in the
			// same way. hi does not need to be changed in this case.
			lo = l + 1; 
		}
		else
		{
			// recurse on right side
			qsort2(a, l + 1, hi);

			// Set hi to the hi end of the array on the left side so that after checking
			// the array on the right side the array on the left side is checked in the
			// same way. lo does not need to be changed in this case.
			hi = l - 1;
		}
	}
}

// Iterative (stack-based) QuickSort.
void qsort3(int a[], int lo, int hi) {
	// Create an instance of the STL stack class and initialize it by pushing lo and hi
	// onto it since they represent the start and end of the initial array.
	stack<int> s;
	s.push(lo);
	s.push(hi);

	while (!s.empty()) {
		// Set hi and lo to the top two integers of the stack and pop those two integers
		// after assigning them to hi and lo. hi is assigned first since stack is last-in
		// first-out.
		hi = s.top();
		s.pop();
		lo = s.top();
		s.pop();
		
		// If lo is less than hi then perform the partition and push the starting and
		// ending indices of the two resulting subarrays onto the stack. If lo is 
		// equal to hi or hi < lo then do nothing since this is the end of the subarray
		// currently being looked at.
		if (lo < hi) {
			
			int l = partition(a, lo, hi); // location of the pivot used in this partition

			// Push the starting and ending indices of the two resulting subarrays onto
			// the stack.
			s.push(lo);
			s.push(l - 1);
			s.push(l + 1);
			s.push(hi);
		}
	}
}
