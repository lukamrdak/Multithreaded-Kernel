/*
 * IdleThr.h
 *
 *  Created on: Aug 3, 2018
 *      Author: OS1
 */

#ifndef IDLETHR_H_
#define IDLETHR_H_


#include "thread.h"

class IdleThread:Thread {
public:
	IdleThread();
	~IdleThread();
	void run();
	void start();
/*private:
	friend void initIdle();
	friend void undoInit();
	friend void undoInitThreads();
*/
protected:
	static IdleThread* idleThread; 		//ovo dvoje inicijalizovati u init-u, tako da ovo bude prva nit koja se dodaje u scheduler, da bi mogla da se odmah izvadi
	static PCB* idleThreadPCB;			//kad se kreira PCB on se ne doda u listu kao prvi i onda se nakon toga ukloni iz liste

	friend class Global;
	friend void initIdleThread();
};

static void initIdleThread();

#endif /* IDLETHR_H_ */
