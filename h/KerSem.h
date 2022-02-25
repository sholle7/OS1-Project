/*
 * KerSem.h
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "PCBList.h"
#include "semaphor.h"
#include "SemList.h"
#include "SCHEDULE.H"

class SemList;
class List;

class KernelSem{
public:
	volatile int value;
	List* waitingOnSem; //lista pcbova koji cekaju na semaforu
	static SemList* allSemaphores; //lista svih semafora


	KernelSem(int in);
	~KernelSem();

	virtual int wait (Time maxTimeToWait);
	virtual void signal();
	int helper();
};



#endif /* KERSEM_H_ */
