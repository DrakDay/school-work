#pragma once
#include <iostream>
#include "defn.h"
using namespace std;


class HashTable {
	int SIZE;
private:
	struct hash_table_entry** htable;
public:
	//constructor
	HashTable(int N);

	//destructor
	~HashTable();

	//hash function
	int HashFunc(int key);

	//insert a struct of hash table entry into hash table
	void insert(int key,int year, int index);

	// this return the index 
	int index(int key);


	//display hashtable
	void displayHash();
};
