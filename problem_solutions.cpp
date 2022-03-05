#include<bits/stdc++.h>

using namespace std;

/*
**	This class should have solutions to interesting problems
**	Interesting here means, either they are solved using a new concept,
**	or they are important from interview perspective
*/
class Solutions {
	private:
	    
	    int getNum (string s) {
	        int res = 0;
	        for (char ch: s) {
	            res = 10 * res + (ch - '0');
	        }
	        return res;
	    }

	public:
		/*
		** https://www.interviewbit.com/blog/minimum-number-of-jumps/
		*/
		int minJump(vector<int> &A) {
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
		** 	PASS VAUE BY REFERENCE AS MUCH AS POSSIBLE,
		**	CAN SAVE A LOT IN REQUIRED MEMORY!!
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


		/*
		**	SLIDING WINDOW TECHNIQUE
		**	problem: min sub-array length with sum >= target
		**	BRUTE -> for every i, find sum for [i, j] till sum >= target, take min of ans (n2)
		**	IMPROVE ON BRUTE -> cretae sums array, now for every i, use binary search on sums,
		**	such that sums[mid] - sums[i-1] >= target, take min of ans (nlog(n))
		** 	sliding window, take 2 pointers i, j, on every iteration incr cur with arr[j],
		**	remove ith element til the sum >= target, take min of j-i+1, O(n)
		**	problem: https://leetcode.com/problems/minimum-size-subarray-sum/
		*/

    	int minSubArrayLen(int target, vector<int>& nums) {
	        int n = nums.size();
	        if (n == 0) {
	            return -1;
	        }
	        
	        int res = n+1;
	        int i=0, j=0;
	        int cur = 0;
	        while (j<n) {
	            cur+=nums[j];
	            while (i <= j && cur - nums[i] >= target) {
	                cur-= nums[i];
	                i++;
	            }
	            
	            if (cur >= target) {
	                res = min(res, j-i+1);
	            }
	            
	            j++;
	        }
	        return res == n+1 ? -1 : res;
	    }


	    /*
	    **	TODO: refacor to use binary_search_utils
	    */

	    /*
	    **	Longest Increasing Subsequence
	    **	Best time: nlog(n), space: O(n)
	    */
	    int binSearch (int hi, int target, vector<int>& arr) {
		    int lo = 0;
		    while (lo < hi) {
		        int mid = lo + (hi-lo)/2;
		        if (arr[mid] < target) {
		            lo = mid+1;
		        } else {
		            hi = mid;
		        }
		    }
		    return lo;
		}

		/*
		**	In the res array, res[i] denotes the smallest
		**	largest element in an lis of length i+1
		** 	at any point of time. (little tricky it is)
		*/
		int lis(const vector<int> &arr) {
		    int n = arr.size();
		    vector<int> res;
		    for (int i=0; i<n; i++) {
		        int index = binSearch(res.size()-1, arr[i], res);
		        if (index == res.size() || res[index] < arr[i] ) {
		            res.push_back(arr[i]);
		        } else {
		            res[index] = arr[i];
		        }
		    }
		    return res.size();
		}



		/*
		**	Puzzle
		** Bulb switching
		** Logic: since all the factors of a number appear in a number,
		** there will be 2x factors of it, unless its a perfect sqr,
		** in which case it will have pair of factors where both are same
		*/


		/*
		**	Irritating questions like area in 2D matrix etc,
		**	Think carefully about the dp.
		**	https://leetcode.com/problems/maximal-square/submissions/
		*/
		int maximalSquare(vector<vector<char>>& matrix) {
	        int m = matrix.size();
	        int n = matrix[0].size();
	        vector<int> dp(n, 0);
	        
	        int res = 0;
	        for (int i=0; i<n; i++) {
	            dp[i] = matrix[0][i] - '0';
	            res = max(res, dp[i]);
	        }
	        
	        
	        for (int i = 1; i<m; i++) {
	            int backup = dp[0];
	            dp[0] = matrix[i][0] - '0';
	            res = max(res, dp[0]);
	            for (int j = 1; j<n; j++) {
	                int temp = dp[j];
	                dp[j] = matrix[i][j] == '1' ?
	                    1 + min(
	                        backup,
	                        min(
	                            dp[j-1],
	                            dp[j]
	                        )
	                    ) :
	                    0;
	                backup = temp;
	                res = max(res, dp[j] * dp[j]);
	            }
	        }
	        return res;
	    }

	    /*
	    **	Majority element in an array,
	    **	if defined as one with more than n/2 occurances there will be 1 max
	    ** 	................................ n/3 ........................ 2 max
	    **	These problems can be approached using Boris-morse (not sure of name) algo
	    ** 	problem: https://leetcode.com/problems/majority-element-ii/
	    **	Works on voting logic, if some element occurs more than others than
    	**	the last one to survive must be it.
	    */
	 	vector<int> majorityElement(vector<int>& nums) {
	        int n = nums.size();
	        if (n == 0) {
	            return {};
	        }
	        int cand1 = nums[0];
	        int cnt1= 0;
	        int cand2 = cand1 -1;
	        int cnt2= 0;
	        
	        for (int item: nums) {
	            if (item == cand1) {
	                cnt1++;
	            } else if (item == cand2) {
	                cnt2++;
	            } else if (cnt1 == 0) {
	                cand1 = item;
	                cnt1 = 1;
	            } else if (cnt2 == 0) {
	                cand2 = item;
	                cnt2 = 1;
	            } else {
	                cnt1--;
	                cnt2--;
	            }
	        }
	        
	        cnt1 = 0;
	        cnt2 = 0;
	        for (int item: nums) {
	            if (item == cand1) {
	                cnt1++;
	            } else if (item == cand2) {
	                cnt2++;
	            }
	        }
	        
	        vector<int> res;
	        if (cnt1 > n/3) {
	            res.push_back(cand1);
	        }
	        if (cnt2 > n/3) {
	            res.push_back(cand2);
	        }
	        return res;
	    }

	    /*
	    **	number of BST with node value from 1 to n
	    */
        int numTrees(int n) {
	        int ans[n+1];
	        ans[0] = 1;
	        ans[1] = 1;
	        for (int i = 1; i<=n; i++) {
	            int cur = 0;
	            for (int j = 0; j<i; j++) {
	                cur += ans[j] * ans[i-j-1];
	            }
	            ans[i] = cur;
	        }
	        return ans[n];
	    }

	    /*
	    **	Solution is pretty cool
	    ** 	if a solution exist, total must be >= 0
	    **	lets say total >= 0, so solution exist.
	    **	if 0 is a sol, cur will never update, if it has updated to something to lets say "cur" after loop ends
	    **	indices before cur can not be sol for sure.
	    ** 	if i > cur is a solution, then cur must also be a solotion :P
	    **	hence cur will be the solution
	    */
	    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	        int n = gas.size();
	        int total = 0;
	        int cur = 0;
	        int start = 0;
	        for (int i =0; i<n; i++) {
	            total += gas[i] - cost[i];
	            cur += gas[i] - cost[i];
	            if (cur < 0) {
	                start = i+1;
	                cur = 0;
	            }
	        }
	        return total >= 0 ? start : -1;
	    }


