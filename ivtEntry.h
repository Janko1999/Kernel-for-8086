/*
 * IVTEntry.h
 *
 *  Created on: May 31, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
typedef void interrupt (*Interrupt)(...);

class KernelEv;

class IVTEntry {
	unsigned char entry;
	Interrupt oldRoute;
	Interrupt newRoute;
	KernelEv* linked;

public:
	IVTEntry(unsigned char ivtNo, Interrupt newRoutine);
	virtual ~IVTEntry();
	static IVTEntry* getIVTEntry(unsigned char ivtNo);
	static IVTEntry* IVTArray[256];
	void callOldRoutine();
	void signalLinked();
	friend class KernelEv;
	void initialize(KernelEv* event);
	void restore();
	};


#endif /* IVTENTRY_H_ */
