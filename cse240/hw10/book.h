#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>
using namespace std;

enum libraryType { hayden = 0, noble };	// definition of libraryType

class Book {
private:
	string name; // private data members
	int copies;
	libraryType lib;

public:
	Book(string bookName, int noOfCopies, libraryType libType); // constructor

	// accessor methods
	string getName();
	int getCopies();
	libraryType getLibraryType();

	virtual void displayBook()
	{}

	// Q3a: Declare Friend Function changeNoOfCopies()  (1 point)
	// Declare a friend function named changeNoOfCopies() which has 2 parameters and no return value.
	// The first parameter is a pointer to Book class, and the second is an integer which is the new number of copies.
	// You need to define this function in hw10.cpp and call this function in case 'c' of executeAction() in hw10.cpp file

	friend void changeNoOfCopies(Book* newbook, int newcopy);

	
};

#endif // _BOOK_H_