	    /*
	    **	Solution is pretty cool
	    **	https://leetcode.com/problems/largest-divisible-subset/
	    */
        vector<int> largestDivisibleSubset(vector<int>& arr) {
	        int n = arr.size();
	        sort(arr.begin(), arr.end());
	        vector<int> dp(n, 1);
	        vector<int> next(n, -1);
	        int resLen = 1;
	        int res = 0;
	        for (int i=1; i<n; i++) {
	            for (int j=i-1; j>=0; j--) {
	            	// pretty much same as the O(n2) sol of LIS
	                if (arr[i]%arr[j] == 0 && 1 + dp[j] > dp[i]) {
	                    dp[i] = 1 + dp[j];
	                    next[i] = j;
	                }
	                if (resLen < dp[i]) {
	                    resLen = dp[i];
	                    res = i;
	                }
	            }
	        }
	        
	        vector<int> ans;
	        while (res != -1) {
	            ans.push_back(arr[res]);
	            res = next[res];
	        }
	        return ans;
    	}
   
   		/*
   		**	Number of ways to decode a string
   		** 	https://leetcode.com/problems/decode-ways/
   		**	ITS ALL ABOUT HANDLING ZERO PROPERLY
   		*/
	    int numDecodings(string s) {
	        int n = s.size();
	        if (n == 0 || s[0] == '0') {
	            return 0;
	        }
	        
	        int prev = 1;
	        int cur = 1;
	        for (int i=1; i<n; i++) {
	            int temp = 0;
	            if (s[i] != '0') {
	                temp+= cur;
	            }
	            
	            int twoDig = getNum(s.substr(i-1, 2));
	            if (twoDig == 0) {
	                return 0;
	            }
	            
	            if (twoDig < 27 && twoDig > 9) {
	                temp+= prev;
	            }
	            prev = cur;
	            cur = temp;
	        }
	        return cur;
	    }

    	// https://leetcode.com/problems/jump-game-vii/discuss/1224804/JavaC%2B%2BPython-One-Pass-DP
};

