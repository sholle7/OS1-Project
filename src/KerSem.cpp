/*
 * KerSem.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */
#include "KerSem.h"
#include <iostream.h>

SemList* KernelSem::allSemaphores = new SemList();

KernelSem::KernelSem(int in){
	_LOCK_
		waitingOnSem = new List();
		allSemaphores->putBack(this);
		value = in;
	_UNLOCK_
}
KernelSem::~KernelSem(){
	_LOCK_
		delete waitingOnSem;
	_UNLOCK_
}
void KernelSem::signal(){
	_LOCK_
	if(value++ < 0){
		waitingOnSem->getFirst()->setState(PCB::READY); //postavljamo ready flag
		Scheduler::put(waitingOnSem->getFirst()); //dohvatamo prvu blokiranu nit na semaforu
		waitingOnSem->deleteFirst(); //uklanjamo je iz liste blokiranih niti na semaforu
	}
	_UNLOCK_
}
int KernelSem::wait(Time maxTimeToWait){
	_LOCK_

		if(--value<0){

			if(maxTimeToWait>0) {
				PCB::running->semTime = maxTimeToWait;
				_UNLOCK_
				return helper();

			}

			if(maxTimeToWait<0) {
					_UNLOCK_
					return -1;
			}

			else {
				_UNLOCK_
				return helper();
			}
		}
		else{
			_UNLOCK_
			return 1;
		}
}
int KernelSem::helper(){
	_LOCK_

		waitingOnSem->putBack((PCB*)PCB::running);
		PCB::running->setState(PCB::BLOCKED);

	_UNLOCK_
		dispatch();
	_LOCK_
		if(PCB::running->semTime == 0){
			PCB::running->semTime = -2;
			_UNLOCK_
			return 0;
		}
		else{
			_UNLOCK_
			return 1;
		}
}



