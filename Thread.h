/*
 * Thread.h
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#ifndef _thread_h_
#define _thread_h_
typedef void (*SignalHandler)();
typedef unsigned SignalId;
#define lock {asm{pushf; cli;}}
#define unlock asm popf
typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
class PCB; // Kernel's implementation of a user's thread

struct E{
	SignalId id;
	int global;
	E* next;
public:
	E(SignalId idx){
		id=idx;
		global=0;
		next=0;
	}
};
class Thread {
public:
	static E* h;
	static E* t;

 void start();
 void waitToComplete();
 virtual ~Thread();
 ID getId();
 static ID getRunningId();
 static Thread * getThreadById(ID id);
 Thread (StackSize stackSize = defaultStackSize, Time timeSlice =
 defaultTimeSlice);

 void signal(SignalId signal);
 void registerHandler(SignalId signal, SignalHandler handler);
 void unregisterAllHandlers(SignalId id);
 void swap(SignalId id, SignalHandler hand1, SignalHandler hand2);
 void blockSignal(SignalId signal);
 static void blockSignalGlobally(SignalId signal);
 void unblockSignal(SignalId signal);
 static void unblockSignalGlobally(SignalId signal);
protected:
 friend class PCB;
 friend void interrupt timer(...);

 virtual void run();
public:
 PCB* myPCB;
};
void dispatch ();
#endif


