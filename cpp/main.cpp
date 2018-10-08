/*
 * main.cpp
 *
 *  Created on: Aug 3, 2018
 *      Author: OS1
 */

#include "Global.h"
#include "IdleThr.h"
#include "MainThr.h"
#include "locks.h"

#include "pcb.h"
#include "thread.h"
#include "Global.h"

#include "pcb.h"
#include "ThrLst.h"

int main(int argc, char** argv){
	Global::initialiseInterruptRoutine();
	Global::init(argc, argv);
	int returnValue = MainThread::getMainRetValue();

	Global::restoreInterruptRoutine();
	Global::restore();
	syncPrintf("POvratna vrednost je %d", returnValue);
	 return returnValue;
}
