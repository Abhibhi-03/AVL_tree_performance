#ifndef _AVLTREE_H_
#define _AVLTREE_H_
#include <algorithm>
#include <iostream>
#include <fstream>
// AVLTree.cpp: AVL Tree Implementation in C++   */
// Modified by Fahad Ali Khan Wednesday March 20, 2024

// changed the node and avl tree to take any data and store it and changed the value of search from sin to id in the NODE instead of
// in the data structure to accomodate for complex datastructures that would be stored in T data.

extern std::ofstream outfile;

typedef struct EmployeeInfo {
	int salary;
	int age;
	int emplNumber;
	int sin;//search by social insurance number
}EmployeeInfo;

template<typename T>
struct node {
	T data;
	node* left;
	node* right;
	int height;
	int id;  //this is just used for search 
};

template<typename T>
class AVL
{

	node<T>* root;

	void makeEmpty(node<T>* t)
	{
		if (t == NULL)
			return;
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	int max(int a, int b) {
		if (a > b) return a;
		else return b;
	}

	int min(int a, int b) {
		if (a < b) return a;
		else return b;
	}

	node<T>* insert(T data, node<T>* t, int value)
	{
		if (t == NULL)
		{
			t = new node<T>;
			t->data=data;
			t->height = 0;
			t->left = t->right = NULL;
			t->id = value;
		}
		else if (value < t->id)
		{//Go down the left tree
			t->left = insert(data, t->left,value);
			if (height(t->left) - height(t->right) == 2)
			{   //Left is higher than right by two
				if (value < t->left->id)
					t = singleRightRotate(t);//will go down the left subtree, do right rotate
				else
					t = doubleRightRotate(t);//will go down the right subtree, do left-right rotate
			}
		}
		else if (value > t->id)
		{//Go down the right tree
			t->right = insert(data, t->right,value);
			if (height(t->right) - height(t->left) == 2)
			{//Right is higher than left by two
				if (value > t->right->id)
					t = singleLeftRotate(t);//Will go down the right subtree, do left rotate
				else
					t = doubleLeftRotate(t);//Will go down the left subtree, do right-left rotate
			}
		}

		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node<T>* singleRightRotate(node<T>*& t)

	{	
		if (t == nullptr) {
			// Handle the error here, for example:
			return nullptr;
		}
		//        8
   //    4             12
   // 2     6     10        14    
   //1 3   5 7   9  11    13  15
		node<T>* u = t->left;
		if (u == nullptr) {
			// Handle the error here, for example:
			return t;
		}
		//          8
		//    4(U)          12
		// 2     6     10        14    
		//1 3   5 7   9  11    13  15
		t->left = u->right;
		//          8
		//    6          12
		// 5     7     10        14    
		//            9  11    13  15
		//---------------------------
		//    4(U)
		// 2     6
		//1 3   5 7
		u->right = t;
		//          4
		//    2           8
		// 1     3    6         12    
		//           5 7    10     14
		//                 9  11 13  15
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), t->height) + 1;
		return u;
	}

	node<T>* singleLeftRotate(node<T>*& t)
	{
		if (t == nullptr) {
			// Handle the error here, for example:
			return nullptr;
		}
	//        8
   //    4             12
   // 2     6     10        14    
   //1 3   5 7   9  11    13  15
		node<T>* u = t->right;
		if (u == nullptr) {
			// Handle the error here, for example:
			return t;
		}
		//          8
		//    4             12(U)
		// 2     6     10        14    
		//1 3   5 7   9  11    13  15
		t->right = u->left;
		//          8
		//    4        10
		// 2     6   9   11    
		//1 3   5 7
		//-------------------------
		//                  12(U)
		//             10        14    
		//            9  11    13  15
		u->left = t;
		//              12
		//       8              14
		//   4      10     13        15    
		// 2   6   9  11
		//1 3 5 7
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(t->right), t->height) + 1;
		return u;
	}

	node<T>* doubleLeftRotate(node<T>*& t)
	{   //Right rotate the right node< EmployeeInfo>, then left rotate the current node< EmployeeInfo>
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}

	node<T>* doubleRightRotate(node<T>*& t)
	{   //Left rotate the left node< EmployeeInfo>, then right rotate the current node< EmployeeInfo>
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}
	
	node<T>* findMin(node<T>* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node<T>* findMax(node<T>* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	node<T>* remove(int sin, node<T>* t)
	{
		node<T>* temp;

		// Element not found
		if (t == NULL)
			return NULL;

		// Searching for element
		else if (sin < t->id)
			t->left = remove(sin, t->left);
		else if (sin > t->id)
			t->right = remove(sin, t->right);

		// Element found
		// With 2 children
		else if (t->left && t->right)
		{
			temp = findMin(t->right);
			t->id = temp->data.sin;
			t->right = remove(t->id, t->right);
		}
		// With one or zero child
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
		}
		if (t == NULL)
			return t;

		t->height = max(height(t->left), height(t->right)) + 1;

		// If node< EmployeeInfo> is unbalanced
		// If left node< EmployeeInfo> is deleted, right case
		if (height(t->left) - height(t->right) == 2)
		{
			// right right case
			if (height(t->left->left) - height(t->left->right) == 1)
				return singleLeftRotate(t);
			// right left case
			else
				return doubleLeftRotate(t);
		}
		// If right node< EmployeeInfo> is deleted, left case
		else if (height(t->right) - height(t->left) == 2)
		{
			// left left case
			if (height(t->right->right) - height(t->right->left) == 1)
				return singleRightRotate(t);
			// left right case
			else
				return doubleRightRotate(t);
		}
		return t;
	}

	int height(node<T>* t)
	{
		return (t == NULL ? -1 : t->height);
	}

	int getBalance(node<T>* t)
	{
		if (t == NULL)
			return 0;
		else
			return height(t->left) - height(t->right);
	}

	void inorder(node<T>* t)
	{
		if (t == NULL)
			return;
		inorder(t->left);
		outfile << " height:" << t->height << " sin:" << t->data.sin << " employee number:" << t->data.emplNumber << " salary:" << t->data.salary << " age:" << t->data.age << std::endl;

		inorder(t->right);
	}

public:
	AVL()
	{
		root = NULL;
	}

	void insert(T data, int value)
	{
		root = insert(data, root, value);
	}

	void remove(int sin)
	{
		root = remove(sin, root);
	}

	void display()
	{
		inorder(root);
		outfile << std::endl;
	}
	node<T>* GetRoot() {
		return root;
	}
	node<T>* Find(node<T>* node, int value)
	{
		if (node == NULL)
		{
			/* Element is not found */
			return NULL;
		}
		if (value > node->id)
		{
			/* Search in the right sub tree. */
			return Find(node->right, value);
		}
		else if (value < node->id)
		{
			/* Search in the left sub tree. */
			return Find(node->left, value);
		}
		else
		{
			/* Element Found */
			return node;
		}
	}
};
#endif //_AVLTREE_H_


