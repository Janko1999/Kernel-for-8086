/*
 * Thread.cpp
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */
#include"SCHEDULE.H"
#include<iostream.h>
#include "Thread.h"
#include"PCB.h"
#include"dos.h"
#include"Inte.h"
#include"Global.h"
#define lock {asm{pushf; cli;}}
#define unlock asm popf
#define New 1
#define Ready 2
#define Running 3
#define Blocked 4
#define Finished 5
unsigned disp=0;
extern Global* global;
E* Thread::h=0;
E* Thread::t=0;
Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock
	myPCB=new PCB(this,stackSize, timeSlice);
	if(PCB::running == 0)
		PCB::running = this->myPCB;
	unlock
}
void Thread::run() {

}

Thread::~Thread() {
	lock
	delete myPCB;
	unlock
}

void Thread::start(){
	myPCB->status=Ready;
	Scheduler::put(myPCB);
}
ID Thread::getRunningId(){
	return PCB::running->getID();
}
void Thread::signal(SignalId id){
	myPCB->signal(id);
}
void Thread::blockSignal(SignalId id){
	myPCB->blockSignal(id);
}
void Thread::unblockSignal(SignalId id){
	myPCB->unblockSignal(id);
}
void Thread::registerHandler(SignalId id, SignalHandler handler){
	myPCB->registerHandler(id, handler);
}
void Thread::unregisterAllHandlers(SignalId id){
	myPCB->unregisterAllHandlers(id);
}
void Thread::swap(SignalId id, SignalHandler handle1, SignalHandler handle2){
	myPCB->swap(id,handle1,handle2);
}
void Thread::blockSignalGlobally(SignalId id){
	E* pom=h;
	while(pom!=0){
		if(pom->id==id){
			pom->global=1;
			break;
		}
		pom=pom->next;
	}
}
void Thread::unblockSignalGlobally(SignalId id){
	E* pom=h;
		while(pom!=0){
			if(pom->id==id){
				pom->global=0;
				break;
			}
			pom=pom->next;
		}
}
Thread * Thread::getThreadById(ID id){
	PCB* pom;
	while(pom!=0 && pom->getID()!=id){
		pom=pom->next;
	}
	if(pom!=0){
		return pom->myThread;
	}else return 0;
}
void Thread::waitToComplete(){
	lock
	if (myPCB->status == New || myPCB->status == Finished || myPCB == PCB::running || this==global) {
			unlock
			return;
		}else
	{ lock
		cout<<"usao kao"<<endl;
	unlock
		PCB::running->status=Blocked;
		if(myPCB->waitingHead==0)myPCB->waitingHead=myPCB->waitingTail=new Elem(PCB::running);
		else{
		myPCB->waitingTail->next=new Elem(PCB::running);
		myPCB->waitingTail=myPCB->waitingTail->next;
		}
		unlock
		dispatch();
	}
}
void dispatch(){
	lock
	disp=1;
	timer();
	unlock
}
