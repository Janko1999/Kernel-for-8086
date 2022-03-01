/*
 * Semaphore.h
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */
#ifndef _semaphor_h_
#define _semaphor_h_
typedef unsigned int Time;
class KernSem;
class Semaphor {
public:
 Semaphor (int init=1);
virtual ~Semaphor ();
 virtual int wait (Time maxTimeToWait);
 virtual int signal(int n=0);
 int val () const; // Returns the current value of the semaphore
public:
 KernSem* myImpl;
};
typedef Semaphor Semaphore;

#endif
