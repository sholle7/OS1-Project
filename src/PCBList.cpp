/*
 * List.cpp
 *
 *  Created on: Aug 21, 2021
 *      Author: OS1
 */
#include "PCBList.h"
#include <iostream.h>

List::List():head(0),tail(0),cur(0),numOfNodes(0){}
List::~List(){
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
void List::putBack(PCB* p){
	_LOCK_
		if(!head)head = tail = new Node(p);
		else {
			tail->next = new Node(p);
			tail = tail->next;
		}
		numOfNodes++;
	_UNLOCK_
}
int List::getNumberOfNodes(){
	return numOfNodes;
}
PCB* List::getFirst(){
	if(head)return head->pcb;
	else return 0;
}

PCB* List::getCurrent(){
	if(cur){
		return cur->pcb;
	}
	else return 0;
}
void List::resetCurrent(){
	cur = head;
}
void List::next(){
	cur = cur->next;
}
void List::deleteFirst(){
	if(!head)return;
	Node* n = head;
	if(cur == head)cur = cur->next;
	head = head->next;
	_LOCK_
		delete n;
	_UNLOCK_
}
void List::deleteCurrent(){
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



