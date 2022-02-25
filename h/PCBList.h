/*
 * List.h
 *
 *  Created on: Aug 21, 2021
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_
#include "macros.h"
#include "PCB.h"
class PCB;
class System;

//lista za cuvanje PCB-ova
class List{
public:
	struct Node{
			PCB* pcb;
			Node * next;
			Node(PCB* p){pcb=p;next=0;}
	};

	Node* head, *tail, *cur;
	int numOfNodes; //broj cvorova

	List();
	~List();

	void putBack(PCB* p); //dodavanje na kraj liste

	PCB* getCurrent(); //dohvatanje trenutnog elementa
	PCB* getFirst();

	int getNumberOfNodes();

	void resetCurrent();
	void next();

	void deleteFirst();
	void deleteCurrent();

};





#endif /* PCBLIST_H_ */
