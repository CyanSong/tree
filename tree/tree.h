#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<exception>



template <class elemType>
class BinaryTree {
private:
	friend class chTree;
	struct node {
		node* leftChild;
		node* rightChild;
		//node* father;
		elemType data;
		node(const elemType& elem, node* left = NULL, node* right = NULL) :data(elem), \
			leftChild(left), rightChild(right) {}
		node() = default;
	};
	struct clearTask {
		node * clearNode;
		bool ifClear;
		clearTask(node * a, bool b) :clearNode(a), ifClear(b) {}
	};
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

class chTree {
private:
	struct character {
		enum Type { ADD, DE, CHENG, CHU, CHENGF, DATA };
		Type dataType;
		int num;
		int rank;
		character(Type a, int r, int b = 0) :dataType(a), rank(r), num(b) {}
		character() = default;
	};

	BinaryTree<character> Tree;
	static	inline  bool isNumber(char a) { return a >= '0'&&a <= '9'; }
	int getAnswer(BinaryTree<character>::node*);
public:
	chTree(std::string );
	int getAnswer();
};
inline int chTree::getAnswer(BinaryTree<character>::node *p)
{
	if (p->data.dataType == character::DATA)return p->data.num;
	else{
		switch (p->data.dataType) {
		case character::ADD:return getAnswer(p->leftChild) + getAnswer(p->rightChild);
		case character::DE:return getAnswer(p->leftChild) - getAnswer(p->rightChild);
		case character::CHENG:return getAnswer(p->leftChild) * getAnswer(p->rightChild);
		case character::CHU:return getAnswer(p->leftChild) / getAnswer(p->rightChild);
		case character::CHENGF:return pow(getAnswer(p->leftChild) ,getAnswer(p->rightChild));
		}
	}
}
chTree::chTree(std::string expression) {
	int numKuo = 0;
	bool isFull = false;
	for (auto i = expression.cbegin();i != expression.cend();++i)
	{
		if (*i == ' ')continue;
		switch (*i) {
		case '^':case '/':case '*':case '-':case '+':
			character::Type a;
			int tmpRank;
			switch (*i) {
			case '^':a = character::CHENGF;tmpRank = numKuo * 4 + 1;break;
			case '*':a = character::CHENG;tmpRank = numKuo * 4 + 1;break;
			case '/':a = character::CHU;tmpRank = numKuo * 4 + 1;break;
			case '+':a = character::ADD;tmpRank = numKuo * 4 ;break;
			case '-':a = character::DE;tmpRank = numKuo * 4;break;
			}
			character tmp;
			tmp=character(a, tmpRank);
			BinaryTree<character>::node * newNode;
			newNode= new BinaryTree<character>::node(tmp);
			if(isFull){
				if (Tree.root->data.rank >= tmp.rank) {
					newNode->leftChild = Tree.root;
					Tree.root = newNode;
				}
				else {
					auto tmpPar = Tree.root;
					while (tmpPar->rightChild->data.rank < tmp.rank) { tmpPar = tmpPar->rightChild; }
					newNode->leftChild = tmpPar->rightChild;
					tmpPar->rightChild = newNode;
				}
				isFull = !isFull;
			}
			else throw std::exception("连续的符号！");
			break;
		case '(':
			numKuo++;
			break;
		case ')':
			if (numKuo)numKuo--;
			else throw std::exception("右括号多了！");
			break;
		default:
			if (!isNumber(*i))throw std::exception("未声明符号！");
			if (isFull) throw std::exception("数字中间有空格！");
			
			int result;
			result = *i-'0';
			while ((i+1)!=expression.cend()&&isNumber(*(i + 1))) {
				i++;
				result = result * 10 + *i-'0';
			 }

			BinaryTree<character>::node * tmpNode2;
			tmpNode2 = Tree.root;
			if(!tmpNode2)Tree.root=new BinaryTree<character>::node(character(character::DATA, numKuo * 4 + 2, result));
			else {
				while (tmpNode2->rightChild) {
					tmpNode2 = tmpNode2->rightChild;
				}
				tmpNode2->rightChild=new BinaryTree<character>::node(character(character::DATA, numKuo * 4 + 2, result));
			}
			isFull = !isFull;
		}
	}
	if (numKuo)throw std::exception("左括号多了！");
}

inline int chTree::getAnswer()
{
	return getAnswer(Tree.root);
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
	std::stack<clearTask> task;
	task.push(clearTask(root, false));
	while (!task.empty()) {
		clearTask oneTask = task.top();
		task.pop();
		if (oneTask.ifClear)delete oneTask.clearNode;
		else {
			task.push(clearTask(oneTask.clearNode, true));
			if((oneTask.clearNode)->leftChild)task.push(clearTask(oneTask.clearNode->leftChild, false));
			if (oneTask.clearNode->rightChild)task.push(clearTask(oneTask.clearNode->rightChild, false));
		}
	}
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
