/*
 * KerSem.h
 *
 *  Created on: Aug 14, 2018
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "ThrLst.h"
#include "thread.h"

class KernelSem {
public:
	KernelSem(int _init);
	virtual ~KernelSem();

	virtual int wait(int);
	virtual void signal();
	int val() const;
private:
	int value;
	int id;
	ThreadList* waitingOnSemaphore;
	int standardWait();

	friend class KernelSemList;
};

#endif /* KERSEM_H_ */
