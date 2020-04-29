#pragma once
#include "q.h"

struct Queue * runQ;

void startThread(void(*function) (void)) {
	TCB_t *temp = NewItem();
	void *stack = (void *)malloc(8192);
	init_TCB(temp, function, stack, 8192);
	addQueue(runQ, temp);
}

void run()
{
	ucontext_t parent;  
	getcontext(&parent);    
	swapcontext(&parent, &runQ->head->context); 
}

void yield()
{
	ucontext_t current_context; 
	getcontext(&current_context);   
	runQ->head->context = current_context;  
	rotQueue(runQ);  
	ucontext_t new_context = runQ->head->context;   
	swapcontext(&current_context, &new_context);    
}
