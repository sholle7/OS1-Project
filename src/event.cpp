/*
 * event.cpp
 *
 *  Created on: Aug 27, 2021
 *      Author: OS1
 */
#include "event.h"
#include "macros.h"
#include <iostream.h>

Event::Event(IVTNo ivtNo) {
	_LOCK_
		myImpl = new KernelEv(ivtNo);
	_UNLOCK_;
}

void Event::wait() {
	 myImpl->wait();
}

void Event::signal() {
	 myImpl->signal();
}

Event::~Event() {
	_LOCK_
		if(myImpl != 0) delete myImpl;
	_UNLOCK_
}


