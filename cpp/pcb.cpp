/*
 * pcb.cpp
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#include "pcb.h"
#include "dos.h"
#include "Global.h"
#include "ThrLst.h"
#include "STDIO.H"
#include "SCHEDULE.H"
#include "locks.h"
#include "MainThr.h"

//test

int PCB::getID() {
	return id;
}

PCB::PCB(StackSize _stackSize, Time _timeSlice, Thread* _myThread) {
	myThread = _myThread;
	timeSlice = _timeSlice;
	stackSize = _stackSize;
	stackSize /= sizeof(unsigned);
	if (stackSize > maxStackSize)
		stackSize = maxStackSize;
	id = 0;
	state = PCB::created;

	stack = new unsigned[stackSize];
		stack[stackSize - 1] = 0x200;
	#ifndef BCC_BLOCK_IGNORE
		stack[stackSize - 2] = FP_SEG(PCB::wrapper);
		stack[stackSize - 3] = FP_OFF(PCB::wrapper);

		this->ss = FP_SEG(this->stack + this->stackSize - 12);
		this->sp = FP_OFF(this->stack + this->stackSize - 12);
		this->bp = this->sp;
	#endif
	waitingToComplete = new ThreadList();
	Global::allThreads->append(this);
}

PCB::~PCB() {
	lock
		delete stack;
		delete waitingToComplete;
	unlock
}

void PCB::start() {
	lock
	if (state == PCB::created)
			state = PCB::ready;

	unlock
}

void PCB::wrapper() {

	Global::running->myThread->run();

	Global::running->state = PCB::terminated;
	Global::running->waitingToComplete->unblockAll();
	dispatch();

}

void PCB::waitToComplete() {
	lock
	if (	this != Global::running &&
			this != Global::getMainThreadPCB() &&
			this != Global::getIdleThreadPCB() &&
			state != PCB::terminated) {

		((PCB*)Global::running)->state = PCB::waiting;
		waitingToComplete->appendNoIDcheck((PCB*)Global::running);

	/*	//TEST
		syncPrintf("dispatch waittocomplete\n");

		if(this == Global::getMainThreadPCB()) syncPrintf("__MAIN__");
		if(this == Global::getIdleThreadPCB()) syncPrintf("__IDLE__");
		else syncPrintf("ID running: %d ID this = %d Running state %d\n",((PCB*)Global::running)->getID(), getID(),((PCB*)Global::running)->state );
		Global::allThreads->writeList();
		//test
*/

		unlock
		dispatch();
		return;
	}
	else{
		unlock
		return;
	}
}



void PCB::sleep(Time timeToSleep) {
	Global::sleepingThreads->append((PCB*)Global::running, timeToSleep);
	dispatch();
}

void PCB::initializeMainThreadStack(){
	stack[stackSize - 1] = 0x200;
	#ifndef BCC_BLOCK_IGNORE
		stack[stackSize - 2] = FP_SEG(MainThread::runWrapper);
		stack[stackSize - 3] = FP_OFF(MainThread::runWrapper);

		this->ss = FP_SEG(this->stack + this->stackSize - 12);
		this->sp = FP_OFF(this->stack + this->stackSize - 12);
		this->bp = this->sp;
	#endif
}

