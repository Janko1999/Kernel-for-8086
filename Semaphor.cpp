/*
 * Semaphore.cpp
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */

#include "Semaphor.h"
#include"Lista.h"
#include"KernSem.h"
#define lock {asm{pushf; cli;}}
#define unlock asm popf
Semaphor::Semaphor(int init) {
	myImpl=new KernSem(init);
}

Semaphor::~Semaphor() {
myImpl->semaphores.remove(myImpl);
}
int Semaphor::signal(int x) {
	lock
	int y= myImpl->signal(x);
	unlock
	return y;}
int Semaphor::wait(Time x) {
	lock
	int z= myImpl->wait(x);
	unlock
	return z;
}
int Semaphor::val() const{return myImpl->value;}
