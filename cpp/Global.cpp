/*
S * Global.cpp
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#include "Global.h"
#include <DOS.H>
#include "IdleThr.h"
#include "locks.h"
#include "MainThr.h"
#include "IVTE.h"

Global::Global(){
}

volatile PCB* Global::running = 0;
volatile unsigned Global::counter = 0;
volatile int Global::lockCounter = 0;
volatile unsigned Global::lockFlag = 1;
ThreadList* Global::allThreads = new ThreadList();
SleepThreadList* Global::sleepingThreads = new SleepThreadList();
KernelSemList* Global::allKernelSemaphores = new KernelSemList();
pInterrupt Global::oldRoutine = 0;
pInterrupt Global::newRoutine = 0;
volatile unsigned Global::requestedDispatch = 0;

void Global::setRequestedDispatch(){Global::requestedDispatch = 1;}
void Global::resetRequestedDispatch(){Global::requestedDispatch = 0;}


PCB* Global::getIdleThreadPCB(){
	return IdleThread::idleThreadPCB;
}

void Global::initialiseInterruptRoutine(){

#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	lock
	Global::oldRoutine = getvect(0x08);		//TODO: treba li heksa ili obicna osmica
	setvect(0x08, timer);					// 08: nova prekidna rutina
	setvect(0x60, Global::oldRoutine);		// 60: stara prekidna rutina na 55ms
#endif
	Global::newRoutine = timer;
	unlock
#ifndef BCC_BLOCK_IGNORE
	asm popf;
#endif
}

void Global::restoreInterruptRoutine(){

#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	setvect(0x08, Global::oldRoutine);		// 08: vracena stara prekidna rutina
	asm popf;
#endif

}

void Global::init(int argc, char** argv){	//pre ovoga se vrsi inicijalizacija liste svih niti i liste uspavanih niti
	lock
	initIdleThread();						//inicijalizacija idle Threada, stavi se u scheduler i onda se izbaci
	initMain(argc, argv);
	dispatch();
	unlock
}

void Global::restore(){
	delete Global::allThreads;
	delete MainThread::mainThread;
	delete MainThread::mainThreadPCB;
	delete IdleThread::idleThread;
	delete IdleThread::idleThreadPCB;
	delete Global::sleepingThreads;
}

PCB* Global::getMainThreadPCB(){
	return MainThread::mainThreadPCB;
}

void Global::runWrapper(){
	Global::running->wrapper();
}


void Global::initRunning(){

}
