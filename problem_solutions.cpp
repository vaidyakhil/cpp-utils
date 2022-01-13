class Solutions {
	public:
		/*
		** https://www.interviewbit.com/blog/minimum-number-of-jumps/
		*/
		static int minJump(vector<int> &A) {
		    int n = A.size();
		    int res = 0;
		    if (n < 2) {
		        return res;
		    }

		    int pos = 0;
		    res++;
		    while (pos + A[pos] < n-1) {
		        int i = pos + 1;
		        int curRadius = pos + A[pos];
		        while (i <= curRadius) {
		            if (i + A[i] > pos + A[pos]) {
		                pos = i;
		            }
		            i++;
		        }
		        if(pos + A[pos] <= curRadius) {
		            return -1;
		        }
		        res++;
		    }
		    return res;
		}

		/*
		*  GOOD PROBLEM USE OF LINKED LIST CYCLE DETECTION ALGO.
		*/
		https://leetcode.com/problems/find-the-duplicate-number/discuss/72846/My-easy-understood-solution-with-O(n)-time-and-O(1)-space-without-modifying-the-array.-With-clear-explanation.

		/*
		*  GOOD PROBLEM VARIANT OF BUY SELL WITH COOLDOWN PERIOD
		*/
		https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
}