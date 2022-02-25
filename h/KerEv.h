/*
 * KerEv.h
 *
 *  Created on: Aug 27, 2021
 *      Author: OS1
 */

#ifndef KEREV_H_
#define KEREV_H_
#include "event.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "IVTEntry.h"
class PCB;
class Event;

class KernelEv{
public:
	 KernelEv(IVTNo ivtNo);
	 ~KernelEv();
	 void wait ();
	 void signal();
	 IVTNo ivtNum;

	 PCB* PCB_Event;
	 int val;



};



#endif /* KEREV_H_ */
