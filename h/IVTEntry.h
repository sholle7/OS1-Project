/*
 * IVTEntry.h
 *
 *  Created on: Aug 27, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "KerEv.h"
#include "macros.h"
#include "dos.h"



typedef unsigned char IVTNo;

class KernelEv;
class IVTEntry{
public:
	IVTEntry(IVTNo iv,pInterrupt pI);
	~IVTEntry();

	void signal();

	void setEvent(KernelEv* ke);

	pInterrupt newIntR, oldIntR;
	IVTNo ivtNO;
	KernelEv* kernEv;
	static IVTEntry* IVTable[256]; //ivtp tabela
};




#endif /* IVTENTRY_H_ */
