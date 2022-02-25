/*
 * thread.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */
#include "thread.h"
#include "macros.h"
#include <iostream.h>
#include "PCB.h"

Thread::Thread(StackSize stackSize,Time timeSlice) {
	_LOCK_
		myPCB = new PCB(stackSize,timeSlice,this);
	_UNLOCK_
}
Thread::~Thread(){
	_LOCK_
		delete myPCB;
	_UNLOCK_
}

ID Thread::getId(){
	return this->myPCB->getId();
}
ID Thread::getRunningId(){
	return PCB::running->getId();
}
Thread* Thread::getThreadById(ID id){

	for(System::allPCBs->resetCurrent(); System::allPCBs->getCurrent() != 0; System::allPCBs->next()){
		PCB* p = System::allPCBs->getCurrent();
		if(p->getId() == id) return p->getThread();
	}

	return 0;
}
void Thread::waitToComplete(){

	myPCB->wait_to_complete();

}
void Thread::start(){
	_LOCK_
		myPCB->startPCB();
	_UNLOCK_
}

void dispatch(){
	lock
			System::context_switch_on_demand = 1;
			System::timer();
	unlock
}
