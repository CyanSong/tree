#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<vector>



template <class elemType>
class BinaryTree {
private:
	struct node {
		node* leftChild;
		node* rightChild;
		//node* father;
		elemType data;
		node(const elemType& elem, node* left = NULL, node* right = NULL) :data(elem), \
			leftChild(left), rightChild(right) {}
		node() = default;
	};
	void clear(node* r);
	node *root = NULL;
public:
	BinaryTree() = default;
	//BinaryTree(const node& rootNode):root(new node(rootNode)){}
	BinaryTree(const node& rootNode, BinaryTree* leftBranch = NULL, BinaryTree* rigtBranch = NULL);
	~BinaryTree() { clear(); }
	void clear();
	void preTraverse();
	//void postTraverse();
	//void midTraverse();
	inline bool isEmpty() { return root == NULL; }
	//int height();
	//int size();
	void createTree(const elemType & stopFlag);
};

//#include"tree.cpp"



template<class elemType>
void BinaryTree<elemType>::clear(node * r)
{
	if (r) {
		clear(r->leftChild);
		clear(r->rightChild);
		delete r;
	}
}

template<class elemType>
BinaryTree<elemType>::BinaryTree(const node & rootNode, BinaryTree *leftBranch, BinaryTree * rigtBranch)
{
	root = new node(rootNode);
	root->left = leftBranch->root;
	root->right = rightBranch->root;
	leftBranch->root = rightBranch->root = NULL;
}

template<class elemType>
void BinaryTree<elemType>::clear()
{
	clear(root);
}

template<class elemType>
void BinaryTree<elemType>::preTraverse()
{
	if (!isEmpty()) {
		std::stack<node*>task;
		task.push(root);
		while (!task.empty()) {
			auto tmp = task.top();
			task.pop();
			std::cout << tmp->data;
			if (tmp->rightChild) { task.push(tmp->rightChild); }
			if (tmp->leftChild) { task.push(tmp->leftChild); }
		}
	}
}

template<class elemType>
void BinaryTree<elemType>::createTree(const elemType & stopFlag)
{

	if (isEmpty()) {
		std::cout << "Please input the root node.";
		elemType tmp;
		std::cin >> tmp;
		if (tmp != stopFlag) {
			std::queue<node*> task;
			root = new node(tmp);
			task.push(root);
			while (!task.empty()) {
				auto tmp = task.front();
				task.pop();
				elemType leftElem, rightElem;
				std::cout << "left";std::cin >> leftElem;
				std::cout << "right";std::cin >> rightElem;
				if (leftElem != stopFlag) { tmp->leftChild = new node(leftElem); task.push(tmp->leftChild); }
				if (rightElem != stopFlag) { tmp->rightChild = new node(rightElem); task.push(tmp->rightChild); }
			}
		}
	}
}
