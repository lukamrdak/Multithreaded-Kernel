/*
 * IdleThr.cpp
 *
 *  Created on: Aug 3, 2018
 *      Author: OS1
 */

#include "IdleThr.h"
#include "thread.h"
#include "locks.h"

IdleThread* IdleThread::idleThread = 0;
PCB* IdleThread::idleThreadPCB = 0;


IdleThread::IdleThread() : Thread(1500, 1) {
}


IdleThread::~IdleThread(){
}

void IdleThread::run() {
	int alwaysTrue = 1;
	while(alwaysTrue);
}

void IdleThread::start(){
	lock
	myPCB->start();
	unlock
}

void initIdleThread(){
			IdleThread::idleThread = new IdleThread();
			IdleThread::idleThread->start();
			IdleThread::idleThreadPCB = Global::allThreads->removeFirst();
			//Global::allThreads->decID();
}

