#include "userlib/syscall.h"
#include "userlib/libnachos.h"

CondId cond;

const int NB_THREAD = 3;

int values[] = {12, 6, 8, 9};
int pt[4];
int ok[3];

void ok_init()
{
	int i;
	for(i = 0; i < NB_THREAD; i++)
	{
		ok[i] = 1;
	}
}

int all_threads_ended()
{
	int i;
	for(i = 0; i < NB_THREAD; i++)
	{
		if(ok[i] == 1)
		{
			n_printf("thread %d have not ended\n", i);
			return 1;
		}
	}
	return 0;
}

void run_thread(int id)
{
	n_printf("run thread %d\n", id);
	if(pt[id] >= 0)
	{
		int newValue = values[id] + values[pt[id]];
		int newPt = pt[pt[id]];
		n_printf("run thread %d compute ended -> %d\n", id, newValue);
		ok[id] = 0;
		int error = CondWait(cond);
		n_printf("CondWait error %d : %d\n", id, error);
		values[id] = newValue;
		pt[id] = newPt;
	} 
	else
	{
		ok[id] = 0;
	}
}

void thread0()
{
	run_thread(0);
}

void thread1()
{
	run_thread(1);
}

void thread2()
{
	run_thread(2);
}

void step(int step)
{
	n_printf("step %d\n", step);
	
	ok_init();
	
	threadCreate("thread", thread0);
	threadCreate("thread", thread1);
	threadCreate("thread", thread2);
	
	while(all_threads_ended() == 1)
	{
		//n_printf("dommage\n");
		Yield();
	}
	
	if(CondBroadcast(cond) != 0)
	{
		n_printf("error on CondBroadcast\n");
	}
	else
	{
		n_printf("CondBroadcast ok\n");
	}
}

int main()
{
	n_printf("\n\n\n** Starting condition test **\n\n");
	n_printf("trying to compute 12+6+8+9 in parallele with pointer jumping\n");
	
	cond = CondCreate("MyCond");
	
	int i;
	for(i = 0; i < NB_THREAD; i++)
	{
		pt[i] = i+1;
		ok[i] = 1;
	}
	pt[3] = -1;
	
	i = 1;
	while(pt[0] >= 0)
	{
		n_printf("value = %d\n", values[0]);
		step(i);
		i++;
	}
	
	n_printf("value = %d\n", values[0]);
	
	n_printf("\n\n** Ending condition test **\n\n\n");

    return 0;
}
