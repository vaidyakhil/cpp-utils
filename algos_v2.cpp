class AlgosV2 {
	public:
        // kadane's algo
    	static int maxSubArray(vector<int>& nums) {
            int n = nums.size();
            if ( n == 0) { 
                return 0;
            }
            
            long long res = nums[0];
            long long cur = 0;
            for (int i=0; i<n; i++) {
                cur+= nums[i];
                res = max(res, cur);
                
                if (cur < 0) {
                    cur = 0;
                }
            }
            return res;
    	}
} 
