/*
 * IVTE.cpp
 *
 *  Created on: Jun 29, 2018
 *      Author: OS1
 */

#include "IVTE.h"
#include "DOS.H"
#include "locks.h"

IVTEntry* IVTEntry::IVTEntries[256];

IVTEntry::IVTEntry(IVTNo _IVTEntryNumber, pInterrupt _newRoutine) {
	IVTEntryNumber = _IVTEntryNumber;
	oldRoutine = 0;	// u konstruktoru kernelEventa se dodeljuje odgovarajuca prekidna rutina
	newRoutine = _newRoutine;
	myEvent = 0;
	IVTEntry::IVTEntries[IVTEntryNumber] = this;
}

IVTEntry::~IVTEntry() {
}

void IVTEntry::signal() {
	myEvent->signal();
}

void IVTEntry::callOldRoutine() {
	oldRoutine();
}
