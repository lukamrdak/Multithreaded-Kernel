/*
 * ThrLst.h
 *
 *  Created on: Aug 2, 2018
 *      Author: OS1
 */

#ifndef THRLST_H_
#define THRLST_H_
#include "pcb.h"

class ThreadList {
public:
	ThreadList();
	~ThreadList();
	void append(PCB* _pcb);
	void appendNoIDcheck(PCB*);
	PCB* get(int id);
	PCB* getFirst();
	PCB* remove(int id);
	PCB* removeFirst();
	void unblockAll();
	void writeList();
	static void decID();
	int allUserThreadsTerminated();		//0-nisu sve korisnicke niti zavrsene, 1-jesu sve korisnicke niti zavrsene
protected:
	struct Element{
		PCB* pcb;	//posto je pokazivac kada se izbrise u jednoj listi onda se ne menja u drugoj
		Element* next;
		Element(PCB* myPCB, Element* nextElem = 0){
			pcb = myPCB;
			next = nextElem;
		}
	};

	Element *first;
	Element *last;
	int numOfElements;
	static int PCBId;
};

#endif /* THRLST_H_ */
