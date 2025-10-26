#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	bool quitting;
	int leftItem;
	int rightItem;
	sem_t mutex;
} sharedMemoryBuffer;

sharedMemoryBuffer *openSharedMemory() {
	int fd = shm_open("/theSharedMemoryTable", O_RDWR | O_CREAT, 0600);
	ftruncate(fd, sizeof(sharedMemoryBuffer)); // initialized empty table
	void *mem = mmap(NULL, sizeof(sharedMemoryBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (mem == NULL) {
		perror("Memory map failed here is the real error explained by computer:");
		exit(1);
	}
	sharedMemoryBuffer *table = mem;
	return table;
	//
}

void initializeSharedMemory(sharedMemoryBuffer *table) {
	if (sem_init(&table->mutex, 1, 1) < 0) perror("fml");
	table->quitting = 0;
	table->leftItem = 0;
	table->rightItem = 0;
}