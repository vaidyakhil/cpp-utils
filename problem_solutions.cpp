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
		*  GOOD PROBLEM USE OF LINKED LIST CYCLE DETECTION ALGO.
		*  https://leetcode.com/problems/find-the-duplicate-number/discuss/72846/My-easy-understood-solution-with-O(n)-time-and-O(1)-space-without-modifying-the-array.-With-clear-explanation.
		*/
		

		/*
		*  GOOD PROBLEM VARIANT OF BUY SELL WITH COOLDOWN PERIOD
		*  https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
		*/
}