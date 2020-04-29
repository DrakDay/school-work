#include "book.h"

// definitions of Book member functions
Book::Book(string bookName, int noOfCopies, libraryType libType)
{
	name = bookName;
	copies = noOfCopies;
	lib = libType;
}

string Book::getName()
{
	return name;
}

int Book::getCopies()
{
	return copies;
}

libraryType Book::getLibraryType()
{
	return lib;
}