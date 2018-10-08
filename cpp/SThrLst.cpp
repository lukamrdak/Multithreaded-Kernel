/*
 * SThrLst.cpp
 *
 *  Created on: Aug 3, 2018
 *      Author: OS1
 */

#include "SThrLst.h"
#include "locks.h"
#include "SCHEDULE.H"



SleepThreadList::SleepThreadList(){
	lock
	first = 0;
	numOfElements = 0;
	unlock
}


SleepThreadList::~SleepThreadList(){
	lock
		Element* old = first;
		while(old != 0){
			old = first->next;
			delete first;
			first = old;
		}
	unlock
}

PCB* SleepThreadList::removeFirst(){
	lock
		if (first == 0) {
			unlock;
			return 0;
		}

		Element* old = first;
		PCB* ret = first->pcb;
		first = first->next;
		old->next = 0;
		delete old;
	unlock
	return ret;
}


void SleepThreadList::append(PCB* _pcb, Time _time){
	lock
	if(_pcb == Global::getIdleThreadPCB()){
		unlock
		return;
	}
	//TODO: da li je potrebna provera da li se taj pcb vec nalazi u uspavanim
	numOfElements++;
	_pcb->state = PCB::waiting;

	if(first == 0){
		first = new Element(_pcb, _time);
		unlock
		//test
		return;
	}
	//poseban slucaj kada se dodaje na pocetak

	if(_time <= first->timeToSleep){
		Element* newElement = new Element(_pcb, _time, first);
		first->timeToSleep -= _time;
		first = newElement;
		unlock
		return;
	}


	Time timeElapsed = 0;
	Element* current = first;
	Element* previous = 0;

	//ok


	while(current->next != 0 && timeElapsed < _time){
			timeElapsed+=current->timeToSleep;
			previous = current;
			current = current->next;

	}
	timeElapsed+= current->timeToSleep;// za slucaj kada ima samo jedan element u listi. numOfElements == 2


	if(current->next == 0 && timeElapsed <= _time){ //ako se dodaje na kraj liste
			current->next = new Element(_pcb, _time - timeElapsed);
		unlock
		return;
	}

	timeElapsed-= current->timeToSleep;

	//dodavanje u sredinu liste
	Element* elem = new Element(_pcb,  _time - timeElapsed);
	previous->next = elem;
	elem->next = current;
	current->timeToSleep -= (_time - timeElapsed);
	unlock
	return;

}

void SleepThreadList::timeIntervalPassed(){
	if(first == 0)
		return;
	first->timeToSleep--;
	while(first && first->timeToSleep == 0){
		PCB* wakeUp = removeFirst();
		wakeUp->state = PCB::ready;
		Scheduler::put(wakeUp);
	}
}

void SleepThreadList::writeList(){
	for(Element* current = first; current != 0; current = current->next){
		syncPrintf("ID = %d, time = %u\n", current->pcb->getID(), current->timeToSleep);
	}
}


