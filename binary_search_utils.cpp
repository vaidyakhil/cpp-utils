#include <bits/stdc++.h>

using namespace std;

class BinarySearchUtils {

	/*
	** binary search VERY IMP POINTS
	** There are basically two forms of binary search functions that we are using
	** Each one differs slightly from the other and when to use which depends on 
	** usecase only.
	** the VERY IMP points highlighted are due to how division is approximated to floor values
	** and is very important in order to avoid TLE
	** if res required is >= key, this also gives the least index if multiple present
	** change low agressively
	** define mid = l + (h-l)/2
	*/
	int binSearchHighestIndex(vector<int> arr, int l, int h, int key) {
	    while(l<h){
	        int mid= l+(h-l)/2; // VERY IMP can't stress this enough, will go in TLE otherwise
	        if(arr[mid] < key)
	            l= mid+1;
	        else 
	            h= mid;     
	    }
    	return l;
	}

	/*
	** if res required is <= key, this also gives the highest index if multiple present
	** change high agressively
	** define mid = l + (h-l+1)/2
	*/
	int binSearchHighestIndex(vector<int> arr, int l, int h, int key) {
	    while(l<h){
	        int mid= l+(h-l+1)/2; // VERY IMP can't stress this enough, will go in TLE otherwise
	        if(arr[mid] > key)
	            h= mid-1;
	        else 
	            l= mid;     
	    }
    	return l;
	}
    
};