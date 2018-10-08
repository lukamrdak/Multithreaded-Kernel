/*
 * IVTE.h
 *
 *  Created on: Jun 29, 2018
 *      Author: OS1
 */

#ifndef IVTE_H_
#define IVTE_H_
#include "KerEv.h"
#include "event.h"
#include "DOS.H"



typedef void interrupt (*pInterrupt) (...);

class IVTEntry {
public:
	IVTEntry(IVTNo _IVTEntryNumber, pInterrupt newRoutine);
	~IVTEntry();

	void signal();
	void callOldRoutine();

static IVTEntry* IVTEntries[256];

protected:
	pInterrupt oldRoutine;
	pInterrupt newRoutine;
	KernelEv* myEvent;
	IVTNo IVTEntryNumber;


	friend class KernelEv;
	friend class Event;
};


#define PREPAREENTRY(entryNumber, callOld)\
void interrupt inter##entryNumber(...);\
IVTEntry newEntry##entryNumber(entryNumber, inter##entryNumber);\
void interrupt inter##entryNumber(...){\
	newEntry##entryNumber.signal();\
	if(callOld == 1)\
		newEntry##entryNumber.callOldRoutine();\
}

#endif /* IVTE_H_ */
