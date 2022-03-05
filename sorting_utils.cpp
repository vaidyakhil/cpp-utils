#include <iostream>
#include<bits/stdc++.h>

using namespace std;

class SortingUtils {

	/*
	** bucket sort, counting sort, radix sort, these all can work in O(n) with specific dataset but SPACE COMPLEXITY INCREASES.
	** for bucket sort: 
	    if almost uniformally distributed data is present.
	** for counting sort: 
	    if range of data O(n).
	** for  radix sort:
	    if ~ n > logb(n); 
	*/

	private: 
		void static swap(vector<int>& arr, int i, int ind) {
			int temp= arr[i];
			arr[i]= arr[ind];
			arr[ind]= temp;
		}

		bool static isSortRequired(vector<int>& arr) {
			return arr.size() >= 2;
		}

		int static placeInSorted(vector<int> & arr, int beg, int end) {
		    int count= 0; 
		    // not making it (beg+end)/2 as that leads to 
		    // movement of the piv element before completing
		    // counting of smaller elements
		    int piv= end;

		    for(int i= beg; i<end; i++)
		    {
		        if(arr[i] < arr[piv])
		        {
		            swap(arr, i, beg+count);
		            count++;
		        }
		    }
		    swap(arr, piv, beg + count);
		    return beg + count;
		}

		void static quickSortUtil(vector<int> & arr, int beg, int end) {
		    if(beg < end)
		    {
		        int piv= placeInSorted(arr, beg, end);
		        quickSortUtil(arr, beg, piv-1);
		        quickSortUtil(arr, piv+1, end);
		        return;
		    }
		    return;
		}

		void static mergeSortedArrays(vector<int> & arr, int beg1, int beg2, int end) {
			int n = end-beg1+1;
			vector<int> tempArr = vector<int>(n);
			int start1 = beg1;
			int start2 = beg2;
			int cur = 0;

			while (start1 < beg2 && start2 <= end) {
				if (arr[start1] < arr[start2]) {
					tempArr[cur] = arr[start1];
					start1++;
				} else {
					tempArr[cur] = arr[start2];
					start2++;
				}
				cur++;
			}

			while (start1 < beg2) {
				tempArr[cur] = arr[start1];
				start1++;
				cur++;
			}

			while (start2 <= end) {
				tempArr[cur] = arr[start2];
				start2++;
				cur++;
			}
			
            cur = 0;
			while (cur  < n) {
				arr[beg1 + cur] = tempArr[cur];
				cur++;
			}
			return;
		}

		void static mergeSortUtil(vector<int> & arr, int beg, int end) {
		    if (beg >= end) {
		    	return;
		    }

		    int mid = (beg + end)/2;
		    mergeSortUtil(arr, beg, mid);
		    mergeSortUtil(arr, mid+1, end);
		    mergeSortedArrays(arr, beg, mid+1, end);
		    return;
		}

		/*
		**	Heap Sort Utils
		*/

		/*
		**	To be called on heap with 2*i, 2*i+1 heapified children
		**	log(n), if total n elements smaller or equal to arr[i]
		*/
		static void maxHeapify (vector<int>& arr, int i, int N) {
			// left child
		    int left = 2*i;
		    
		    //right child
		    int right = 2*i +1;

	    	// evaluate which one is largest and swap it with i
		    int largest = i;
		    if(left <= N and arr[left] > arr[i] ) {
	    		largest = left;
		    }
		          
		    if(right <= N and arr[right] > arr[largest] ) {
	    		largest = right;
		    }

		    if(largest != i )
		    {
		        swap (arr, i , largest);

		        // then recursively heapify the correct child
		        maxHeapify (arr, largest, N);
		    } 
		 }


		/*
		**	The total operation takes O(n) time. 
		**	maxHeapify takes O(h) time for nodes at same level (height), 
		**	it is called at various nodes 
		**	which have different n -> r for almost n/2 times.
		** 	Will become a sum of A.G.P, N *( 1 - 1/N) ~~ O(N)
		*/
		static void buildMaxHeap (vector<int>& arr) {
			//number of elements
			int N= arr.size() - 1; 

		    for(int i = N/2; i>0 ; i-- ) {
		        maxHeapify (arr, i, N) ;
		    }
		}


	public: 
		void static selectionSort(vector<int>& arr) {
			int n= arr.size();
			if(!isSortRequired(arr)) {
				return;
			}

			for (int i=0; i<n; i++) {
				int ind=i;
				for (int j=i+1; j<n; j++) {
					if (arr[j]<arr[ind]) {
						ind = j;
					}
				}
				swap(arr, i, ind);
			}
			return;
		}

		void static bubbleSort(vector<int>& arr) {
			int n= arr.size();
			if(!isSortRequired(arr)) {
				return;
			}

			for (int i=0; i<n; i++) {
				bool isSorted = true;
				for (int j=0; j<n-1-i; j++) {
					if (arr[j] > arr[j+1]) {
						swap(arr, j, j+1);
						isSorted =  false;
					}
				}
				if (isSorted) {
					break;
				}
			}
			return;
		}

		void static insertionSort(vector<int>& arr) {
			int n= arr.size();
			if(!isSortRequired(arr)) {
				return;
			}

			for (int i=1; i<n; i++) {
				for (int j=i-1; j>=0; j--) {
					if (arr[j+1] < arr[j]) {
						swap(arr, j, j+1);
					} else {
						break;
					}
				}
			}
			return;
		}

		// worst: O(n^2) -> when arr already sorted in either inc/dec order
		// best: O(nlog(n)) -> when piv calculates new pos towards center
		void static quickSort(vector<int>& arr) {
			int n= arr.size();
			if(!isSortRequired(arr)) {
				return;
			}
			quickSortUtil(arr, 0, n-1);
			return;
		}

		void static mergeSort(vector<int>& arr) {
			int n= arr.size();
			if(!isSortRequired(arr)) {
				return;
			}

			mergeSortUtil(arr, 0, n-1);
			return;		
		}


		/*
		**	best, worst and average time complexities all are O(nlog(n))
		*/
		static void heapSort(vector<int>& arr) {
		    int N = arr.size();
		    vector<int> aux(N+1);

		    // copying into 1 indexed aux array
		    for (int i=0; i<N; i++) {
		    	aux[i+1] = arr[i];
		    }

			// first heapify given array. O(n)
		    buildMaxHeap(aux);


		    for (int i = N; i>=2 ; i-- ) {
		    	// max element will be at top take it to last 
		    	// reduce size of heap
		        swap(aux, 1, i);

				// note that heapify is called and not buid_heap
				// because childeren are already heap,
				// just place parent at correct place.
		        maxHeapify(aux, 1, i-1);
		    }
		    
		    // copying back to original array
		    for (int i=0; i<N; i++) {
		    	arr[i] = aux[i+1];
		    }
		    return;
		}
};

int main() {
    // vector<int> arr = vector<int>({1,23,4,4,1,3,2,3,1,5,2,3,4,66,3});
    vector<int> arr = vector<int>({9,7,3,4,2,1,6,5,4,3,1,45,7,23,32,6,3});
    // vector<int> arr = vector<int>({1,2,3,4});
    // vector<int> arr = vector<int>({9,8,7,4,3,2,1,0});
    
    SortingUtils::heapSort(arr);
    std::cout << "Hello world!" << endl;
    for (int i=0; i<arr.size(); i++) {
        std::cout << arr[i] << "\t";    
    }
    std::cout << endl << "Hello world!";

    return 0;
}