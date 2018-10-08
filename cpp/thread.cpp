/*
 * thread.cpp
 *
 *  Created on: Jul 2, 2018
 *      Author: OS1
 */

#include "thread.h"
#include "pcb.h"
#include "Global.h"
#include "locks.h"
#include "SCHEDULE.H"

Thread::Thread(StackSize _stackSize, Time _timeSlice){
	myPCB = new PCB(_stackSize, _timeSlice, this);
}

Thread::~Thread(){
	waitToComplete();
	delete myPCB;
}

void Thread::start(){
	lock
	myPCB->start();
	Scheduler::put(myPCB);
	unlock
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

void Thread::sleep(Time _timeToSleep){
	myPCB->PCB::sleep(_timeToSleep);
}

void Thread::run(){

}
int Thread::getId(){
	return myPCB->getID();
}


void dispatch(){
	lock
	Global::setRequestedDispatch();
	unlock
	#ifndef BCC_BLOCK_IGNORE
		asm int 0x60;
	#endif
}

int Thread::getRunningId(){
	lock
	int idret = ((PCB*)Global::running)->getID();
	unlock
	return idret;
}

