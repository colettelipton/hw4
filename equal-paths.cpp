#ifndef RECCHECK
#include <iostream>
#endif

#include "equal-paths.h"
#include <algorithm>
using namespace std;

bool treelen(int curlen, int& fpath, Node* root);

bool equalPaths(Node * root)
{
	int first = -1;
	return treelen(0, first, root);
}

bool treelen(int curlen, int& fpath, Node* root){
	if(root == nullptr){
		return true;
	}
	if(root->left == nullptr && root->right == nullptr){
		if(fpath == -1){
			fpath = curlen;
			return true;
		}

		else{
			return fpath == curlen;
		}
	}
	
	// recurse down left subtree
	bool left = treelen(curlen + 1, fpath, root->left);

	// recurse down right subtree
	bool right = treelen(curlen + 1, fpath, root->right);

	if(left && right) return true;
	else return false;
	
}
