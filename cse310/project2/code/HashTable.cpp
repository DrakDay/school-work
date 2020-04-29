#include "HashTable.h"



// constructor
HashTable::HashTable(int n) {
	this->SIZE = n;
	htable = new hash_table_entry*[SIZE];
	for (int i = 0; i < SIZE; i++)
		htable[i] = NULL;
}

//destructor
HashTable:: ~HashTable(){
	for (int i = 0; i < SIZE; ++i)
	{
		hash_table_entry* entry = htable[i];
		while (entry != NULL)
		{
			hash_table_entry* prev = entry;
			entry = entry->next;
			delete prev;
		}
	}
	delete[] htable;
}

//hash function
int HashTable::HashFunc(int key) {
	return key % SIZE;
}

// insertion struct of hash table entry at beginning
void HashTable::insert(int key,int year, int index) {

	int hash_val = HashFunc(key);

	hash_table_entry* entry = new hash_table_entry();
	entry->event_id = key;
	entry->year = year;
	entry->event_index = index;

	if (htable[hash_val] == NULL) {
		htable[hash_val] = entry;
		htable[hash_val]->next = NULL;
	}
	else {
		hash_table_entry *temp = htable[hash_val]->next;
		htable[hash_val]->next = entry;
		entry->next = temp;
	}

}

int HashTable::index(int key) {

	int hash_val = HashFunc(key);
	hash_table_entry* entry = htable[hash_val];

	while (entry != NULL)
	{
		if (entry->event_id == key)
		{
			return entry->event_index;
		}
		entry = entry->next;
	}
	return -1;
}



void HashTable::displayHash() {

	int max = 0;
	for (int i = 0; i < SIZE; i++) {
		int length = 0;
		hash_table_entry* entry = htable[i];
		while (entry != NULL) {
			length++;
			entry = entry->next;
		}
		if (length > max)
			max = length;
	}
	int sum = 0;
	int *arr = new int[max+1];
	for (int i = 0; i < max+1; i++) {
		arr[i] = 0;
	}

	for (int i = 0; i < SIZE; i++) {
		int length = 0;
		hash_table_entry* entry = htable[i];
		while (entry != NULL) {
		//	cout << " -- > " << entry->event_id;
			sum++;
			length++;
			entry = entry->next;
		}
		arr[length] = arr[length] + 1;
	}
	for (int i = 0; i < max+1; i++) {
		cout << "chaning length " << i << "  is :  " << arr[i] << endl;
		}
	cout << "the load factor is: " << double(sum) /double( SIZE) << endl;
	delete[] arr;
}
