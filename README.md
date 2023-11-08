# ProducerConsumer
Emulates the Producer-Consumer problem in operating systems

Contains:
Producer.cpp
Consumer.cpp
sharedMem.h

How this should work is that The producer should take a structure from the shared memory, produce a number for it, and then send it to the consumer to print out. I've converted a lot of code from the example given so that it's in two files, the memory comes from a structure, and the mmap maps the files. However, I can't get the programs to run, because mmap won't work on me. It's giving me an error for the void address of NULL, but all of the examples I've seen use that, and it seems to be the preferred parameter.
