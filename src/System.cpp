/*
 * system.cpp
 *
 *  Created on: Aug 20, 2021
 *      Author: OS1
 */
#include "PCB.h"
#include <dos.h>
#include "macros.h"
#include "SCHEDULE.H"
#include "System.h"
#include <iostream.h>
#include "KerSem.h"

volatile int System::context_switch_on_demand = 0;
volatile unsigned int System::counter = 50;
volatile unsigned System::lockFlag = 0;
PCB* System::PCB_main = 0;
IdleThread* System::THR_idle = 0;
pInterrupt oldISR = 0;
List* System::allPCBs = 0;
int mask;

void interrupt System::timer(...){
	static volatile unsigned tsp;
	static volatile unsigned tss;
	static volatile unsigned tbp;

	mask = 0;
	if(context_switch_on_demand) mask = 1;
	else {
		 // poziv stare prekidne rutine
		 // koja se nalazila na 08h, a sad je na 60h;
		 // poziva se samo kada
		 // nije zahtevana promena konteksta
		 // tako da se stara rutina poziva
		 // samo kada je stvarno doslo do prekida
	     if(counter != 0) {
	         counter--;
	         if(counter==0) mask = 1;
	     }
	     asm int 60h;
	     tick();
	     KernelSem::allSemaphores->updateSemaphores();
	}
	if (mask) {
				if(lockFlag == 0){

					context_switch_on_demand = 0;
					asm{
						mov tsp, sp
						mov tss, ss
						mov tbp, bp
					}
					PCB::running->bp = tbp;
					PCB::running->sp = tsp;
					PCB::running->ss = tss;

					if(PCB::running->finishedFlag == 0 && PCB::running->getState() != PCB::BLOCKED && PCB::running->getState() != PCB::IDLE && PCB::running->getState() == PCB:: READY ){
						Scheduler::put((PCB*)PCB::running);
					}
					// scheduler
					PCB::running = Scheduler::get();
					if (PCB::running == 0){

						PCB::running = System::THR_idle->myPCB;
					}
						tbp = PCB::running->bp;
					    tsp = PCB::running->sp;
						tss = PCB::running->ss;

						counter = PCB::running->getTimeSlice();

						asm {
							// restauriranje bp,sp i ss
							mov bp, tbp
							mov sp, tsp
							mov ss, tss
						}

				}
				else context_switch_on_demand = 1;
	}
}


void System::inic(){
		_LOCK_
		allPCBs = new List();
		PCB_main = new PCB(0,0,0); //ne treba da pravimo stek za main nit i timeSlice = 0 odnosno ima neograniceno vreme izvrsavanja na procesoru
		PCB_main->setState(PCB::READY);
		PCB::running = PCB_main;

		THR_idle = new IdleThread();
		_UNLOCK_

		oldISR = getvect(0x08);
		setvect(0x08,timer); //podmece nasu prekidnu rutinu na ulaz 08h
		setvect(0x60,oldISR); //postavlja staru prekidnu rutinu na ulaz 60h

}

void System::restore(){
		setvect(0x08,oldISR);
		_LOCK_
			delete PCB_main;
			delete allPCBs;
			delete THR_idle;
			delete KernelSem::allSemaphores; //brisanje liste svih semafora
		_UNLOCK_
}
