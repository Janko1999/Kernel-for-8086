/*
 * Queue.h
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */
#include "PCB.h"
#ifndef QUEUE_H_
#define QUEUE_H_
struct Element{
		PCB* pcb;
		Element* next;
		int timeblocked;
		Element(PCB* x,int y){
			timeblocked=y;
			pcb=x;
			next=0;
		}
	};
class Queue {
public:
int size;
Element* head;
Element* tail;
void add(PCB* x, int time);
PCB* remove();
PCB* removefrom();
Element* get(int index);
	Queue();
	virtual ~Queue();

};

#endif /* QUEUE_H_ */
