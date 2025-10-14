# opsys-asmt1

Description borrowed from Canvas: 
```
Topic: Producer-Consumer Problem
The producer generates items and puts items onto the table. The consumer will pick up items.
The table can only hold two items at the same time. When the table is completed, the producer
will wait. When there are no items, the consumer will wait. We use semaphores to synchronize
the producer and the consumer. Mutual exclusion should be considered. We use threads in
the producer program and consumer program. Shared memory is used for the “table”.

We expect to use these two programs (producer and consumer) like this:
$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &
```
The producer program allows you to decide what items to put on the table. The consumer program will pick up the items from the table that are set by the producer. When the table is full, the producer will wait for the consumer to pick up something. When the table is empty, the consumer will wait for the producer to put out something new. 
