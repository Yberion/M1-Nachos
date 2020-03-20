#include "userlib/syscall.h"
#include "userlib/libnachos.h"

LockId lock;

void thread1_fun()
{
    n_printf("==== Thread 1 START\n");
    LockAcquire(lock);
    n_printf("==== Thread 1 - LOCKED\n");
    LockRelease(lock);
    n_printf("==== Thread 1 FINISH\n");
}

void thread2_fun()
{
    n_printf("==== Thread 2 START\n");
    LockAcquire(lock);
    n_printf("==== Thread 2 - LOCKED\n");
    LockRelease(lock);
    n_printf("==== Thread 2 FINISH\n");
}

int main()
{
    n_printf("\n\n\n** Starting lock test **\n\n");
    n_printf("\n");

    lock = LockCreate("Lock 1");
    
    ThreadId thread_1 = threadCreate("thread1", thread1_fun);
    ThreadId thread_2 = threadCreate("thread2", thread2_fun);

    Join(thread_1);
    Join(thread_2);

    LockDestroy(lock);

    n_printf("\n\n** Ending lock test **\n\n\n");

    return 0;
}
