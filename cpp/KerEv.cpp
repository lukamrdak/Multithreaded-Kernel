/*
 * KerEv.cpp
 *
 *  Created on: Jun 29, 2018
 *      Author: OS1
 */

#include "KerEv.h"
#include "Global.h"
#include "locks.h"
#include "pcb.h"
#include "DOS.H"

KernelEv::KernelEv(IVTNo _ivtEntry){
	lock
		ivtEntryNumber = _ivtEntry;
		binSemaphore = new Semaphore(1);
		creatorID = ((PCB*)Global::running)->getID();
		IVTEntry::IVTEntries[ivtEntryNumber]->myEvent = this;
	unlock
	if(IVTEntry::IVTEntries[ivtEntryNumber]->oldRoutine == 0){
#ifndef BCC_BLOCK_IGNORE
		IVTEntry::IVTEntries[ivtEntryNumber]->oldRoutine = getvect(ivtEntryNumber);
		setvect(ivtEntryNumber, IVTEntry::IVTEntries[ivtEntryNumber]->newRoutine);
#endif
	}
}

//i ovde ima da se sredi kada se zavrsi klasa
KernelEv::~KernelEv(){
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtEntryNumber, IVTEntry::IVTEntries[ivtEntryNumber]->oldRoutine);
#endif
	IVTEntry::IVTEntries[ivtEntryNumber]->myEvent = 0;
}


void KernelEv::signal(){
	lock
		binSemaphore->signal();
	unlock
}

void KernelEv::wait(){
	lock
	if(((PCB*)Global::running)->getID() == creatorID)
		binSemaphore->wait(1);//ako je parametar toblock != 0 operacija se ponasa na standardan nacin
	unlock
}
