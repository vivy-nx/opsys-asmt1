#! /bin/bash

gcc consumer.c -pthread -lrt -g -o consumer
gcc producer.c -pthread -lrt -g -o producer