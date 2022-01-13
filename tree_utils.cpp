#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left, *right;

	TreeNode(int value): val(value), left(NULL), right(NULL) {};
}

class Trees {
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

        //postorder
        void recurPostorder(TreeNode* root, vector<int>& res) {
            if (root == NULL) {
                return;
            }
            
            recurPostorder(root->left, res);
            recurPostorder(root->right, res);
            res.push_back(root->val);
        }
        // have not been able to do a iterative one for post order

	public:

		static vector<int> traverseTree(TreeNode* root) {
	        vector<int> res;
            // methods among the above ^^
	        // typeOrderOfChoiceFn(root, res);
	        return res;
		}

        static int getHeight(TreeNode* root) {
            if(root == NULL)
                return 0;

            return 1+ max(depth(root->left),depth(root->right));
        }	
};