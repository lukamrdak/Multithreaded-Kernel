/*
 * event.h
 *
 *  Created on: Jun 28, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
//#include "KerEv.h"


typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();
protected:
	friend class KernelEv;
	void signal();
private:
	KernelEv* myImpl;
	friend class IVTEntry;
};

#endif /* EVENT_H_ */
