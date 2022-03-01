/*
 * Queue.cpp
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */

#include "Queue.h"
#define infinitytime 10000
Queue::Queue() {
	// TODO Auto-generated constructor stub
head=0;
tail=0;
size=0;
}


Queue::~Queue() {
	// TODO Auto-generated destructor stub
}
void Queue::add(PCB* x,int y){

	if(head==0){
		tail=head=new Element(x,y);
	}
	else{
		if(y==infinitytime){
		tail->next=new Element(x,y);
		tail=tail->next;
	}else{
		Element*pom=head;
	Element* pom1=0;
	while(pom!=0 && pom->timeblocked<y){pom1=pom; pom=pom->next;}
		if(pom==0){
		tail->next=new Element(x,y);
		tail=tail->next;
		}
		if(pom1==0){
			Element* novi=new Element(x,y);
			novi->next=head;
			head=novi;
		}else{
			Element* nov=new Element(x,y);
			nov->next=pom;
			pom1->next=nov;
		}
	}
}
	size++;
}
PCB* Queue::remove(){
	Element* pom=head;
	if(head==tail){
		PCB* pom1=head->pcb;
		delete head;
		delete tail;
		head=0;
		tail=0;
		size--;
		return pom1;
	}
	while(pom->next!=tail) pom=pom->next;
	PCB* pom1=tail->pcb;
	delete tail;
	tail=pom;
	tail->next=0;
	size--;
	return pom1;

}
PCB* Queue::removefrom(){
	if(head!=0){
PCB* pom=head->pcb;
Element* pomh=head;
head=head->next;
if(head==0) tail=0;
delete pomh;
size--;
return pom;
	}else return 0;
}

Element* Queue::get(int index){
int i=0;
Element* pom=head;
while(i!=index){
	i++;
	pom=pom->next;}
return pom;
}

