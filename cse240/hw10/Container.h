#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "book.h"

class Container {
public:
	Book *book;
	Container *next;
	Container();			// constructor
};

#endif // _CONTAINER_H_