/*
 * semaphor.cpp
 *
 *  Created on: Aug 14, 2018
 *      Author: OS1
 */

#include "semaphor.h"
#include "locks.h"
#include "KerSem.h"
#include "Global.h"
#include "KSemL.h"

Semaphore::Semaphore(int init) {
	lock
		myImpl = new KernelSem(init);
	Global::allKernelSemaphores->append(myImpl);
	unlock
}

Semaphore::~Semaphore() {
	lock
		delete myImpl;
	unlock
}

int Semaphore::wait(int toBlock) {
	lock
		int retval = myImpl->wait(toBlock);
	unlock
	return retval;
}

void Semaphore::signal() {
	lock
		myImpl->signal();
	unlock
}

int Semaphore::val() const {
	lock
		int ret = myImpl->val();
	unlock
		return ret;
}
