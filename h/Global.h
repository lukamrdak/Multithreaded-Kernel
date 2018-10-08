/*
 * Global.h
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

 #include "pcb.h"
#include "ThrLst.h"
#include "IVTE.h"
#include "SThrLst.h"
#include "KSemL.h"

class Global {
public:
	Global();
	static volatile PCB* running;				//Nit koja se trenutno izvrsava
	static volatile unsigned counter;			//Brojac koliko jos vremena tekuca nit ima dok joj se ne oduzme procesor
	static volatile int lockCounter; 			//broji koliko je puta pozvato lock da bi dozvolio preuzimanje samo kada se izadje iz svih
	static volatile unsigned lockFlag;			//Flag da li je dozvoljeno preuzimanje 1-dozvoljeno, 0 nije

	static volatile unsigned requestedDispatch;

	static SleepThreadList* sleepingThreads;	// Lista uspavanih niti (njihovih PCB-jeva)
	static ThreadList* allThreads;				//Lista svih niti (njihovih PCB-jeva)
	static KernelSemList* allKernelSemaphores;	//Lista svih KernelSemafora

	static pInterrupt oldRoutine;				//stara prekidna rutina na 55ms
	static pInterrupt newRoutine;
	static void setRequestedDispatch();			//postavi flag za promenu konteksta
	static void resetRequestedDispatch();		//ukloni flag za promenu konteksta

	static PCB* getIdleThreadPCB();				//dohvati PCB Idle Threada
	static PCB* getMainThreadPCB();				//dohvati PCB glavne niti

	static void initialiseInterruptRoutine();	//inicijalizacija ulaza u tabelu prekidnih rutina
	static void restoreInterruptRoutine();		//povratak stare prekidne rutine

	static void initRunning();

	static void init(int, char**);				//inicijalizacija svega sto je potrebno
	static void restore();						// brisanje svega i dovrsavanje

	static void runWrapper();
};

//volatile unsigned requestedDispatch; 	//Flag da li je zatrazena promena konteksta
				//pomocne promenljive za promenu konteksta


void tick();
#endif /* GLOBAL_H_ */
