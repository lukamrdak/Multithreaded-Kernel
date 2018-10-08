/*
 * MainThr.h
 *
 *  Created on: Aug 7, 2018
 *      Author: OS1
 */

#ifndef MAINTHR_H_
#define MAINTHR_H_


#include "thread.h"

class MainThread:Thread{
public:
	MainThread();
	~MainThread();
	static int getMainRetValue();
	void run();
	void start();
	static void runWrapper();
	static void finishMain();
protected:
	static MainThread* mainThread;
	static PCB* mainThreadPCB;
	static int argc;
	static char** argv;
	static int returnValue;
	static int finishedMainThread;

	friend void initMain(int, char**);
	friend class Global;
	friend void interrupt timer(...);
};

#endif /* MAINTHR_H_ */
