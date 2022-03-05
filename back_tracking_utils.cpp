/*
** try to make a tree, on every level you are iterating over possible options, 
** DO NOT TRY TO MAKE IT A BINARY TREE WHEN ITS NOT
*/


/*
*	BACKTRACKING PROBLEMS: all these problems on leetcode
*  	* COMBINATION I (UNIQUE NUMBERS) 
*   * COMBINATION II (DUPLICATE NUMBERS)
*   * COMBINATION III (DUPLICATE NUMBERS)
*  	* PERMUTATION I (UNIQUE NUMBERS)
*   * PERMUTATION II (DUPLICATE NUMBERS)
*  	* SUBSETS I (UNIQUE NUMBERS)
*   * SUBSETS II (DUPLICATE NUMBERS)
*/

/*
** consider this standard solution as better as this applies to all
** push something go dfs, if does not work pop it (back track cur branch) 
** can be remembered as backtracking  template:
*/

void recurCombWithoutRepetition(vector<int>& nums, int target, int i, vector<int> cur, vec& res) {
    // notice the order first check success condition than out of bound
    // this will avoid missing success cases
    if (target == 0) {
        res.push_back(cur);
        return;
    }            

    if (i < 0 || target < 0) {
        return;
    }
    

    // notice this not being a binary tree
    for (int j = i; j>=0; j--) {
        cur.push_back(nums[j]);
        recurComb(nums, target - nums[j], j, cur, res);
        cur.pop_back();
    }
    return;
}











 coin change krna hai




