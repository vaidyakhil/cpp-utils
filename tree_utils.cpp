#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left, *right;

	TreeNode(int value): val(value), left(NULL), right(NULL) {};
};

class TreesUtils {

    /*
    **  In case of linked list and trees pointer to pointer has to be sent
    **  in questions where the the sent head has to point somewhere else
    **  i.e VALUE IN POINTER HAS TO BE CHANGED SO POINTER TO POINTER HAS TO BE SENT
    */

    /*
    **  Balanced Binary tree is one which has all the levels filled except maybe the last one
    **  and all  the nodes are possiblly to the leftmost.
    **  Full binary tree is one in which every node has either 0 or 2 childeren
    */

    private:
		/*
		**traversals
		*/

		//inorder
        void recurInorder(TreeNode* root, vector<int>& res) {
            if (root == NULL) {
                return;
            }
            
            recurInorder(root->left, res);
            res.push_back(root->val);
            recurInorder(root->right, res);
        }

        void iterativeInorder(TreeNode* root, vector<int>& res) {
            if (root == NULL) {
                return;
            }
            stack<TreeNode*> st;
            TreeNode* curr = root;
            while (curr != NULL || !st.empty()) {
        		while (curr != NULL) {
        			st.push(curr);
        			curr = curr->left;
        		}
        		curr = st.top();
        		st.pop();
        		res.push_back(curr->val);
        		curr = curr->right;
            }
        }


        //preorder
        void recurPreorder(TreeNode* root, vector<int>& res) {
            if (root == NULL) {
                return;
            }
            
            res.push_back(root->val);
            recurPreorder(root->left, res);
            recurPreorder(root->right, res);
        }
    
        void iterativePreorder(TreeNode* root, vector<int>& res) {
            if (root == NULL) {
                return;
            }
            
            stack<TreeNode*> st;
            st.push(root);
            while (!st.empty()) {
                TreeNode *curr = st.top();
                st.pop();
                res.push_back(curr->val);
                
                if (curr->right != NULL) {
                    st.push(curr->right);
                }
                
                if (curr->left != NULL) {
                    st.push(curr->left);
                }
            }
        }

        /* postorder */
        void recurPostorder(TreeNode* root, vector<int>& res) {
            if (root == NULL) {
                return;
            }
            
            recurPostorder(root->left, res);
            recurPostorder(root->right, res);
            res.push_back(root->val);
        }
        
        /* -----> have not been able to do a iterative one for post order <------ */


        /*
        ** if simple level order, just push in one order
        */
        void recurZigZagLevelOrder(TreeNode* root, int cur, int height, vector<vector<int>>& res) {
            if (root == NULL) {
                return;
            }
            
            if (cur < height) {
                if (height % 2 == 0) {
                    recurZigZagLevelOrder(root->left, cur+1, height, res);
                    recurZigZagLevelOrder(root->right, cur+1, height, res);
                } else {
                    recurZigZagLevelOrder(root->right, cur+1, height, res);
                    recurZigZagLevelOrder(root->left, cur+1, height, res);
                }
                return;
            }
            
            if (res.size() <= height) {
                res.push_back(vector<int>());
            }
            
            res[height].push_back(root->val);
            return;
        }

	public:

		static vector<int> traverseTree(TreeNode* root) {
	        vector<int> res;
            /*
            ** methods among the above ^^
	        ** typeOrderOfChoiceFn(root, res);
            */
	        return res;
		}

        static int getHeight(TreeNode* root) {
            if(root == NULL)
                return 0;

            return 1+ max(getHeight(root->left),getHeight(root->right));
        }

        vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
            vector<vector<int>> res;
            int height = getHeight(root);
            
            int h = 0;
            while (h < height) {
                recurZigZagLevelOrder(root, 0, h, res);
                h++;
            }
            
            return res;
        }
};