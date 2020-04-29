#include "BST.h"
#include <string>
#include <string.h>


BST::BST() {
	root = NULL;
}

BST::~BST() {
	deleteBST();
}

void BST::deleteBST(bst * node) {
	if (!node)
		return;

	bst * curTreeNode = node;
	bst * leftTreeNode = node->left;
	bst * rightTreeNode = node->right;
	delete(curTreeNode);
	deleteBST(leftTreeNode);
	deleteBST(rightTreeNode);
}

void BST::insert(bst* node, char* s, int id,int year, char* event_type,char cz, char* czname) {
	if (!node) {
		node = new bst();
		node->s = s; node->event_id = id; node->year = year;
		node->event_type = event_type;  node->cz_type = cz; node->cz_name = czname;
		node->left = NULL;
		node->right = NULL;
		root = node;
		
	}

	else {
		const char *str = s;
		const char *str2 = node->s;
		if (strcmp(str,str2)==0) {
			if (id < node->event_id) {
				if (!node->left) {
					bst* tempnode = new bst();
					tempnode->s = s; tempnode->event_id = id; tempnode->year = year;
					tempnode->event_type = event_type; tempnode->cz_type = cz; tempnode->cz_name = czname;
					tempnode->left = NULL;
					tempnode->right = NULL;
					node->left = tempnode;
				}
				else {
					insert(node->left, s, id, year, event_type, cz, czname);
				}
			}
			else {
				if (!node->right) {
					bst* tempnode = new bst();
					tempnode->s = s; tempnode->event_id = id; tempnode->year = year;
					tempnode->event_type = event_type; tempnode->cz_type = cz; tempnode->cz_name = czname;
					tempnode->left = NULL;
					tempnode->right = NULL;
					node->right = tempnode;
				}
				else {
					insert(node->right, s, id, year, event_type, cz, czname);
				}
			}
		}
		else if (strcmp(str,str2)<0) {
			if (!node->left) {
				bst* tempnode = new bst();
				tempnode->s = s; tempnode->event_id = id; tempnode->year = year;
				tempnode->event_type = event_type; tempnode->cz_type = cz; tempnode->cz_name = czname;
				tempnode->left = NULL;
				tempnode->right = NULL;
				node->left = tempnode;
			}
			else {
				insert(node->left, s, id,year,event_type,cz,czname);
			}
		}
		else {
			if (!node->right) {
				bst* tempnode = new bst();
				tempnode->s = s; tempnode->event_id = id; tempnode->year = year;
				tempnode->event_type = event_type; tempnode->cz_type = cz; tempnode->cz_name = czname;
				tempnode->left = NULL;
				tempnode->right = NULL;
				node->right = tempnode;
			}
			else {
				insert(node->right, s, id, year,event_type, cz, czname);
			}
		}
	}
}

int BST::value(string s) {

	return int(s[0]);
}

void BST::inorder(bst* node, string low, string high, string filed_name) {
	if (!node)
		return;

	inorder(node->left, low, high, filed_name);
	const char *temp = node->s;
	const char *low1 = low.c_str();
	const char *high1 = high.c_str();
	if (filed_name == "state" || filed_name == "motn_name")
	{
		if (low == high) {
			if (value(node->s) == value(low)) {
				cout << "state/month name: " << node->s << endl
					<< "event id: " << node->event_id << endl
					<< "year: " << node->year << endl
					<< "event type: " << node->event_type << endl
					<< "cz type: " << node->cz_type << endl
					<< "cz name: " << node->cz_name << endl
					<< endl;
			}
		}
		else if (strcmp(temp, low1) >= 0 && strcmp(temp, high1) <= 0) {
			cout << "state/month name: " << node->s << endl
				<< "event id: " << node->event_id << endl
				<< "year: " << node->year << endl
				<< "event type: " << node->event_type << endl
				<< "cz tyoe: " << node->cz_type << endl
				<< "cz name: " << node->cz_name << endl << endl;
		}
	}
		else {
			if (low == high) {
				if (node->s == low) {
					cout << "state/month name: " << node->s << endl
						<< "event id: " << node->event_id << endl
						<< "year: " << node->year << endl
						<< "event type: " << node->event_type << endl
						<< "cz type: " << node->cz_type << endl
						<< "cz name: " << node->cz_name << endl
						<< endl;
				}
			}
			else if (strcmp(temp, low1) >= 0 && strcmp(temp, high1) <= 0) {
				cout << "state/month name: " << node->s << endl
					<< "event id: " << node->event_id << endl
					<< "year: " << node->year << endl
					<< "event type: " << node->event_type << endl
					<< "cz tyoe: " << node->cz_type << endl
					<< "cz name: " << node->cz_name << endl << endl;
			}
		}
		inorder(node->right, low, high, filed_name);
	}


int BST::getheight(bst* node) {
	if (!node) {
		return 0;
	}
	int lheight = getheight(node->left);
	int rheight = getheight(node->right);

	if (lheight > rheight)
		return 1 + lheight;

	return 1 + rheight;
}

int BST::lefttreeheight(bst* node) {
	return getheight(node->left);
}

int BST::righttreeheight(bst* node) {
	return getheight(node->right);
}

int BST::countnode(bst* node) {
	if (node == NULL) {
		return 0;
	}
	return 1 + countnode(node->left) + countnode(node->right);
}
