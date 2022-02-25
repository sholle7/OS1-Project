/*
 * SemList.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */
#include "SemList.h"
#include <iostream.h>

SemList::SemList():head(0),tail(0),cur(0),numOfNodes(0){}
SemList::~SemList(){
	_LOCK_
		while(head){
			cur = head;
			head = head->next;
			delete cur;
		}
		numOfNodes = 0;
		head=0;
		tail=0;
		cur=0;
	_UNLOCK_
}
void SemList::putBack(KernelSem* p){
	_LOCK_
		if(!head)head = tail = new Node(p);
		else {
			tail->next = new Node(p);
			tail = tail->next;
		}
		numOfNodes++;
	_UNLOCK_
}
int SemList::getNumberOfNodes(){
	return numOfNodes;
}
KernelSem* SemList::getFirst(){
	if(head)return head->sem;
	else return 0;
}

KernelSem* SemList::getCurrent(){
	if(cur){
		return cur->sem;
	}
	else return 0;
}
void SemList::resetCurrent(){
	cur = head;
}
void SemList::next(){
	cur = cur->next;
}
void SemList::deleteFirst(){
	if(!head)return;
	Node* n = head;
	if(cur == head)cur = cur->next;
	head = head->next;
	_LOCK_
		delete n;
	_UNLOCK_
}
void SemList::deleteCurrent(){
	if(!cur)return;
	Node* n = head;
	if(cur == head){
		head = head->next;
		cur = head;
		_LOCK_
			delete n;
		_UNLOCK_
	}
	else{
		while(n->next!=cur)n = n->next;
		if(cur!=tail){
			n->next = cur->next;
			n = cur;
			cur = cur->next;
			_LOCK_
				delete n;
			_UNLOCK_
		}
		else{
			n->next = 0;
			cur = n;
			n = tail;
			tail = cur;
			_LOCK_
				delete n;
			_UNLOCK_
		}
	}
}
void SemList::updateSemaphores(){
	_LOCK_
	for(resetCurrent(); getCurrent() != 0; next()){ //for petlja za prolaz kroz sve semafore
		KernelSem* tmpKerSem = getCurrent(); //dohvata tekuci semafor iz liste semafora
		List* tmpList = tmpKerSem->waitingOnSem; //dohvata listu blokiranih niti iz tekuceg semafora
		for(tmpList->resetCurrent(); tmpList->getCurrent() !=0 ; ){//for petlja za prolaz kroz sve niti blokirane na tekucem semaforu
			if(tmpList->getCurrent()->semTime > 0){//ispitivanje da li datu nit treba odblokirati
				tmpList->getCurrent()->semTime--;
				if(tmpList->getCurrent()->semTime == 0){//nit treba da se odblokira
									PCB* pcb = tmpList->getCurrent();//dohvatanje pcb niti koja treba da se odblokira
									tmpList->deleteCurrent();
									if(pcb){
										pcb->setState(PCB::READY);
										Scheduler::put(pcb);
										//tmpKerSem->value++;
									}
				}
				else{
					tmpList->next();
				}
			}
			else{
				tmpList->next();
			}
		}
	}
	_UNLOCK_
}





