#include <bits/stdc++.h>

using namespace std;

/*
**	It is ok if this class remains an empty class and just contains comments 
**	explaining certain algorithms that DO NOT QUITE FIT INTO SPECIFIC UTIL CLASSES
**	having said that, having method is a plus++ :P
*/
class AlgosV2 {

	public:


		/*
		**	Monotonous Stack problems:
		**	IMP ones being: rain water trapping and area in histogram
		**	In mono stack problems what we do is we push an element in stack if some condition is met,
		**	else we start poping elements untill condition is met,
		**	meanwhile calculate the possible res using the elements that are getting popped
		** 	since these elements we won't encounter again.
		** 	In this way mono stack approach sometimes results in O(n) time complexity
		**	for eg. see problem_solutions::trap for rain water problem
		*/


		/*
		** In a array with each number occuring twice accept TWO numbers.
		** Find those two numbers
		** Algo:
		**	res = xor all (this will be a^b)
		**	i = first set bit of res; (there will be one since two number are different)
		**	start xoring res with those which have ith bit set after traversing res = a
		**	start xoring res with those which have ith bit unset after traversing res = b
		*/

		/*
		**	Single Number occurs once, rest thrice
		**	Look at the handing for INT_MIN, since its binary represntation is: [1..(31 0s)..]
		** 	so we build result from first 31 bits, then handle sign
		*/
	    int singleNumber(vector<int>& nums) {
	        vector<int> bits(32, 0);
	        for (long a: nums) {
	            for (int i=0; i<32; i++) {
	                if (a & (1 << i)) {
	                    bits[i] = (bits[i] + 1) % 3;
	                }
	            }
	        }
	        int res = 0;
	        for (int i =30; i>=0; i--) {
	            res = 2 * res + bits[i];
	        }
	        return bits[31] ? res ^ INT_MIN : res;
	    }

	    /*
	    **	Boyer-Moore Voting Algorithm
	    **	Return an item which appears more than n/2 times
	    **	Linear time and O(1) space!!
	    **	Since the element appears more than n/2 times
	    **	
	    */
	    int majorityElement(vector<int>& A) {
	        int n = A.size();
	        int cur = A[0];
	        int count = 1;
	        for (int i=1; i<n; i++) {
	            if (A[i] == cur) {
	                count++;
	            } else {
	                count--;
	            }
	            
	            if (count == 0) {
	                cur = A[i];
	                count = 1;
	            }
	        }
	        
	        return cur;
	    }
};
