class Solutions {
	public:
		/*
		** https://www.interviewbit.com/blog/minimum-number-of-jumps/
		*/
		static int minJump(vector<int> &A) {
	        int n = A.size();
	        int res = 0;
	        if (n < 2) {
	            // return true;
	            return 0;
	        }

	        int pos = 0;
	        int start = pos + 1;
	        while (pos + A[pos] < n-1) {
	            int newPos = pos;
	            int i = start;
	            int curMax = pos + A[pos];
	            while (i<=curMax) {
	                if (i + A[i] > newPos + A[newPos]) {
	                    newPos = i;
	                }
	                i++;
	            }
	            if (newPos == pos) {
	                // return false;
	                return -1;
	            }
	            start = curMax+1;
	            pos = newPos;
	            res++;
	        }
	        res++;
	        // return true;
	        return res;
		}

		/*
		**  GOOD PROBLEM USE OF LINKED LIST CYCLE DETECTION ALGO.
		**  https://leetcode.com/problems/find-the-duplicate-number/discuss/72846/My-easy-understood-solution-with-O(n)-time-and-O(1)-space-without-modifying-the-array.-With-clear-explanation.
		*/
		

		/*
		**  GOOD PROBLEM VARIANT OF BUY SELL WITH COOLDOWN PERIOD
		**  https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
		*/

        /*
        ** EDIT DISTANCE (convert word1 -> word2) in minm operations
        ** https://leetcode.com/problems/edit-distance/submissions/
        ** m = word1 size
        ** n = word2 size
        */

	    int recurEditDistance(string& word1, string& word2, int i, int j, Vec& dp) {
	        // base cases
	        if(dp[j][i] != -1) {
	            return dp[j][i];
	        }
	        int res;
	        if (word1[i] == word2[j]) {
	            res = min(
	                recurEditDistance(word1, word2, i-1, j-1, dp),
	                1+min(
	                    recurEditDistance(word1, word2, i, j-1, dp),
	                    recurEditDistance(word1, word2, i-1, j, dp)
	                )
	            );
	        } else {
	            res = 1+min(
	                recurEditDistance(word1, word2, i-1, j-1, dp),
	                min(
	                    recurEditDistance(word1, word2, i, j-1, dp),
	                    recurEditDistance(word1, word2, i-1, j, dp)
	                )
	            );
	        }
	        return dp[j][i] = res;
	    }
	    
	    int iterativeEditDistance(string& word1, string& word2, Vec& dp) {
	        int n = word1.size();
	        int m = word2.size();
	        
	        for (int i=1; i<m; i++) {
	            for (int j=1; j<n; j++) {
	                
	                int replaced = dp[i-1][j-1];
	                int deleted = dp[i-1][j];
	                int inserted = dp[i][j-1];
	                
	                if (word1[j] == word2[i]) {
	                    dp[i][j] = min(
	                        replaced, // if char matches we will start comparing next of both, no operation
	                        1+min(
	                            deleted,
	                            inserted
	                        )
	                    );
	                } else {
	                    dp[i][j] = 1+min(
	                        replaced,
	                        min(
	                            deleted,
	                            inserted
	                        )
	                    );
	                }
	            }
	        }
	        
	        return dp[m-1][n-1];
	    }


		/*
		** 	PASS VAUE BY REFERENCE AS MUCH AS POSSIBLE, CAN SAVE A LOT IN REQUIRED MEMORY!!
		**	see notes/pass_by_ref_on_memory_usage
		** 	https://leetcode.com/problems/n-queens/submissions/
		*/

		
		/*
		** 	GOOD PROBLEM, Graph, remove leaf nodes layer by layer;
		** 	https://leetcode.com/problems/minimum-height-trees/
		*/


		/*
		** 	GOOD PROBLEM, RAIN WATER TRAPPING PROBLEM;
		**	multiple approaches: left, right array, mono stack approach and 2 pointer approach
		**	The two pointer approach being least intuitive but best performant
		**	stack approach increments in horizontal boxes, while others do in vertical.
		** 	https://leetcode.com/problems/trapping-rain-water/
		*/
	    int trap(vector<int>& arr) {
	        int n = arr.size();
	        int res = 0;
	        int lo=0, hi = n-1;
	        int lMax = 0, rMax = 0;
	        while (lo < hi) { 
	        // we are calculating for all the walls

	        	// 	we get to update the water on lo(th) index 
	        	//	only when bounding wall (min among l,r max) is lMax;
        		//	simillarly we get to .. hi(th)..
        		//	... is rMax;
	            if (arr[lo] < arr[hi]) {
	                (arr[lo] > lMax) ?
	                	(lMax = arr[lo]) : res+= lMax-arr[lo]; 
	                lo++;
	            } else {
	                (arr[hi] > rMax) ?
                		(rMax = arr[hi]) : res+= rMax-arr[hi];
	                hi--;
	            }
	        }
	        
	        return res;
	    }


		/*
		** 	GOOD PROBLEM, LARGEST RECTANGLE AREA PROBLEM;
		**	multiple approaches again: left, right array, mono stack approach
		**	stack approach increments in horizontal boxes, while others do in vertical.
		**	Both are O(n), O(n), just that stack does it in 1 pass
		** 	https://leetcode.com/problems/largest-rectangle-in-histogram/
		*/
	    int largestRectangleArea(vector<int>& arr) {
	        int n = arr.size();
	        int res = 0;
	        stack<int> st;
	        int i = 0;

	        // run till the stack is empty
	        while (i<n || !st.empty()) {

	        	// even when we have traversed whole array, we might have missed comp areas for some
	        	// think sorted inc array
	        	// hence the i==n block
	        	//	we use i =n element as height = 0 element (shorter from all)
	            while (!st.empty() && ( i == n || arr[st.top()] > arr[i] )) {
	            	// you got an element which is smaller than the top of stack element
	            	// this indicates that if we create rect of height of h[st.top]
	            	// i will be the right boundry for such rect
	            	// left boundry will be st.top after popping cur.
	                int cur = st.top();
	                st.pop();

	                int left = st.empty() ? -1 : st.top();
	                int right = i;
	                res = max((right-left-1)*arr[cur], res);
	            }
	            if (i<n) {
	                st.push(i);    
	                i++;
	            }
	        }

	        return res;
	    }
}