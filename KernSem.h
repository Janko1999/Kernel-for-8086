/*
 * KernelSem.h
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_
#include"Queue.h"
class Lista;
class KernSem {
public:

	static Lista semaphores;
	Queue pcbs;
	int value;
	KernSem(int init);
	virtual ~KernSem();
	int wait(int x);
	int signal(int y);
	static void time();
	int getValue();
};

#endif /* KERNSEM_H_ */
