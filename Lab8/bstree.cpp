#include <iostream>
#include <algorithm>
//--------------------------------------------------------------------
//
//  Laboratory 11                                           bstree.h
//
//  Class declarations for the linked implementation of the Binary
//  Search Tree ADT -- including the recursive partners of the
//  public member functions
//
//--------------------------------------------------------------------

using namespace std;

template < class TE, class KF > class BSTree;
template < class TE, class KF > class BSTreeNode;

template < class TE, class KF >
class BSTreeNode             // Facilitator class for the BSTree class
{
private:

	// Constructor
	BSTreeNode(const TE& elem,
		BSTreeNode* leftPtr, BSTreeNode* rightPtr);

	// Data members
	TE element;          // Binary search tree element
	BSTreeNode* left,    // Pointer to the left child
		* right;   // Pointer to the right child

	friend class BSTree<TE, KF>;
};

//--------------------------------------------------------------------

template < class TE, class KF >    // TE : tree element
class BSTree                       // KF : key field
{
public:

	// Constructor
	BSTree();

	// Destructor
	~BSTree();

	// Binary search tree manipulation operations
	void insert(const TE& newElement); // Insert element

	bool retrieve(KF searchKey, TE& searchElement) const;
	// Retrieve element
	bool remove(KF deleteKey);                  // Remove element
	void writeKeys() const;                      // Output keys
	void clear();                                // Clear tree

	// Binary search tree status operations
	bool isEmpty() const;                           // Tree is empty
	bool isFull() const;                            // Tree is full

	// Output the tree structure -- used in testing/debugging
	void showStructure() const;

	// In-lab operations
	int getHeight() const;

private:

	// Recursive partners of the public member functions -- insert
	// prototypes of these functions here.
	void insertSub(BSTreeNode<TE, KF>*& p, const TE& newElement);
	bool retrieveSub(BSTreeNode<TE, KF>* p, KF searchKey,
		TE& searchElement) const;
	bool removeSub(BSTreeNode<TE, KF>*& p, KF deleteKey);
	void cutRightmost(BSTreeNode<TE, KF>*& r,
		BSTreeNode<TE, KF>*& delPtr);
	void writeKeysSub(BSTreeNode<TE, KF>* p) const;
	void clearSub(BSTreeNode<TE, KF>* p);
	void showSub(BSTreeNode<TE, KF>* p, int level) const;

	// In-lab operations
	int getHeightSub(BSTreeNode<TE, KF>* p) const;

	// Data member
	BSTreeNode<TE, KF>* root;   // Pointer to the root node
};

using namespace std;

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
	clear();
	delete root;
}

// Insert

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

//--------------------------------------------------------------------

// Retrieve 

template < class TE, class KF >
bool BSTree<TE, KF>::retrieve(KF searchKey, TE& searchElement) const
{
	if (retrieveSub(root, searchKey, searchElement)) {
		return true;
	}
	else
		return false;
}

template < class TE, class KF >
bool BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF>* p, KF searchKey, TE& searchElement) const
{
	if (p == NULL) {
		return false;
	}
	else if (searchKey < p->element.key())
		retrieveSub(p->left, searchKey, searchElement);
	else if(searchKey > p->element.key()){
		retrieveSub(p->right, searchKey, searchElement);
	}
	else {
		searchElement = p->element;
		return true;
	}
}

//--------------------------------------------------------------------

// Remove

template < class TE, class KF >
bool BSTree<TE, KF>::remove(KF deleteKey)
{
	if (removeSub(root, deleteKey)) {
		return true;
	}
	else
		return false;
}

template < class TE, class KF >
bool BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF>*& p, KF deleteKey)
{
	BSTreeNode<TE, KF>* tempPtr;
	tempPtr = p;
	if (p == NULL)
		return false;
	else if (deleteKey < p->element.key())
		removeSub(p->left, deleteKey);
	else if (deleteKey > p->element.key())
		removeSub(p->right, deleteKey);
	else {
		if (p->left == NULL) {
			p = p->right;
			delete tempPtr;
		}
		else if (p->right == NULL) {
			p = p->left;
			delete tempPtr;
		}
		else
			cutRightmost(p, tempPtr);
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF>*& r, BSTreeNode<TE, KF>*& delPtr)
{
	delPtr = delPtr->left;
	while (delPtr->right != NULL)
		delPtr = delPtr->right;

	r->element.setKey(delPtr->element.key());
	removeSub(r->left, delPtr->element.key());
}

//--------------------------------------------------------------------

// Write Keys

template < class TE, class KF >
void BSTree<TE, KF>::writeKeys() const
{
	writeKeysSub(root);
}

template < class TE, class KF >
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF>* p) const
{
	if(p)
	{
		writeKeysSub(p->left);
		cout << p->element.key() << " ";
		writeKeysSub(p->right);
	}
}

//--------------------------------------------------------------------

// Clear

template < class TE, class KF >
void BSTree<TE, KF>::clear()
{
	clearSub(root);
}

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF>* p)
{
	if (p == NULL)
	{
		return;
	}
	else {
		remove(p->element.key());
		clearSub(root);
	}
}

//--------------------------------------------------------------------

// Empty / Full

template < class TE, class KF >
bool BSTree<TE, KF>::isEmpty() const
{
	if (root == NULL)
		return true;
	else 
		return false;
}

template < class TE, class KF >
bool BSTree<TE, KF>::isFull() const
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

//--------------------------------------------------------------------

// Show Structure

template < class TE, class KF >
void BSTree<TE, KF>::showStructure() const

{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::showSub(BSTreeNode<TE, KF>* p,
	int level) const

{
	int j;   // Loop counter

	if (p != 0)
	{
		showSub(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->element.key();   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);          // Output left subtree
	}
}

// In-lab operations
template <class TE, class KF>
int BSTree<TE, KF>::getHeight() const
{
	//in-lab
	if (root == NULL)
		return 0;
	else {
		return getHeightSub(root);
	}
		
}

template <class TE, class KF>
int BSTree<TE, KF>::getHeightSub(BSTreeNode<TE, KF>* p) const
{
	//in-lab
	if (p)
		return max(getHeightSub(p->left), getHeightSub(p->right)) + 1;
	else
		return 0;
}