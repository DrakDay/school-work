

#include <stdio.h>
#include <unistd.h> 
#include "sem.h"

#define true 1
#define false 0

#define METHOD_1 1
#define METHOD_2 2

#define NUM_RESOURCES 1 
#define BUFFER_SIZE 5
#define SLEEP_TIME 1 


// Method 1 stuff - Multithreading with global var
void Method_1();
int global = 0;
struct Semaphore * s;
void func1();
void func2();
void func3();

// Method 2 stuff - Producer/Consumer
void Method_2();
int buffer[BUFFER_SIZE];
int in, out = 0;
struct Semaphore * full;
struct Semaphore * empty;
struct Semaphore * mutexC;
struct Semaphore * mutexP;
void producer1();
void producer2();
void consumer1();
void consumer2();

// Other method forward declarations
void printbuffer();
void error(int error_message);
int isValidInput(int num);

int main()
{
	runQ = initQueue();

	printf("\n\n");
	printf("Method 1: Each thread is an infinite loop, and has a critical section using a mutex semaphore. The thread gets into the CS, prints values of global and local variables (like proj1), sleeps and exists the CS. Then it prints a message and sleeps and then repeats. \n");
	printf("Method 2: Write a producer consumer solution, using the code given in class (see notes). Run 2 producers and 2 consumers. You will have to work out some details. If you choose to do this you really should do method 1 first. Also, doing this will make it easier for you to do project 4. \n");
	printf("Which method would you like to perform? (type '1' or '2') \n");

	int c = getchar() - 48; 
	if (c != 1 && c != 2) {
		printf("invlaid input, program terminates");
		exit(1);
	}

	switch (c)
	{
	case METHOD_1:
		s = InitSem(1);
		Method_1();
		break;
	case METHOD_2:
		full = InitSem(0);
		empty = InitSem(BUFFER_SIZE);
		mutexP = InitSem(1);
		mutexC = InitSem(1);
		int i;
		for (i = 0; i < BUFFER_SIZE; i++) {
			buffer[i] = 0;
		}
		Method_2();
		break;
	default:
		break;
	}
	return 0;
}

void Method_1()
{
	printf("Method 1 starting\n\n");

	startThread(func1);
	startThread(func2);
	//startThread(func3);

	run();
}

void Method_2()
{
	printf("Method 2 starting\n\n");

	startThread(producer1);
	startThread(producer2);
	startThread(consumer1);
	startThread(consumer2);

	run();
}

void func1()
{
	int local = 0;
	while (true)
	{
		
		P(s); 
		global++;
		local++;
		printf("ping\n");
		//printf("Function 1: global -> %d  local -> %d \n", global, local);
		sleep(SLEEP_TIME);
		V(s); 
	}
}

void func2()
{
	int local = 0;
	while (true)
	{
		P(s); 
		global++;
		local++;
		printf("pong\n");
		//printf("Function 2: global -> %d  local -> %d \n", global, local);
		sleep(SLEEP_TIME);
		V(s); 
	}
};

void func3()
{
	int local = 0;
	while (true)
	{
		P(s);
		global++;
		local++;
		printf("Function 3: global -> %d  local -> %d \n", global, local);
		sleep(SLEEP_TIME);
		V(s);
	}
};

void producer1()
{
	while (true)
	{
		P(empty);
		P(mutexP); 

		buffer[in] = 1;
		in = (in + 1) % BUFFER_SIZE;

		printf("Producer 1: added   \t");
		printbuffer();
		sleep(SLEEP_TIME);

		V(mutexP); 
		V(full);
	}
}

void producer2()
{
	while (true)
	{
		P(empty);
		P(mutexP); 

		buffer[in] = 1;
		in = (in + 1) % BUFFER_SIZE;

		printf("Producer 2: added   \t");
		printbuffer();
		sleep(SLEEP_TIME);

		V(mutexP); 
		V(full);
	}
}

void consumer1()
{
	while (true)
	{
		P(full);
		P(mutexC); 

		buffer[out] = 0;
		out = (out + 1) % BUFFER_SIZE;

		printf("Consumer 1: removed \t");
		printbuffer();
		sleep(SLEEP_TIME);

		V(mutexC);
		V(empty);
	}
}

void consumer2()
{
	while (true)
	{
		P(full);
		P(mutexC); 

		buffer[out] = 0;
		out = (out + 1) % BUFFER_SIZE;

		printf("Consumer 2: removed \t");
		printbuffer();
		sleep(SLEEP_TIME);

		V(mutexC); 
		V(empty);
	}
}

void printbuffer()
{
	int i;
	for (i = 0; i < BUFFER_SIZE; i++) {
		printf("%d\t", buffer[i]);
	}
	printf("\n");
}


