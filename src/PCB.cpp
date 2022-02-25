/*
 * PCB.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#include "PCB.h"
#include "macros.h"
#include "SCHEDULE.H"
#include <dos.h>
#include <iostream.h>

ID PCB::stID = 0;
volatile PCB* PCB::running = 0;
void PCB::wrapper(){
	//moze se pristupiti ili preko pokazivaca this ili preko globlne promenljive running
	if(running->thread){
		running->thread->run();
		_LOCK_
			running->unblock();
			//kada se nit zavrsi postavi joj se stanje na finished kako ga ne bi vracali nazad u scheduler
			running->threadState = PCB::FINISHED;
			running->finishedFlag = 1;
		_UNLOCK_;
	}
	//vrsi se promena konteksta
	dispatch();
}

PCB::PCB(StackSize stSize , Time tSlice, Thread* thr){
			if (stSize<0 || stSize>maxStSz) stackSize = maxStSz/sizeof(unsigned);
			else stackSize = stSize / sizeof(unsigned);

			waitingPCBs = new List();
			semTime = -2;
			timeSlice = tSlice;
			thread = thr;
			threadState = NEW;
			threadID = stID++;
			finishedFlag = 0;
			System::allPCBs->putBack(this);
			// alokacija steka niti
			this->bp = this->sp = this->ss = 0;
			if(stackSize!=0 && threadID !=0){
					unsigned* stack = new unsigned[stackSize];
					// setovanje I flega u pocetnom PSW-u za nit
					stack[stackSize-1] =0x200;
					//stack[stackSize - 12] = 0;
						// postavljanje adrese funkcije koju ce nit da izvrsava
					#ifndef BCC_BLOCK_IGNORE
						stack[stackSize-2] = FP_SEG(PCB::wrapper);
						stack[stackSize-3] = FP_OFF(PCB::wrapper);
						//svi sacuvani registri pri ulasku u interrupt rutinu
						sp = FP_OFF(stack+stackSize-12);
						ss = FP_SEG(stack+stackSize-12);
						bp = FP_OFF(stack+stackSize-12);
					#endif
			}
}

PCB::~PCB(){
	_LOCK_
		thread->myPCB = 0;
		thread = 0;
		delete waitingPCBs;
		if(stackSize!=0 && threadID != 0) delete[] stack;
	_UNLOCK_
}

void PCB::startPCB(){
	if(threadState == NEW){
		//nit se pokrece jednom i onda je spremna za izvrsavanje i ubacuje se u scheduler
		threadState = READY;
		Scheduler::put(this);
	}
}
void PCB::wait_to_complete(){
	_LOCK_
	if(PCB::running != this && this->getState()!=PCB::IDLE &&this->getState()!= PCB::NEW && this->getState()!= PCB::FINISHED){
			if(this->finishedFlag ==0){
					PCB::running->setState(PCB::BLOCKED);
					if(PCB::running)waitingPCBs->putBack((PCB*)PCB::running);
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
void PCB::unblock(){
	_LOCK_
	for(waitingPCBs->resetCurrent(); waitingPCBs->getCurrent()!=0;/* waitingPCBs->next()*/){
		PCB* p= waitingPCBs->getCurrent();
		p->setState(PCB::READY);
		Scheduler::put(p);
		waitingPCBs->deleteFirst();
	}
	_UNLOCK_
}


