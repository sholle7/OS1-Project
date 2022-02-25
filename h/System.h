/*
 * system.h
 *
 *  Created on: Aug 20, 2021
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "IdleThr.h"

typedef void interrupt (*pInterrupt)(...);
extern pInterrupt oldISR;

#define _LOCK_ System::lockFlag++;

#define _UNLOCK_\
{\
	System::lockFlag--;\
	if(System::context_switch_on_demand && System::lockFlag == 0) dispatch();\
}

void tick();

class PCB;
class Thread;
class List;


class System{
public:

	static volatile int context_switch_on_demand;
	static volatile unsigned int counter;
	static volatile unsigned lockFlag;
	static void interrupt timer(...);

	static void inic();
	static void restore();
	static PCB* PCB_main; //cuvanje PCB main-a
	static IdleThread* THR_idle; //cuvane idle niti
	static List* allPCBs;
	friend void dispatch();
	friend class Thread;
};


#endif /* SYSTEM_H_ */

