#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define _GNU_SOURCE

// double circular  linklist queue
struct qelement {
	int payload;
	struct qelement * next;
	struct qelement * prev;
};

struct Queue{
	struct qelement* head;

};

void initQueue(struct Queue * queue) {
	queue->head = NULL;
	return;
}

struct qelement* NewItem() {
	struct qelement * item = (struct qelement*) malloc(sizeof(struct qelement));
	item->next = NULL;
	item->prev = NULL;
	return item;
}

void addQueue(struct Queue * queue, struct qelement * item) {
	// check if the queue is empty of not
	if (queue->head == NULL) {
		// queue is empty
		queue->head = item;
		queue->head->prev = item;
		queue->head->next = item;
	}
	else {
		//Queue not empty, isnerset at end
		struct qelement *tail = queue->head->prev; 		
		item->next = queue->head;	
		item->prev = tail;			
		queue->head->prev = item; 	
		tail->next = item;
	}
	return;
}

struct qelement* delQueue(struct Queue * queue) {
	struct qelement * element;

	//check if queue is empty
	if (queue->head != NULL) {
		//grab the first element
		 element= queue->head;

		//check queue have single or mutiple element
		// if current item->next/preve is not itself then there are more than 1 item in the queue
		// else single element
		if ((queue->head != queue->head->prev) && (queue->head != queue->head->next)) {		
			queue->head->next->prev = queue->head->prev; 
			queue->head->prev->next = queue->head->next; 		
			queue->head = queue->head->next; 
		}
		else {
			queue->head = NULL;	
		}
		//make removed element's pinter to null
		element->next = NULL;
		element->prev = NULL;

	}
	else {	
		// Queue is empty
		return NULL;
	}
	return element;
}

void rotQueue(struct Queue * queue) {
	addQueue(queue, delQueue(queue));
	return;
}
