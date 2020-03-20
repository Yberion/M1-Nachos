#include "userlib/syscall.h"
#include "userlib/libnachos.h"

SemId semaphore;

void thread1_fun()
{
    n_printf("Thread 1\n");
}

void thread2_fun()
{
    n_printf("Thread 2\n");
}

// Wait 1 and 2 to execute before this one
void thread3_fun()
{
    n_printf("Thread 3\n");
}

int main()
{
	n_printf("\n\n\n** Starting semaphore test **\n\n");
	n_printf("\n");
	
	semaphore = SemCreate("Semaphore 1", 0);

	ThreadId thread_1 = threadCreate("thread0", thread1_fun);
	ThreadId thread_2 = threadCreate("thread1", thread2_fun);
	ThreadId thread_3 = threadCreate("thread2", thread3_fun);


	Join(thread_1);
	Join(thread_2);
	Join(thread_3);

	SemDestroy(semaphore);

	n_printf("\n\n** Ending semaphore test **\n\n\n");

    return 0;
}
