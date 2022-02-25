/*
 * IdleThr.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */
#include "IdleThr.h"
#include "macros.h"
#include "PCB.h"

volatile int IdleThread::temp = 1;
IdleThread::IdleThread():Thread(defaultStackSize,1){ //pozivanje konstruktora natklase sa defaultnim argumentima
	myPCB->setState(PCB::IDLE);
}

void IdleThread::run(){
	while(temp); //vrti se u beskonacnoj petlji
}


