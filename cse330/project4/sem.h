#pragma once
#include "threads.h"

struct Semaphore {
	int value;
	struct Queue * tcb_queue;
};

struct Semaphore * InitSem(int value) {
	struct Semaphore * sem = (struct Semaphore *) malloc(sizeof(struct Semaphore));
	sem->value = value;
	sem->tcb_queue = initQueue();
	return sem;
}

void P(struct Semaphore * sem) {
	sem->value--;
	if (sem->value < 0) {
		TCB_t * tcb = delQueue(runQ);
		addQueue(sem->tcb_queue, tcb);
		swapcontext(&tcb->context, &runQ->head->context);
	}
}

void V(struct Semaphore * sem) {
	sem->value++;
	if (sem->value <= 0) {
		TCB_t * tcb = delQueue(sem->tcb_queue);
		addQueue(runQ, tcb);
	}
	yield();
}
