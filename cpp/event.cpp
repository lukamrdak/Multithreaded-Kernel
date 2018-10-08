/*
 * event.cpp
 *
 *  Created on: Jun 28, 2018
 *      Author: OS1
 */

#include "event.h"
#include "KerEv.h"
#include "locks.h"


Event::Event(IVTNo ivtNo) {
	lock
	myImpl = new KernelEv(ivtNo);
	unlock
}

Event::~Event() {
	lock
	delete myImpl;
	unlock
}

void Event::wait() {
	lock
	myImpl->wait();
	unlock
}

void Event::signal() {
	lock
	myImpl->wait();
	unlock
}
