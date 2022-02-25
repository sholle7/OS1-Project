/*
 * hello.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: OS1
 */

#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.H"
#include "macros.h"
#include "thread.h"
#include "PCB.h"
#include "IdleThr.h"
#include "PCBList.h"
#include "System.h"

int retValue;
extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{

		System::inic();
		retValue = userMain(argc,argv);
		System::restore();

		return retValue;
}





