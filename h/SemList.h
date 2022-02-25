/*
 * SemList.h
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_
#include "KerSem.h"
class KernelSem;
class SemList{
public:
	//lista za cuvanje semafora
		struct Node{
				KernelSem* sem;
				Node * next;
				Node(KernelSem* s){sem=s;next=0;}
		};

		Node* head, *tail, *cur;
		int numOfNodes; //broj cvorova

		SemList();
		~SemList();

		void putBack(KernelSem* p); //dodavanje na kraj liste

		KernelSem* getCurrent(); //dohvatanje trenutnog elementa
		KernelSem* getFirst();

		int getNumberOfNodes();

		void resetCurrent();
		void next();

		void deleteFirst();
		void deleteCurrent();

		void updateSemaphores();

};


#endif /* SEMLIST_H_ */
