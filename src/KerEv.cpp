/*
 * KerEv.cpp
 *
 *  Created on: Aug 27, 2021
 *      Author: OS1
 */
#include "KerEv.h"

KernelEv::KernelEv(IVTNo ivtNo){
	_LOCK_

		IVTEntry::IVTable[ivtNo]->oldIntR = getvect(ivtNo);
		setvect(ivtNo, IVTEntry::IVTable[ivtNo]->newIntR);
		ivtNum = ivtNo;
		val = 1; //vrednost semafora
		if(PCB::running->getState() != PCB::IDLE) PCB_Event = (PCB*)PCB::running;
		if(IVTEntry::IVTable[ivtNo] != 0) IVTEntry::IVTable[ivtNo]->setEvent(this);
	_UNLOCK_
}
KernelEv::~KernelEv(){
	_LOCK_
		PCB_Event=0;
		IVTEntry::IVTable[ivtNum]->kernEv = 0;
		IVTEntry::IVTable[ivtNum]->newIntR = 0;
		setvect(ivtNum, IVTEntry::IVTable[ivtNum]->oldIntR);
		IVTEntry::IVTable[ivtNum] = 0;
	_UNLOCK_
}

void KernelEv::wait(){
	_LOCK_
	if(val == 1){
			if(PCB::running == PCB_Event){
				val = 0;
				PCB::running->setState(PCB::BLOCKED);
				_UNLOCK_
				dispatch();
			}
			else{
				_UNLOCK_
			}
	}
	else{
		_UNLOCK_
	}
}
void KernelEv::signal(){
	_LOCK_
	if(val == 0){
		PCB_Event->setState(PCB::READY);
		Scheduler::put(PCB_Event);
		val = 1;
		_UNLOCK_
		dispatch();
	}
	else{
		_UNLOCK_
	}
}


