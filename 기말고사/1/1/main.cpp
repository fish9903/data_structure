#include <iostream>
#include <string>
using namespace std;

template < class TE, class KF > class BSTree;
template < class TE, class KF > class BSTreeNode;

template < class TE, class KF >
class BSTreeNode
{
private:
	BSTreeNode(const TE& elem, BSTreeNode* leftPtr, BSTreeNode* rightPtr);
	TE element;
	BSTreeNode* left, * right;

	friend class BSTree<TE, KF>;
};

template < class TE, class KF > 
class BSTree
{
public:

	BSTree();

	~BSTree();

	void insert(const TE& newElement);                                                  
	bool isEmpty();          
	bool isFull();     
	void clear();
	void del();

private:
	void insertSub(BSTreeNode<TE, KF>*& p, const TE& newElement);
	void clearSub(BSTreeNode<TE, KF>* p);
	void delSub(BSTreeNode<TE, KF>* p);

	BSTreeNode<TE, KF>* root;
};

template < class TE, class KF >
BSTreeNode<TE, KF>::BSTreeNode(const TE& elem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	this->element = elem;
	this->left = leftPtr;
	this->right = rightPtr;
}

template < class TE, class KF >
BSTree<TE, KF>::BSTree()
{
	root = NULL;
}

template < class TE, class KF >
BSTree<TE, KF>::~BSTree()
{
	delete root;
}

template < class TE, class KF >
void BSTree<TE, KF>::insert(const TE& newElement)
{
	if (isFull())
	{
		cout << "Tree is Full" << endl;
		return;
	}
	insertSub(root, newElement);
}

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF>*& p, const TE& newElement)
{
	if (p == NULL) {
		p = new BSTreeNode<TE, KF>(newElement, NULL, NULL);
	}
	else if (newElement.key() < p->element.key())
		insertSub(p->left, newElement);
	else
		insertSub(p->right, newElement);
}

template < class TE, class KF >
bool BSTree<TE, KF>::isEmpty() 
{
	if (root == NULL)
		return true;
	else
		return false;
}

template < class TE, class KF >
bool BSTree<TE, KF>::isFull() 
{
	BSTreeNode<TE, KF>* n_Node = new BSTreeNode<TE, KF>(TE(), NULL, NULL);
	if (n_Node == NULL) {
		cout << "The List is Full" << endl;
		return true;
	}
	else {
		delete n_Node;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::clear()
{
	clearSub(root);
}

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF>* p)
{
	if (p->left == NULL && p->right == NULL)
	{
		delete p;
	}
	else {
		clearSub(p->left);
		clearSub(p->right);
		
	}
}

template<class TE, class KF>
void BSTree<TE, KF>::del()
{
	delSub(root);
}

template<class TE, class KF>
void BSTree<TE, KF>::delSub(BSTreeNode<TE, KF>* p)
{
	if (p->left == NULL && p->right == NULL) {
		cout << p->element.key();
		delete p;
	}
	else {
		if (p != NULL) {
			if (p->left != NULL) {
				delSub(p->left);
			}
			if (p->right != NULL) {
				delSub(p->right);
			}
		}		
	}
}

class Data
{
public:
	void setKey(char newKey)
	{
		keyField = newKey;
	} 

	char key() const
	{
		return keyField;
	} 

private:

	char keyField;       
};

int main() {
	BSTree<Data, char> Tree;
	Data data;             
	string inputKey;                  

	while (1) {
		cin >> inputKey;
		if (inputKey == "$")
			break;
		else if (inputKey == "*")
			Tree.clear();

		for (int i = 0; i < inputKey.size(); i++) {
			data.setKey(inputKey[i]);
			Tree.insert(data);
		}
		while (!Tree.isEmpty()) {
			Tree.del();
			cout << endl;
		}		
	}
	

	return 0;
}