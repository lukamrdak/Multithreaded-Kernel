/*
 * KerSem.cpp
 *
 *  Created on: Aug 14, 2018
 *      Author: OS1
 */

#include "KerSem.h"
#include "Global.h"
#include "locks.h"
#include "SCHEDULE.H"
#include "ThrLst.h"

KernelSem::KernelSem(int _init) {
lock
	value = _init;
	//syncPrintf("Semafor inicijalizovan na vrednost %d\n", value);
	id = 0;
	waitingOnSemaphore = new ThreadList();
unlock
}

KernelSem::~KernelSem() {
lock
	delete waitingOnSemaphore;
unlock
}

int KernelSem::wait(int toBlock) {
	lock
	int retVal;
	//syncPrintf("Pozvan wait na semaforu ID= %d, vrednost semafora pre je %d, (--value < 0 uslov za blokiranje) \n", id, value);
	if(toBlock != 0) retVal = standardWait();
	else{
		if(value <= 0) retVal = -1;
		else retVal = standardWait();
	}
	unlock
	return retVal;
}


void KernelSem::signal() {
lock
	//syncPrintf("Pozvan signal na semaforu ID= %d, vrednost semafora pre je %d, (value++ < 0 uslov za odblokiranje) \n", id, value);
	if(value++ < 0){ 													//proveri da li treba jednako
			PCB* unblocked = waitingOnSemaphore->removeFirst();
				//syncPrintf("UNBLOCK: ID odblokirane niti = %d, ID semafora = %d, value = %d (posle ++)\n",unblocked->getID(), id,value);
				unblocked->state = PCB::ready;
				Scheduler::put(unblocked);

		}
unlock
}

int KernelSem::val() const {
lock
	int rval= value;
unlock
return rval;
}



int KernelSem::standardWait(){
	lock
	int returningValue;
	if(--value < 0){
		Global::running->state = PCB::waiting;
		//syncPrintf("BLOCK: ID blokirane niti = %d, ID semafora = %d,  value = %d(posle --)\n",((PCB*)Global::running)->getID(), id,value);
		waitingOnSemaphore->appendNoIDcheck((PCB*)Global::running);
		dispatch();
		returningValue = 1;
	}
	else returningValue = 0;
	unlock
	return returningValue;
}
