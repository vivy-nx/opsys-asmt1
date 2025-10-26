#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
sharedMemoryBuffer *table;
int left = 0;
int right = 0;
bool waiting = false;
bool active = false;

void critSection();

int main() {
	// sleep(1);
	bool active = true;
	printf("Consumer is awake and would love to look at tables.\n");
	sharedMemoryBuffer *table = openSharedMemory();
	sem_wait(&table->mutex);
	do {
		sem_wait(&table->mutex);
		critSection();
		// if (waiting == true) { sleep(1); };
		// waiting = false;
	} while (active == true);
	printf("Consumer exits cleanly.\n");
	return 0;
}

void critSection() {
	printf("Consumer is looking at the table.\n");
	if (table->quitting == true) {
		printf("Consumer leaves since this table is being taken down.\n");
		active = false;
	} else {
		// take everything from the table!
		int left = table->leftItem;
		int right = table->rightItem;
		if (left == 0 && right == 0) {
			printf("Consumer found nothing on the table, and will come back around in a sec.\n");
			// waiting = true;
		} else {
			printf("Consumer found items on the table!\n");
			if (left != 0) { printf("%d", left); }
			if (left != 0 && right != 0) { printf(" and "); }
			if (right != 0) { printf("%d\n", right); }
			// taking things from the table means the table doesn't have them anymore.
			table->leftItem = 0;
			table->rightItem = 0;
			// now that you've looked at them, you don't have them anymore either!
			left = 0;
			right = 0;
			printf("Consumer leaves satisfied with what it found on the table.\n");
		}
	}
	sem_post(&table->mutex);
}