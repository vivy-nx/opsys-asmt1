#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
int iterations = 16;
sharedMemoryBuffer *table;

void critSection();
void quitSection();

int main() {
	bool active = true;
	printf("Producer active. Setting up shop.\n");
	table = openSharedMemory();
	printf("Opened shared memory.\n");
	initializeSharedMemory(table);
	printf("Producer's table is setup. Ready to enter the serve loop.\n");
	do {
		sem_wait(&table->mutex);
		critSection();
		iterations -= 1;
	} while (iterations != 0);
	if (iterations = 0) {
		sem_wait(&table->mutex);
		quitSection();
		sem_wait(&table->mutex);
		shm_unlink("/theSharedMemoryTable");
	};
	printf("Producer exits cleanly.\n");
	return 0;
}

void critSection() {
	printf("Producer OK to go. Throwing random values on the table.\n");
	int val = 0;
	val = rand() % 256;
	if (val % 2 == 1 && table->leftItem == 0) {
		table->leftItem = val;
		printf("Producer placed %d on the left.\n", val);
	} else if (table->rightItem == 0) {
		table->rightItem = val;
		printf("Producer placed %d on the right.\n", val);
	} else {
		printf("Table is full. Producer can take a break.\n");
	}

	sem_post(&table->mutex);
}

void quitSection() {
	printf("Producer gets tired and starts taking down the table.");
	table->leftItem = 0; // probably unnecessary to take the items off the table but i think it's cute to do
	table->rightItem = 0;
	table->quitting = true;
	sem_post(&table->mutex);
}