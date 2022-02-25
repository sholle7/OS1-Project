/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 27, 2021
 *      Author: OS1
 */
#include "IVTEntry.h"
#include <iostream.h>

IVTEntry* IVTEntry::IVTable[256] = {0};

IVTEntry::IVTEntry(IVTNo iv,pInterrupt pI):kernEv(0), oldIntR(pI), newIntR(pI),ivtNO(iv){
	_LOCK_
		//oldIntR = getvect(iv);
		//setvect(iv, newIntR);
		IVTEntry::IVTable[iv] = this;
	_UNLOCK_
}
IVTEntry::~IVTEntry(){}

void IVTEntry::setEvent(KernelEv* ke){
	_LOCK_
		kernEv = ke;
	_UNLOCK_
}
void IVTEntry::signal(){
	_LOCK_
	    if(kernEv)kernEv->signal();
	_UNLOCK_
}


