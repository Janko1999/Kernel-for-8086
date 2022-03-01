/*
 * KernelEv.cpp
 *
 *  Created on: May 31, 2020
 *      Author: OS1
 */

#include "KernelEv.h"

#include "ivtEntry.h"
#include "PCB.h"
#include"SCHEDULE.H"
#define New 1
#define Ready 2
#define Running 3
#define Blocked 4
#define Finished 5
KernelEv::KernelEv(PCB* pcb, unsigned char ivtNo) {
	owner=pcb;
	value = 1;
	myEntry = IVTEntry::IVTArray[ivtNo];
	myEntry->initialize(this);

}

KernelEv::~KernelEv() {
	KernelEv::signal();
	myEntry->restore();
}


void KernelEv::wait() {
	if (PCB::running ==owner && value == 1) {
		value = 0;
		PCB::running->status = Blocked;
		dispatch();
	}
}
void KernelEv::signal(){
	if (value == 0) {
		value = 1;
		owner->status = Ready;
		Scheduler::put((PCB*) owner);
		dispatch();
	}
}
