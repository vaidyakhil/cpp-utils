class DpUtills {

	// LIS
	// n2 sol
	int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return n;
        }
        
        int res = 1;
        vector<int> dp = vector<int>(n, 1);
        for (int i = 1; i<n; i++) {
            for (int j=0; j<i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], 1+dp[j]);
                }
            }
            res = max(res, dp[i]);
        }
        
        return res;
    }

    // with bin search
    // at every index generate the LIS till that index with greatest number smallest possible
    // O(n) space


}