/*
 * PCB.h
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "PCBList.h"
#include "thread.h"
#include "iostream.h"

class Thread;
class List;

class PCB{
public:
	enum State{NEW=0, READY=1, BLOCKED=2, IDLE=3, FINISHED=4, SUSPENDED=5}; //sva stanja niti

	static void wrapper();//metoda omotac koja poziva metoud run iz thread klase
	ID getId(){return threadID;} //vraca ID niti

	Thread* getThread(){return thread;}
	State getState(){return threadState;} //vraca stanje niti
	Time getTimeSlice(){return timeSlice;}
	void setState(State st){threadState=st;} //postavlja stanje niti
	void setTimeSlice(Time ts){timeSlice=ts;}

	void startPCB(); //pokrece nit odnosno stavlja je u scheduler

	void wait_to_complete();
	void unblock();

	//konstruktor i destruktor
	PCB (StackSize stackSize , Time timeSlice,Thread* thread);
	~PCB();


	static volatile PCB* running;//staticka promenenljiva koja predstavlja trentnu nit koja se izvrsava
	static ID stID;
	StackSize stackSize;
	Time timeSlice; //quantum
	Thread* thread;
	State threadState; //stanje niti
	unsigned finishedFlag; //flag za proveru jel se nit zavrsila
	unsigned bp;
	unsigned sp;
	unsigned ss;
	unsigned* stack;
	int semTime;
	List* waitingPCBs;

	ID threadID; //ID niti
	friend void dispatch();
	friend class System;
};

#endif /* PCB_H_ */
