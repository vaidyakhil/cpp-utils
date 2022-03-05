#include <bits/stdc++.h>

using namespace std;

class BitUtils {
public:
	int countSetBits (int num) {
		int res = 0;
		int n = num;
		while (n) {
			res++;
			n = n & (n-1);
		}
		return res;
	}


	// power sub set problem by bit-masking
	vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        int num = pow(2, n), i = 0;
        
        while(i<num)
        {
            vector<int> temp;
            for(int j=0; j<n; j++)
            {
                if(i & 1<<j)
                    temp.push_back(nums[j]);
            }
            ans.push_back(temp);
            i++;
        }
        
        return ans;
    }
};