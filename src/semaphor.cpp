/*
 * semaphor.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */
#include "semaphor.h"

Semaphore::Semaphore(int init){
	_LOCK_
		myImpl = new KernelSem(init);
	_UNLOCK_
}
Semaphore::~Semaphore(){
	if(myImpl != 0){
		_LOCK_
			delete myImpl;
		_UNLOCK_
		myImpl = 0;
	}
}
void Semaphore::signal(){
	myImpl->signal();
}
int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}
int Semaphore::val()const{
	return myImpl->value;
}


