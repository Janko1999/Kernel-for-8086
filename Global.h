/*
 * Global.h
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_
#include"Thread.h"
#include"PCB.h"
#define New 1
#define Ready 2
#define Running 3
#define Blocked 4
#define Finished 5
#define lock {asm{pushf; cli;}}
#define unlock asm popf
class Global:public Thread{
public:
	Global():Thread(4096,1){

	}
	void run(){
		while(1){}
	}
	virtual ~Global();
	//void start();
};

#endif /* GLOBAL_H_ */
