#include <iostream>
#include <string>
#include <queue>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        TreeNode *curRoot = root;
        TreeNode *head;
        queue<TreeNode*> q, nextq;
        nextq.push(root);
        bool allNull = true;
        if(root) allNull = false;

        
        while(!nextq.empty() && !allNull) {
            allNull = true;
            q = nextq;
            while(!nextq.empty())
                nextq.pop();
            
            while(!q.empty()) {
                head = q.front();
                q.pop();
                
                if(!head) {
                    res += "null,";
                    continue;
                }
                
                res += to_string(head->val) + ",";
                if(head->left || head->right) allNull = false;

                nextq.push(head->left);
                nextq.push(head->right);
            }
        }
        
        
        if(res.back() == ',')
            res.pop_back();
        //cout << "ser: " << res << endl;
        
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(!data.size())
            return nullptr;
        
        TreeNode *root, *curRoot;
        root = nullptr;
        
        int start=0;
        size_t next = 0;
        next = data.find(',', start);
        if(next==string::npos) { // is the only element
            int val = stoi(data.substr(start), &next, 10);
            root = new TreeNode(val);
            return root;
        }
        
        int val = stoi(data.substr(start), &next, 10);
        root = new TreeNode(val);
        queue<TreeNode*> q;
        q.push(root);
        //cout << "added: " << root->val << endl;
        
        start = next + 1;
        
        while( start < data.size() ) {
            curRoot = q.front();
            q.pop();
            
            //cout << "new start: " << start << endl;
            
            if(data.find("null", start)==start) {
                curRoot -> left = nullptr;
                start += 5;
            } else {
                int leftVal = stoi(data.substr(start), &next, 10);
                curRoot->left = new TreeNode(leftVal);
                q.push(curRoot->left);
                //cout << "added left: " << curRoot->left->val << endl;
                start += next + 1 ;
            }
            
            
            //cout << "new start: " << start << endl;
            if(start >= data.size()) {
                break;
            }
            
            if(data.find("null", start)==start) {
                curRoot -> right = nullptr;
                start += 5;
            } else {
                int rightVal = stoi(data.substr(start), &next, 10);
                curRoot->right = new TreeNode(rightVal);
                q.push(curRoot->right);
                //cout << "added right: " << curRoot->right->val << endl;
                start += next + 1 ;
            }
            
        }
        
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));



int main() {
    Codec c;
    std::string str;
    getline(std::cin, str); 
    cout << "str size: " << str.size() << endl;
    TreeNode* tree = c.deserialize(str);
    string res = c.serialize(tree);
    TreeNode *tree2 = c.deserialize(res);
    string res2 = c.serialize(tree2); 
    if(res == res2 ) {
        cout << "equal trees\n";
    } else {
        cout << "oops! not equal\n";
    }

}

