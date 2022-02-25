/*
 * thread.h
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // tdefaultTimeSliceime, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;


class PCB; // Kernel's implementation of a user's thread
class List;

class Thread {

public:
	 void start();
	 void waitToComplete();

	 virtual ~Thread();
	 ID getId();

	 static ID getRunningId();
	 static Thread* getThreadById(ID id);

protected:
	 friend class PCB;
	 Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	 virtual void run() {}

private:
	 PCB* myPCB;
	 friend class System;
	 friend class IdleThread;
};

void dispatch ();

#endif /* THREAD_H_ */
