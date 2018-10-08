/*
 * pcb.h
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "thread.h"
#include "ThrLst.h"


class ThreadList;

class PCB {
public:

//test private:


	unsigned sp;	//stack pointer
	unsigned ss;	//stack segment/ huge mem model
	unsigned bp;	//base pointer

	unsigned* stack; //stek niti

	Thread* myThread;
	StackSize stackSize;
	Time timeSlice;

	ThreadList* waitingToComplete;
	int id;
	enum ThreadState{
			created,
			ready,
			run,
			waiting,
			terminated
		};
	volatile ThreadState state; //treba li ovo da bude volatile
	static void wrapper();
//protected: commented out for test purposes
	PCB(StackSize, Time, Thread*);
	~PCB();
	void start();
	void waitToComplete();
	static void sleep(Time timeToSleep);
	int getID();
	void initializeMainThreadStack();

	friend class ThreadList;
	friend void interrupt timer(...);
	friend class SleepThreadList;
};

#endif /* PCB_H_ */
