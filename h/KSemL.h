/*
 * KSemL.h
 *
 *  Created on: Aug 14, 2018
 *      Author: OS1
 */

#ifndef KSEML_H_
#define KSEML_H_


#include "KerSem.h"

class KernelSemList {
public:
	KernelSemList();
	~KernelSemList();
	void append(KernelSem* _kerSem);
	KernelSem* get(int id);
	KernelSem* getFirst();
	KernelSem* remove(int id);
	KernelSem* removeFirst();
protected:
	struct Element{
		KernelSem* kernelSem;
		Element* next;
		Element(KernelSem* myKernelSem, Element* nextElem = 0){
			kernelSem = myKernelSem;
			next = nextElem;
		}
	};

	Element* first;
	Element* last;
	int numOfElements;
	static int KerSemId;


};

#endif /* KSEML_H_ */
