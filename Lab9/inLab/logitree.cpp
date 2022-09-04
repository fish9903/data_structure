//--------------------------------------------------------------------
//		Lab 12									logitree.cpp
//
//--------------------------------------------------------------------

#include "logitree.h"
#include <iostream>

using namespace std;
//--------------------------------------------------------------------

ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr)
{
	element = elem;
	left = leftPtr;
	right = rightPtr;
}

//--------------------------------------------------------------------

ExprTree::ExprTree()
{
	root = NULL;
}

ExprTree::~ExprTree()
{
	clear();
	root = NULL;
}

//--------------------------------------------------------------------

void ExprTree::build()
{
	buildSub(root);
}

void ExprTree::buildSub(ExprTreeNode*& p)
{
	char prefix;
	cin >> prefix;
	ExprTreeNode* t;
	while (prefix != '\n') {
		t = new ExprTreeNode(prefix, NULL, NULL);
		p = t;

		// +:or, *:and, -:not
		if (prefix == '+' || prefix == '*') {
			buildSub(p->left);
			buildSub(p->right);
			return;
		}
		else if (prefix == '-') {
			buildSub(p->right);
			return;
		}
		else
			return;
	}
}

//--------------------------------------------------------------------

void ExprTree::expression() const
{
	exprSub(root);
}

void ExprTree::exprSub(ExprTreeNode* p) const
{
	if (p != 0) {
		switch (p->element) {
		case '+': case '*':
			cout << '(';
			exprSub(p->left);
			cout << p->element;
			exprSub(p->right);
			cout << ')';
			break;
		case '-':
			cout << '(';
			exprSub(p->left);
			cout << "!";
			exprSub(p->right);
			cout << ')';
			break;
		default:
			exprSub(p->left);
			cout << p->element;
			exprSub(p->right);
		}
	}
}

//--------------------------------------------------------------------

int ExprTree::evaluate() const
{
	if (root == 0)
	{
		cout << " Tree is Empty ";
		return 0;
	}
	else if (root->element != '*' && root->element != '-' && root->element != '+') {
		return root->element - '0';
	}

	return evaluateSub(root);
}

int ExprTree::evaluateSub(ExprTreeNode* p) const
{
	switch (p->element) {
	case '+':
		p->element = evaluateSub(p->left) || evaluateSub(p->right);
		break;
	case '*':
		p->element = evaluateSub(p->left) && evaluateSub(p->right);
		break;
	case '-':
		p->element = !evaluateSub(p->right);
		break;
	}

	return p->element;
}

//--------------------------------------------------------------------

void ExprTree::clear()
{
	clearSub(root);
	root = NULL;
}

void ExprTree::clearSub(ExprTreeNode* p)
{
	if (p != NULL) {
		clearSub(p->left);
		clearSub(p->right);
		delete p;
	}
}

//--------------------------------------------------------------------

void ExprTree::showStructure() const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ExprTree::showSub(ExprTreeNode* p, int level) const

// Recursive partner of the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		showSub(p->right, level + 1);        // Output right subtree
		for (j = 0; j < level; j++)   // Tab over to level
			cout << "\t";
		cout << " " << p->element;       // Output data item
		if ((p->left != 0) &&          // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);         // Output left subtree
	}
}