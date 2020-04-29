//cse 300 project 2
//name: zhi li hu
#include "threads.h"
#include <stdio.h>

#define true 1
int global = 0;

void f1(void) {
	int local = 0;
	while (true)
	{
		printf("Func1 -> local: %d\n", local);
		printf("Func1 -> global: %d\n\n", global);
		local++;
		global++;
		sleep(1); 
		yield();
	}
}

void f2(void) {
	int local = 0;
	while (true)
	{
		printf("Func2 -> local: %d\n", local);
		printf("Func2 -> global: %d\n\n", global);
		local++;
		global++;
		sleep(1); 
		yield();
	}
}

void f3(void) {
	int local = 0;
	while (true)
	{
		printf("Func3 -> local: %d\n", local);
		printf("Func3 -> global: %d\n\n", global);
		local++;
		global++;
		sleep(1); 
		yield();
	}
}

int main() {
	runQ = (struct Queue*) malloc(sizeof(struct  Queue));

	initQueue(runQ);
	printf("Initilazing Threads\n");
	startThread(f1);
	startThread(f2);
	startThread(f3);
	printf("program running\n");
	run();

	return 0;
}