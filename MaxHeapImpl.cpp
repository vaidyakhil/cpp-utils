#include <bits/stdc++.h>

using namespace std;

class MaxHeap {
	/*
	**	Heap data structure:
	**	Parent has strict order with children, children have no strict order among them
	**	One implementation of heap involves use of queueImplay,
	**	parent is stored at i, 2 childre are at 2*i, 2*i+1
	**	so there will be n/2 leaf nodes (n/2 non leaf nodes)
	*/

	/*
	** 	Implementation here is for max heap, 
	**	similar can be done for min heap
	*/

private:

    int length;
    vector<int> queueImpl;

    void swap(int i, int j){
        int temp= queueImpl[i];
        queueImpl[i]= queueImpl[j];
        queueImpl[j]=temp;
    }

	/*
	**	To be called on heap with 2*i, 2*i+1 heapified children
	**	log(n), if total n elements smaller or equal to queueImpl[i]
	*/
	void maxHeapify (int i) {
		// left child
	    int left = 2*i;
	    //right child
	    int right = 2*i +1;

    	// evaluate which one is largest and swap it with i
	    int largest = i;
	    if(left <= length and queueImpl[left] > queueImpl[i] ) {
    		largest = left;
	    }
	          
	    if(right <= length and queueImpl[right] > queueImpl[largest] ) {
    		largest = right;
	    }

	    if(largest != i )
	    {
	        swap (queueImpl[i] , queueImpl[largest]);

	        // then recursively heapify the correct child
	        maxHeapify (largest);
	    } 
	 }

public:

	static const int NVAL = -1;

    MaxHeap(){
        length=1;
        queueImpl= vector<int>(1, NVAL);
    }

    bool empty(){
        if(length== 1) return true;
        return false;
    }

    void push(int a){
    	queueImpl.push_back(a);
    	int i= length;
        while(i > 1 && queueImpl[i] > queueImpl[i/2]){
            swap(i ,i/2);
            i= i/2;
        }
        length= length+1;
    }

    int top(){
        if(queueImpl.size()==1) return NVAL;
        return queueImpl[1];
    }

    int pop(){
        if(queueImpl.size()==1) return NVAL;
        int ans= queueImpl[1];
        queueImpl[1]= queueImpl[length];
        length= length-1;
        maxHeapify(1);
        return ans;
    }
};