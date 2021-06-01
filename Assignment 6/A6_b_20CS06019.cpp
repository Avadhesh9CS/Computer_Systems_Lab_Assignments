/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem
/*
Given  a  preorder  and  inorder  traversal,  write  a  C/C++  program  to  create  a  binary  tree.
Write a C function that will print the length of the longest path in the tree
*/

#include <iostream>
#include <vector>
using namespace std;

// Data structure to store a Binary Tree node
struct Node{
	char data;
	Node *left, *right;
};

// Function to create a new binary tree node having given key
Node* newNode(char data){
	Node* node = new Node;
	node->data = data;
	node->left = node->right = nullptr;
	return node;
}

/* Function to find index of value in arr[start...end]   */
int search(vector<char> &inorder, int start,int end, int value){
    int i;
    for (i = start; i <= end; i++){
        if (inorder[i] == value) {
            return i;
        }
    }
    return i; // Just to remove warning of void return of non void function
}

// Recursive function to construct a binary tree from given inorder and preorder sequence
Node* BuildTree(vector<char> &inorder,vector<char> &preorder,int start, int end){
    static int pIndex=0;
	// base case
	if (start > end)
		return nullptr;

	// The next element in preorder[] will be the root node of subtree formed by inorder[start, end]
	Node *root = newNode(preorder[pIndex]);
	pIndex++;

	// get the index of root node in inorder[] to determine the boundary of left and right subtree
	int index =search(inorder,start,end,root->data);

	// recursively construct the left subtree
	root->left = BuildTree(inorder, preorder,start, index - 1);

	// recursively construct the right subtree
	root->right = BuildTree(inorder, preorder,index + 1, end);

	// return current node
	return root;
}
// function to find depth of node
int depth(Node* root){
      //Base case
    if (root == nullptr)
		return 0;
    //Just to reduce function calls I create l and r variable
    //l gave no of level in left subtree
    int l=depth(root->left);
    //r gave no of level in right subtree
    int r=depth(root->right);
     //return maximum no of level
    return l>r?l+1:r+1;

}
// Find longest path between any two node in tree
int longestpath(Node* root){
    //Base case when no node in tree
    if (root == nullptr)
		return 0;
    return depth(root->left)+depth(root->right);
}

// Driver Code
int main(){
    int n;
    cout<<"Enter no of node in the tree: ";
    cin>>n;
    vector<char> inorder(n);
    vector<char> preorder(n);
    cout<<"Enter in-order Traversal of tree: ";
    for(int i=0;i<n;i++){
        cin>>inorder[i];
    }
    cout<<"Enter pre-order Traversal of tree: ";
    for(int i=0;i<n;i++){
    cin>>preorder[i];
    }
    Node* root =(Node*)BuildTree(inorder, preorder, 0, n-1);
    std::cout<< std::endl << "       -----OUTPUT-----" << std::endl;
    cout<<"Longest path in given tree is of length: "<<longestpath(root);
    return 0;
}

