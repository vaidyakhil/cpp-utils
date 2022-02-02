class DpUtills {

    /*
    ** If all subproblems must be solved at least once, a bottom-up dynamic-programming algorithm usually outperforms a top-down memoized algorithm by a constant factor.

    ** If some subproblems need not to be solved at all, memoization will be better than DP, else in general DP outperforms memo due to less overhead of call stack.
    */


    /*
    ** MEMOIZATION TEMPLATE
        datatype recur_func(n,r){
            secure base cases:
            return c;
            check if value in memory:
                return it.
            x= INT_MAX/MIN
            for loop:
                x= min/max(recur_func(b,c), recur_func(d,e));
            else return cache[n][r]= x;
        }
    */

    private:
        // generates a string adding chars at the start and end of original string
        // that do not exist in original string 
        // adds a char again not part of original string, b/w every char
        string getManipualtedString(string s) {
            string res = "$";
            for (int i=0; i<s.size(); i++) {
                res+= "#";
                res+= s[i];
            }
            res+= "#";
            res+= "@";
            return res;
        }
    
    public:
        // manacher's algorithm
        string longestPalindromeSubString(string s) {
            int n = s.size();
            
            if (n<2) {
                return s;
            }
            
            string TEST = getManipualtedString(s);
            
            int m = TEST.size();
            vector<int> dp = vector<int>(m, 0);
            
            // here we maintain center and number of elements
            // which are same on the left and right of center
            // at any point the palindrome is one with greatest r 
            // (so that for most i >c, we have pre computed values)
            int cur = 0, r= 0;

            // these are final values of center and r in TEST string
            int resC = 0, resL = 0;
            
            for (int i = 2; i<m; i++) {
                
                if (i<r) {
                    dp[i] = min(dp[2*cur - i], r-i);    
                }
     
                // above ^^ initialization of dp[i], makes it possible not to compute several values
                while (i - dp[i] - 1 >=0 && i + dp[i] + 1 < m && TEST[i + dp[i] + 1] == TEST[i - dp[i] - 1]) {
                    dp[i]++;
                }
                
                if (i + dp[i] > r) {
                    cur = i;
                    r = i + dp[i];
                }
                
                if (dp[i] > resL) {
                    resL = dp[i];
                    resC= i;
                }
            }
            
            return s.substr((resC-1)/2 - resL/2, resL);
        }


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

        // with bin search lesser-than-or-equal-to variant
        // at every index generate the LIS till that index with smallest numbers possible
        // O(n) space
        // O(nlog(n)) time
        int lengthOfLISBinarySearch (vector<int>& nums) {
            int n= nums.size();
            if (n<2) {
                return n;
            }
            
            vector<int> lengths;
            lengths.push_back(nums[0]);
            
            for (int i=1; i<n; i++) {
                // bin search
                int pos = getLesserItem(lengths, 0, lengths.size()-1, nums[i]);
                if(lengths[pos] >= nums[i]) {
                    lengths[pos] = nums[i];
                } else if (lengths.size() > pos+1) {
                    lengths[pos+1] = nums[i];
                } else {
                    lengths.push_back(nums[i]);
                }
            }
            return lengths.size();
        }


        // longest palindromic subsequence lps
        // using O(n) space, O(n2) time
        int longestPalindromeSubseq(string s) {
            int n = s.size();
            if (n < 2) {
                return n;
            }
            
            vector<int> dp = vector<int>(n, 0);
            // before each iteration dp[j] contains length of lps bw [j, i-1];
            for (int i=0; i<n; i++) {
                int backup = 0;
                dp[i] = 1;
                for (int j = i-1; j>=0; j--) {
                    int newBackup = dp[j]; // contains lps [j, i-1]; this will become backup for [j-1, i] (i.e next iteration of j)
                    if (s[i] == s[j]) {
                        dp[j] = 2 + backup; 
                    } else {
                        dp[j] = max(newBackup, dp[j+1]); // max of lps [j, i-1] and lps [j+1, i];
                    }
                    backup = newBackup;
                }
            }
            return dp[0];
        }

        // using O(n) space, O(n2) time
        int longestCommonSubsequence(string text1, string text2) {
            int n = text1.size();
            int m = text2.size();
            
            if (n ==0 || m==0) {
                return 0;
            }
            
            vector<int> dp = vector<int>(n, 0);
            for (int j =0; j<m; j++) {
                int backup = dp[0];
                dp[0] = text1[0] == text2[j] || backup ? 1 : 0;
                // pay attention to ^^ this initialization of dp[0];  || backup
                for (int i = 1; i<n; i++) {
                    int newBackup = dp[i];
                    if (text1[i] == text2[j]) {
                        dp[i] = 1 + backup;    
                    } else {
                        dp[i] = max(dp[i], dp[i-1]);
                    }
                    backup = newBackup;
                }        
            }
            return dp[n-1];
        }

        // kadane's algo
        int maxSubArray(vector<int>& nums) {
            int n = nums.size();
            if ( n == 0) { 
                return 0;
            }
            
            long long res = nums[0];3
            long long cur = 0;
            for (int i=0; i<n; i++) {
                // if all nums are negative, we are comparing individual num with res,
                // since cur = 0 at the start of every iteration
                cur+= nums[i];
                res = max(res, cur);
                
                if (cur < 0) {
                    cur = 0;
                }
            }
            return res;
        }
}