/*
 * PCB.h
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */
#define New 1
#define Ready 2
#define Running 3
#define Blocked 4
#define Finished 5
#ifndef PCB_H_
#define PCB_H_
#define lock {asm{pushf; cli;}}
#define unlock asm popf
#include"Thread.h"
struct Elem{
	PCB* pcb;
	Elem* next;
	Elem(PCB* x){
		pcb=x;
		next=0;
	}
};

struct El{
	SignalId id;
	SignalHandler handler;
	int locked;
	El* next;
	El* right;
public:
	El(SignalId idx){
		id=idx;
		handler=0;
		locked=0;
		next=0;
		right=0;

	}
};
class PCB {
static int ID;
private:

El* signalHead;
El* signalTail;
public:
void signal(SignalId signal);
void registerHandler(SignalId signal, SignalHandler handler);
void unregisterAllHandlers(SignalId id);
void swap(SignalId id, SignalHandler hand1, SignalHandler hand2);
void blockSignal(SignalId signal);
static void blockSignalGlobally(SignalId signal);
void unblockSignal(SignalId signal);
static void unblockSignalGlobally(SignalId signal);
int Id;
int stacksize;
int dblckedTime;
static PCB* first;
static PCB* last;
PCB* next;
public:unsigned status;
unsigned* stack;
unsigned ss;
unsigned sp;
unsigned bp;
Time time;
Thread* myThread;
	friend Thread;
	static PCB* running;
	Elem* waitingHead;
	Elem* waitingTail;
	int getID(){return Id;}
	static void wrapper();
	PCB(Thread* t,StackSize x, Time y);
	virtual ~PCB();
};

#endif /* PCB_H_ */
