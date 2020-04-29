#pragma once
#include "defn.h"
#include <iostream>

using namespace std;


class BST {
	
private:
	bst * root;
	void insert(bst* node, char* s, int id, int year,char* event_type, char cz, char* czname);
	void deleteBST(bst* node);
	void inorder(bst* node, string low, string high,string filed_name);
	int getheight(bst* node);
	int lefttreeheight(bst*node);
	int righttreeheight(bst* node); 
	int countnode(bst* node);
public:
	BST();

	~BST();
	
	int value(string s);

	void deleteBST() { deleteBST(root); }

	void insert( char* s, int id, int year, char* event_type, char cz, char* czname) { insert(root, s, id,year,event_type, cz, czname); }
	
	void inorder(string low, string high,string filed_name) { inorder(root,low,high,filed_name);}

	int getheight() { return getheight(root); }

	int lefttreeheight() { return lefttreeheight(root); }

	int righttreeheight() { return righttreeheight(root); }

	int countnode() { return countnode(root); }

};
