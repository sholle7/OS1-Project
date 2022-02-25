/*
 * IdleThr.h
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#ifndef IDLETHR_H_
#define IDLETHR_H_
#include "thread.h"

class IdleThread: public Thread{
public:
	static volatile int temp;
	IdleThread();
	virtual void run();
};



#endif /* IDLETHR_H_ */
