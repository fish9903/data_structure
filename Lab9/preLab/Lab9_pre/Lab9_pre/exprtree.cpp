//--------------------------------------------------------------------
//		Lab 12									exprtree.cpp
//
//--------------------------------------------------------------------

#include "exprtree.h"
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

		if (prefix == '+' || prefix == '-' || prefix == '*' || prefix == '/') {
			buildSub(p->left);
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
		case '+': case '-': case '*': case '/':
			cout << '(';
			exprSub(p->left);
			cout << p->element;
			exprSub(p->right);
			cout << ')';
			break;
		default:
			exprSub(p->left);
			cout << p->element;
			exprSub(p->right);
		}
		/*cout << '(';
		exprSub(p->left);
		cout << p->element;
		exprSub(p->right);
		cout << ')';*/
	}
}

//--------------------------------------------------------------------

float ExprTree::evaluate() const
{
	if (root == 0)
	{
		cout << " Tree is Empty ";
		return 0;
	}
	else if (root->element != '*' && root->element != '-' && root->element != '+' && root->element != '/') {
		return root->element - '0';
	}

	float result = evaluateSub(root) - '0';
	return result;
}

float ExprTree::evaluateSub(ExprTreeNode* p) const
{
	switch (p->element) {
	case '+':
		p->element = evaluateSub(p->left) + evaluateSub(p->right) - '0';
		break;
	case '-':
		p->element = evaluateSub(p->left) - evaluateSub(p->right) + '0';
		break;
	case '*':
		p->element = (evaluateSub(p->left) - '0') * (evaluateSub(p->right) - '0') + '0';
		break;
	case '/':
		p->element = (evaluateSub(p->left) - '0') / (evaluateSub(p->right) - '0') + '0';
		break;
	default:
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

void ExprTree::showSub(ExprTreeNode* p, int level) const
{
	int j;

	if (p != 0)
	{
		showSub(p->right, level + 1);
		for (j = 0; j < level; j++)
			cout << "\t";
		cout << " " << p->element;
		if ((p->left != 0) &&
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);
	}
}