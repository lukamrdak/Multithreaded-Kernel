/*
 * STL_t.cpp

 *
 *  Created on: Aug 7, 2018
 *      Author: OS1
 */

#include "SThrLst.h"
#include "pcb.h"


void sleepThreadListTest(){
	SleepThreadList* sleepThreadList = new SleepThreadList();
	PCB* pcb = new PCB(6000, 30, 0);


	sleepThreadList->append(pcb, 9);
	sleepThreadList->append(pcb, 5);
	sleepThreadList->append(pcb, 14);
	sleepThreadList->append(pcb, 11);
	sleepThreadList->append(pcb, 16);
	sleepThreadList->append(pcb, 14);
	sleepThreadList->append(pcb, 11);
	sleepThreadList->append(pcb, 16);
	sleepThreadList->append(pcb, 18);
	sleepThreadList->append(pcb, 18);
	sleepThreadList->append(pcb, 14);
	sleepThreadList->append(pcb, 5);
	sleepThreadList->append(pcb, 2);
	sleepThreadList->append(pcb, 2);

//provereno dodavanje na pocetak, dodavanje na kraj, dodavanje u sredinu, dodavanje visestrukih sa istim vremenom spavanja
//jedino treba proveriti da li treba da se prilikom dodavanja pcb-ja u listu proveri da li se on vec nalazi u listi

}

