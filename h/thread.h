/*
 * thread.h
 *
 *  Created on: Jul 2, 2018
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_




typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
const StackSize maxStackSize = 65535;
typedef unsigned int Time;
const Time defaultTimeSlice = 200;
typedef int ID;

class PCB;

class Thread {
public:

	void start();

	void waitToComplete();

	virtual ~Thread();

	void sleep(Time timeToSleep);
	//TODO: test, izbrisati posle
	int getId();
	static int getRunningId();

protected:

	friend class PCB;
	friend class IdleThread;
	friend class MainThread;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice =	defaultTimeSlice);
	virtual void run();
private:
	PCB* myPCB;
};

void dispatch();


#endif /* THREAD_H_ */
