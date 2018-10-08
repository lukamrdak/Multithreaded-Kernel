/*
 * ThrLst.cpp
 *
 *  Created on: Aug 2, 2018
 *      Author: OS1
 */

#include "ThrLst.h"
#include "pcb.h"
#include "STDIO.H"
#include "locks.h"
#include "SCHEDULE.H"
//test

int ThreadList::PCBId = 1;	//0 kao indikator da je tek kreiran pcb

ThreadList::ThreadList() {
	lock
	first = last = 0;
	numOfElements = 0;
	unlock
}

ThreadList::~ThreadList() {
	//for(ThreadList::Element* curr = first; curr!= 0; curr = curr->next)	curr->pcb->waitToComplete();
}

void ThreadList::append(PCB* _pcb) {
	lock
	if (_pcb->id != 0){
		unlock;
		return;	//ako ovaj element vec postoji u listi
	}

	appendNoIDcheck(_pcb);

	if (_pcb->id == 0)
			_pcb->id = PCBId++;
		//test
	unlock
}

void ThreadList::appendNoIDcheck(PCB* p){
lock
	ThreadList::Element* newElement = new ThreadList::Element(p);
	if (first == 0)
		first = last = newElement;
	else {
		last->next = newElement;
		last = last->next;
	}
	numOfElements++;

unlock
}
PCB* ThreadList::get(int id) {
	lock
	PCB* retPCB = 0;
	if (first == 0) {
		unlock
		return retPCB;
	}
	for (Element* current = first; current != 0; current = current->next) {
		if (current->pcb->getID() == id) {
			retPCB = current->pcb;
			break;
		}
	}
	unlock
	return retPCB;
}

PCB* ThreadList::getFirst() {
	lock
	PCB* returnPCB = 0;
	if (first == 0) {
		unlock
		return returnPCB;
	}
	returnPCB = get(first->pcb->id);
	unlock
	return returnPCB;
}

PCB* ThreadList::remove(int _id) {
	lock
	PCB* ret = 0;
	if (first == 0) {
		unlock
		return ret;
	}
	Element* previous = 0;
	Element* current = first;

	for(; current != 0; previous = current,current = current->next){
		if(current->pcb->getID() == _id){

			ret = current->pcb;
			numOfElements--;

			if(current == first && current == last)						//1 element
				first = last = 0;
			else if(current != first && current != last){				//sredina
					previous->next = current->next;
					current->next = 0;
				}
			else if(current == first && current != last){				//pocetak
				first = current->next;
				current->next = 0;
			}
			else if(current != first && current == last){
				last = previous;
				previous->next = 0;
			}
			delete current;
			}
			if(ret != 0) break;
		}
	unlock
	return ret;
}

PCB* ThreadList::removeFirst() {
	PCB* toret = 0;
	lock
	if(first != 0)
		toret = remove(first->pcb->getID());
	unlock
	return toret;
}

void ThreadList::unblockAll() {
	lock
	PCB* pcbToUnblock =	removeFirst();
	while (pcbToUnblock != 0) {
		if(pcbToUnblock->state == PCB::waiting){
			//syncPrintf("Odblokirana nit ID = %d ", pcbToUnblock->getID());
			pcbToUnblock->state = PCB::ready;
			Scheduler::put(pcbToUnblock);
		}
		pcbToUnblock = removeFirst();
	}
	unlock
}

void ThreadList::writeList(){
	lock
	for(Element* current = first; current != 0; current = current->next){
			syncPrintf("ID = %d , state = %d \n", current->pcb->getID(), current->pcb->state);
		}
	unlock
}


void ThreadList::decID(){
	lock
	PCBId--;
	unlock
}

int ThreadList::allUserThreadsTerminated(){
	int num = 0;
	lock
	for(Element* current = first; current != 0; current = current->next)
		if(current->pcb->state == PCB::terminated) num++;

	if(num == numOfElements) num = 1;
	else num = 0;


	unlock
	return num;
}


/*for (; current != 0; ) {
		if (current->pcb->getID() == id) {
			if (previous == 0) {				//ako se izbacuje prvi iz liste
				first = first->next;
				if (first == 0)
					last = 0;			//ako je lista samo od jednog elementa
				ret = current->pcb;
				delete current;
				break;

			} else if (current == last) {	//ako se izbacuje poslednji iz liste
				last = previous;
				last->next = 0;
				ret = current->pcb;
				delete current;
				break;

			} else {
				previous->next = current->next;
				current->next = 0;
				ret = current->pcb;
				delete current;
				break;
			}
		}
		previous = current; current = current->next;
	}*/
