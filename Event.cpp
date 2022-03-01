/*
 * Event.cpp
 *
 *  Created on: May 31, 2020
 *      Author: OS1
 */

#include "Event.h"
#include"PCB.h"
#include"KernelEv.h"
#define lock {asm{pushf; cli;}}
#define unlock asm popf
Event::Event(IVTNo ivtNo) {
	lock
	myImpl=new KernelEv(PCB::running,ivtNo);
	unlock
}

Event::~Event() {
	lock
	delete myImpl;
	unlock
}
void Event::wait(){
	lock
	myImpl->wait();
	unlock

}

