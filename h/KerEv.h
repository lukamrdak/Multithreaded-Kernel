/*
 * KerEv.h
 *
 *  Created on: Jun 29, 2018
 *      Author: OS1
 */

#ifndef KEREV_H_
#define KEREV_H_


#include "event.h"
#include "pcb.h"
#include "SCHEDULE.H"
#include "semaphor.h"



class KernelEv {
public:
	KernelEv(IVTNo _ivtEntry);
	~KernelEv();
	void signal();
	void wait();
private:
	IVTNo ivtEntryNumber;
	Semaphore* binSemaphore;
	int creatorID;
};

#endif /* KEREV_H_ */
