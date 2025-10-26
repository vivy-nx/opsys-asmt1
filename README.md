# opsys-asmt1

C project that consists of two executables, the producer and the consumer. The producer puts integers onto a shared memory table that can hold two of them. The consumer takes these integers off the table. After a couple iterations, it quits out cleanly. They run simultaneously, and enforce mutual exclusion by way of using a semaphore to determine which one can run a critical section.

This project consists of two C files, an associated header file, and some assorted scripts to facilitate standard execution.

# Compile

To compile on Linux, simply run `build.sh`. 

Alternatively, you can run these gcc commands. They are borrowed directly from the information about this assignment from Canvas.
```
gcc consumer.c -pthread -lrt -o consumer
gcc producer.c -pthread -lrt -o producer
```

# Execution

In a terminal, execute `run.sh`.
