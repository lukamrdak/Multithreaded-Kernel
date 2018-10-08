/*
 * KSemL.cpp
 *
 *  Created on: Aug 14, 2018
 *      Author: OS1
 */

#include "KSemL.h"
#include "locks.h"

int KernelSemList::KerSemId = 1;

KernelSemList::KernelSemList() {
	lock
	first = last = 0;
	numOfElements = 0;
	unlock
}

void KernelSemList::append(KernelSem* _kerSem){
	lock
	if(_kerSem->id != 0){
		unlock
		return;
	}

	KernelSemList::Element* newElement = new KernelSemList::Element(_kerSem);
		if (first == 0)
			first = last = newElement;
		else {
			last->next = newElement;
			last = last->next;
		}
		numOfElements++;

	if (_kerSem->id == 0)
				_kerSem->id = KerSemId++;
			//test
		unlock
}


KernelSem* KernelSemList::get(int _id) {
	lock
	KernelSem* retKerSem = 0;
	if (first == 0) {
		unlock
		return retKerSem;
	}
	for (Element* current = first; current != 0; current = current->next) {
		if (current->kernelSem->id == _id) {
			retKerSem = current->kernelSem;
			break;
		}
	}
	unlock
	return retKerSem;
}

KernelSem* KernelSemList::getFirst(){
	lock
		KernelSem* returnKSem = 0;
		if (first == 0) {
			unlock
			return returnKSem;
		}
		returnKSem = get(first->kernelSem->id);
		unlock
		return returnKSem;
}

KernelSem* KernelSemList::remove(int _id) {
	lock
	KernelSem* ret = 0;
	if (first == 0) {
		unlock
		return ret;
	}
	Element* previous = 0;
	Element* current = first;

	for(; current != 0; previous = current,current = current->next){
		if(current->kernelSem->id == _id){

			ret = current->kernelSem;
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


KernelSem* KernelSemList::removeFirst() {
	KernelSem* toret = 0;
	lock
	if(first != 0)
		toret = remove(first->kernelSem->id);
	unlock
	return toret;
}
