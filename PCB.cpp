/*
 * PCB.cpp
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */
#include<dos.h>
#include "PCB.h"
#include"Inte.h"
#include"SCHEDULE.H"
#include <iostream.h>
#include"Thread.h"
PCB* PCB::first= 0;
PCB* PCB::last = 0;
PCB* PCB::running=0;
int PCB::ID=0;
#define infinityTime 100000
PCB::PCB(Thread* thread,StackSize x,Time y ) {
	lock
	signalHead=signalTail=0;
	waitingHead=waitingTail=0;
	dblckedTime=0;
	Id=ID++;
stacksize=x;
stacksize/=sizeof(unsigned);
	status=New;
	stack=new unsigned[stacksize];
	ss=0;
	sp=0;
	bp=0;
	if(y==0) time=infinityTime;
	else
	time=y;
	myThread=thread;
	if(first==0){
		first=last=this;
	}else{
		last->next=this;
		last=last->next;
	}
	stack[stacksize - 3] = 0x200;
		stack[stacksize - 4] = FP_SEG(PCB::wrapper);
		stack[stacksize - 5] = FP_OFF(PCB::wrapper);
		ss = FP_SEG(stack + stacksize - 14);
		sp = FP_OFF(stack + stacksize - 14);
		bp = sp;
		unlock
}

PCB::~PCB() {
	lock
	delete[] stack;
	unlock
}
void PCB::signal(SignalId id){
	E* pom2=Thread::h;
	int flag;
	while(pom2!=0){
		if(pom2->id==id){
			if(pom2->global=1) flag=0;
			else flag=1;
			break;
		}
		pom2=pom2->next;
	}
	if(pom2==0) flag=1;
El* pom=signalHead;
while(pom!=0){
	if(pom->id==id){
		El* pom1=pom;
		if(pom1->locked==0 || flag==1){
		while(pom1!=0){
            pom1->handler();
			pom1=pom1->next;
		}
		}

	}

	pom=pom->next;
}
}
void PCB::blockSignal(SignalId id){
El* pom=signalHead;
while(pom!=0){
	if(pom->id==id){
		while(pom!=0){
			pom->locked=1;
			pom=pom->right;
		}
		break;
	}
	pom=pom->next;
}
}
void PCB::registerHandler(SignalId id, SignalHandler h ){
El* pom=signalHead;
El* pom1=0;
if(signalHead==0){
	signalHead=signalTail=new El(id);
	signalHead->handler=h;
	Thread::h=Thread::t=new E(id);
}
while(pom!=0){
	if(pom->id==id){
		 pom1=pom;
		while(pom->right!=0) pom=pom->right;
		pom->right=new El(id);
		pom->right->handler=h;
		break;
	}
	pom=pom->next;
}
if(pom1==0){
	signalTail->next=new El(id);
	signalTail->next->handler=h;
	signalTail=signalTail->next;
	Thread::t->next=new E(id);
	Thread::t=Thread::t->next;
}

}
void PCB::swap(SignalId id, SignalHandler h1, SignalHandler h2){
	El* pom=signalHead;
	while(pom!=0){
		if(pom->id==id){
			El* pom1=pom;
			El* pom2=pom;
			while(pom1->handler!=h1 || pom1!=0) pom1=pom1->right;
			while(pom2->handler!=h2 || pom2!=0) pom2=pom2->right;
			if(pom1==0 || pom2==0) break;
			SignalHandler h3=h1;
			pom1->handler=h2;
			pom2->handler=h3;
			break;
		}
	}

}
void PCB::unblockSignal(SignalId id){
	El* pom=signalHead;
	while(pom!=0){
		if(pom->id==id){
			while(pom!=0){
				pom->locked=0;
				pom=pom->right;
			}
			break;
		}
		pom=pom->next;
	}
}
void PCB::unregisterAllHandlers(SignalId id){
El* pom=signalHead;
El* pom1=0;
El* pom2;
El* pom3;
while(pom!=0){
	pom1=pom;
	if(pom->id==id){
		 pom2=pom;
		while(pom!=0){
		 pom3=pom;
		pom=pom->right;
		delete pom3;
		}
		break;
	}
}
if(pom2==signalTail){
	if(signalHead==signalTail)signalHead=signalTail=0;
	else {
		signalTail=pom1;
		signalTail->next=0;
	}

}
if(pom2==signalHead){
	if(signalHead==signalTail)signalHead=signalHead=0;else
	signalHead=signalHead->next;
}
pom1->next=pom2->next;
}
void PCB::wrapper(){
	PCB::running->myThread->run();
	lock
	running->status=Finished;
	lock
		cout<<"Nesto"<<endl;
		unlock
	while(PCB::running->waitingHead!=0){

		PCB::running->waitingHead->pcb->status=Ready;
		Scheduler::put(PCB::running->waitingHead->pcb);
		PCB::running->waitingHead=PCB::running->waitingHead->next;
	}
	PCB::running->waitingHead=0;
	PCB::running->waitingTail=0;
	unlock
	dispatch();


}

