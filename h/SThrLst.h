/*
 * SThrLst.h
 *
 *  Created on: Aug 3, 2018
 *      Author: OS1
 */

#ifndef STHRLST_H_
#define STHRLST_H_

#include "pcb.h"
#include "thread.h"


class SleepThreadList {
public:
	SleepThreadList();
	~SleepThreadList();

	PCB* removeFirst();			//metoda koja uklanja prvi element iz niza i vraca njegov PCB, nisam siguran da li je i za sta potrebna

	void append(PCB*, Time);	//metoda koja dodaje PCB niti koja treba da bude uspavana Time vremena

	void timeIntervalPassed();	//metoda koja se poziva kada treba da se bude uspavane niti

	void writeList();
protected:
	struct Element{
		PCB* pcb;
		Time timeToSleep;
		Element* next;

		Element(PCB* _pcb, Time _time, Element* _next = 0){
			pcb = _pcb;
			timeToSleep = _time;
			next = _next;
		};

	};

	Element* first;
	int numOfElements;
};

#endif /* STHRLST_H_ */
