#include "sem.h"
#include <stdio.h>
#include <unistd.h> 
// option 1
void child1();
void child2();
void child3();
void parent();

struct Semaphore *s;
struct Semaphore *c1;
struct Semaphore *c2;
struct Semaphore *c3;


int arr[3] = { 0,0,0 };

int main() {

	runQ = initQueue();
	s = InitSem(1);
	c1 = InitSem(0);
	c2 = InitSem(0);
	c3 = InitSem(0);
	startThread(parent);
	startThread(child1);
	startThread(child2);
	startThread(child3);
	run();

	
	return 0;
}

void parent() {
	while (1) {
		P(s);
		printf("arr: %d, %d, %d \n", arr[0], arr[1], arr[2]);
		sleep(1);
		V(c1);
	}
}
void child1() {
	while (1) {
		P(c1);
		printf("child 1 now is adding 1 to arr[0]\n");
		arr[0] += 1;
		sleep(1);
		V(c2);
	}
}
void child2() {
	while (1) {
		P(c2);
		printf("child 2 now is adding 1 to arr[1]\n");
		arr[1] += 1;
		sleep(1);
		V(c3);
	}
}
void child3() {
	while (1) {
		P(c3);
		printf("child 3 now is adding 1 to arr[2]\n");
		arr[2] += 1;
		sleep(1);
		V(s);
	}
}
