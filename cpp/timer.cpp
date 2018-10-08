/*
S * timer.cpp
 *
 *  Created on: Aug 3, 2018
 *      Author: OS1
 */

#include "IVTE.h"
#include "Global.h"
#include "SCHEDULE.H"
#include "locks.h"
#include "MainThr.h"

volatile unsigned tsp = 0;
volatile unsigned tss = 0;
volatile unsigned tbp = 0;

volatile unsigned tspMain, tssMain, tbpMain;


void interrupt timer(...){

	if(!Global::requestedDispatch){
		tick();
		Global::oldRoutine();
		if(Global::running->timeSlice != 0) Global::counter--;
		Global::sleepingThreads->timeIntervalPassed();

	}

	if((Global::counter == 0 && Global::running->timeSlice != 0) || Global::requestedDispatch){

		//ako je vreme isteklo nekoj niti ili ako je eksplicitno zatrazena promena konteksta
		if(Global::lockFlag){
			//ako je dozvoljeno preuzimanje i promena konteksta
			//prelazimo u promenu konteksta i
			Global::requestedDispatch = 0;


			if(tsp == 0 && tbp == 0 && tss == 0){
				#ifndef BCC_BLOCK_IGNORE
					asm{
						mov tspMain, sp
						mov tssMain, ss
						mov tbpMain, bp
					}
				#endif
					//syncPrintf("MAIN: sp = %u, tss = %u, bp = %u\n", tspMain, tssMain, tbpMain);
			}


			//cuvanje starih vrednosti
			#ifndef BCC_BLOCK_IGNORE
				asm{
					mov tsp, sp
					mov tss, ss
					mov tbp, bp
				}
			#endif
				//syncPrintf("Stare vrednosti: sp = %u, tss = %u, bp = %u\n", tsp, tss, tbp);

				if(Global::running != 0){
					Global::running->sp = tsp;
					Global::running->ss = tss;
					Global::running->bp = tbp;

						if( Global::running != Global::getIdleThreadPCB() &&
							Global::running != Global::getMainThreadPCB() &&
							((PCB*)Global::running)->state == PCB::run){

						((PCB*)Global::running)->state = PCB::ready;
						Scheduler::put((PCB*)Global::running);
					}
				}

				Global::running = Scheduler::get();



				if(Global::running == 0){
					if(Global::allThreads->allUserThreadsTerminated() != 0)	//alternativno provera da li su sve terminated
						Global::running = Global::getMainThreadPCB();
					else{
						Global::running = Global::getIdleThreadPCB();
					}
				}

				((PCB*)Global::running)->state = PCB::run;

				tsp = Global::running->sp;
				tss = Global::running->ss;
				tbp = Global::running->bp;

				//syncPrintf("Nove vrednosti: sp = %u, tss = %u, bp = %u\n", tsp, tss, tbp);

				Global::counter = Global::running->timeSlice;

				if(MainThread::finishedMainThread){
					tsp = tspMain;
					tss = tssMain;
					tbp = tbpMain;
				}

			#ifndef BCC_BLOCK_IGNORE
				asm{
					mov sp, tsp
					mov ss, tss
					mov bp, tbp
				}
			#endif
		}
		else Global::requestedDispatch = 1;
	}

}




/*
void interrupt timer(...){


	if(!Global::requestedDispatch){
		tick();
		#ifndef BCC_BLOCK_IGNORE
		asm int 0x60;
		#endif
		if(Global::running->timeSlice != 0) Global::counter--;
			Global::sleepingThreads->timeIntervalPassed();
	}

	if((Global::counter == 0 && Global::running->timeSlice != 0 )|| Global::requestedDispatch == 1){
		if(Global::lockFlag){
			Global::requestedDispatch = 0;
			#ifndef BCC_BLOCK_IGNORE
			asm{
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
			#endif
			Global::running->ss=tss;
			Global::running->sp=tsp;
			Global::running->bp=tbp;

			if(	Global::running->state != PCB::waiting && Global::running != Global::getIdleThreadPCB()	&& Global::running->state != PCB::terminated){
				Global::running->state = PCB::ready;
				Scheduler::put((PCB*)Global::running);
			}

			Global::running = Scheduler::get();

			if(Global::running == 0){
				Global::running = Global::getIdleThreadPCB();
			}



				tsp=Global::running->sp;
				tss=Global::running->ss;
				tbp=Global::running->bp;

				if(Global::running != Global::getIdleThreadPCB()) Global::running->state = PCB::run;

				Global::counter=Global::running->timeSlice;

				#ifndef BCC_BLOCK_IGNORE
					asm{
						mov sp, tsp
						mov ss, tss
						mov bp, tbp
					}
					#endif
					}								//ako su dozvoljena preuzimanja izvrsi zamenu konteksta
					else Global::requestedDispatch = 1;			//ako nisu onda zapamti zahtev za sledeci put, za 55ms
				}//counter == 0 && PCB::running->timeSlice != 0 //situacija kada je potreban dispatch, ili je zatrazen eksplicitan ili je isteklo vreme tekucoj niti
	}//timer*/
