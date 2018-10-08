/*
 * locks.h
 *
 *  Created on: Aug 2, 2018
 *      Author: OS1
 */

#ifndef LOCKS_H_
#define LOCKS_H_

#include "Global.h"
#include "STDIO.H"


int syncPrintf(const char *format, ...);

#define lock\
			{Global::lockFlag = 0;\
			Global::lockCounter++;\
			}\

#define unlock\
			{Global::lockCounter--;\
				if(Global::lockCounter <= 0){\
					Global::lockFlag = 1;\
					Global::lockCounter = 0;\
					if(Global::requestedDispatch) timer();\
				}\
			}\


#endif /* LOCKS_H_ */
