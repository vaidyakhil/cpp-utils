class HeapUtils {
	/*
	**	Heap data structure:
	**	Parent has strict order with children, children have no strict order among them
	**	One implementation of heap involves use of array,
	**	parent is stored at i, 2 childre are at 2*i, 2*i+1
	**	so there will be n/2 leaf nodes (n/2 non leaf nodes)
	*/

	/*
	** 	Implementation here is for max heap, 
	**	similar can be done for min heap
	*/

private:

	/*
	**	To be called on heap with 2*i, 2*i+1 heapified children
	**	log(n), if total n elements smaller or equal to arr[i]
	*/
	void maxHeapify (vector<int>& arr, int i, int N) {
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
	        swap (arr[i] , arr[largest]);

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
	void buildMaxHeap (vector<int>& arr) {
		//number of elements
		int N= arr.size() - 1; 

	    for(int i = N/2; i>0 ; i-- ) {
	        maxHeapify (arr, i) ;
	    }
	}

public:
	/*
	**	static because this has nothing to do 
	**	with the instance of this class
	**	it is a heap API kept in the heap class	
	*/
	static void heapSort(vector<int>& arr) {
	    int N = arr.size();
	    vector<int> aux(n+1);

	    // copying into 1 indexed aux array
	    for (int i=0; i<N; i++) {
	    	aux[i+1] = arr[i];
	    }

		// first heapify given array. O(n)
	    buildMaxHeap(aux);


	    for (int i = N; i>=2 ; i-- ) {
	    	// max element will be at top take it to last 
	    	// reduce size of heap
	        swap(aux[1], aux[i]);

			// note that heapify is called and not buid_heap
			// because childeren are already heap,
			// just place parent at correct place.
	        maxHeapify(aux, 1, i-1);
	    }
	    return;
	}
}
12 6 ekon pannas