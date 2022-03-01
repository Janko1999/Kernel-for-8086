/*
 * IVTEntry.cpp
 *
 *  Created on: May 31, 2020
 *      Author: OS1
 */

#include "ivtEntry.h"

#include"KernelEv.h"
#include<DOS.H>
IVTEntry* IVTEntry::IVTArray[] = { 0 };
#define PREPAREENTRY(entryNo, callOldRout)\
		void interrupt newRout##entryNo(...);\
		IVTEntry ivtEntry##entryNo(entryNo, newRout##entryNo);\
		void interrupt newRout##entryNo(...) {\
			ivtEntry##entryNo.signalLinkedEvent();\
			if (callOldRout == 1)\
				ivtEntry##entryNo.callOldRoutine();\
		}
IVTEntry::IVTEntry(unsigned char ivtNo, Interrupt newRoutine) {
	    entry = ivtNo;
		oldRoute = 0;
		newRoute = newRoutine;
		linked = 0;
		IVTEntry::IVTArray[entry] = this;

}
IVTEntry* IVTEntry::getIVTEntry(unsigned char ivtNo){
	if (ivtNo >= 0 && ivtNo <= 255) {
			return IVTArray[ivtNo];
		}
		else {
			return 0;
		}
}
IVTEntry::~IVTEntry() {
	IVTEntry::IVTArray[entry] = 0;
}
void IVTEntry::callOldRoutine(){
	if (oldRoute != 0) {
			(*oldRoute)();
		}
}
void IVTEntry::initialize(KernelEv* event) {
	if (oldRoute == 0) {
		linked = event;
#ifndef BCC_BLOCK_IGNORE
		oldRoute = getvect(entry);
		setvect(entry, newRoute);
#endif
	}
}

void IVTEntry::signalLinked() {
	linked->signal();
}

void IVTEntry::restore() {
	if (oldRoute != 0) {
#ifndef BCC_BLOCK_IGNORE
		setvect(entry, oldRoute);
#endif
		oldRoute = 0;
	}
}

