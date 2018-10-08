/*
 * MainThr.cpp
 *
 *  Created on: Aug 7, 2018
 *      Author: OS1
 */

#include "MainThr.h"
#include "thread.h"
#include "Global.h"
#include "locks.h"

extern int userMain(int argc, char** argv);

MainThread* MainThread::mainThread = 0;
PCB* MainThread::mainThreadPCB = 0;
int MainThread::argc = 0;
char** MainThread::argv = 0;
int MainThread::returnValue = 0;
int MainThread::finishedMainThread = 0;


MainThread::MainThread(): Thread(700, 0) { // proveriti kako ovo treba da bude
}


MainThread::~MainThread() {
}

void MainThread::start(){
	lock
	myPCB->start();
	unlock
}

void MainThread::run(){
	returnValue = userMain(MainThread::argc, MainThread::argv);
}

int MainThread::getMainRetValue() {
	return MainThread::returnValue;
}

void MainThread::runWrapper(){
	MainThread::mainThread->run();
	MainThread::finishMain();

}

void initMain(int argc, char** argv){
		MainThread::mainThread = new MainThread();
		MainThread::mainThreadPCB = Global::allThreads->removeFirst();
		MainThread::mainThread->start();
		MainThread::mainThreadPCB->initializeMainThreadStack();
		//Global::allThreads->decID();
		MainThread::argc = argc;
		MainThread::argv = argv;
}

void MainThread::finishMain(){
	MainThread::finishedMainThread = 1;
	dispatch();
}
