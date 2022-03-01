/*
 * KernelEv.h
 *
 *  Created on: May 31, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
class PCB;
class IVTEntry;
class KernelEv {
	int value;
    PCB* owner;
	IVTEntry* myEntry;
protected:
	friend class IVTEntry;
void signal();

public:
	KernelEv(PCB* pcb, unsigned char ivtNo);
	virtual ~KernelEv();
	void wait();
};

#endif /* KERNELEV_H_ */

