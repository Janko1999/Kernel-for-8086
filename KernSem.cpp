/*
 * KernelSem.cpp
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */

#include "KernSem.h"
#include"Queue.h"
#include"Lista.h"
#include"PCB.h"
#include<dos.h>
#include"SCHEDULE.H"
#include<iostream.h>
Lista KernSem::semaphores=Lista();
#define New 1
#define Ready 2
#define Running 3
#define Blocked 4
#define Finished 5
#define infinitytime 10000
#define lock {asm{pushf; cli;}}
#define unlock asm popf
KernSem::KernSem(int init) {

	semaphores.add(this);
	value=init;
	pcbs= Queue();

}

KernSem::~KernSem() {
	// TODO Auto-generated destructor stub
}
int KernSem::wait(int t){
	if(t==0) t=infinitytime;
	if (value--<=0){
        pcbs.add(PCB::running,t);
		PCB::running->status=Blocked;
		dispatch();
	};
	if(PCB::running->dblckedTime==1){
	PCB::running->dblckedTime=0;
	return 0;
	}
	else return 1;

}
int KernSem::signal(int x){
	int oldvalue=value;
	int ret=0;
	if(x<0) {return x;}
	if(x==0 || x==1){
		if(value++<0){
			PCB* y=pcbs.remove();
			y->status=Ready;
			Scheduler::put(y);
			return x;
		}
		return 0;
	}else {
		while(x>0 && oldvalue<0){
			PCB* y=pcbs.remove();
			pcbs.size--;
			y->status=Ready;
			Scheduler::put(y);
			x--;
			oldvalue++;
			ret++;

		}
		value+=ret;
return ret;
	}
}
 void KernSem::time(){
lock
	for(int j=0;j<semaphores.size;j++){
		Element* head=semaphores.get(j)->pcbs.head;
		if(semaphores.get(j)->value<0){
			while(head!=0){ if(head->timeblocked!=infinitytime)head->timeblocked--; /*cout<<head->timeblocked<<" ";*/ head=head->next;}
			//cout<<endl;
			 head=semaphores.get(j)->pcbs.head;
			while(head!=0){

				if (head->timeblocked == 0) {

					/*lock
					cout<<"Usaoooo"<<endl;
					unlock*/
							semaphores.get(j)->value++;
							PCB* nov = semaphores.get(j)->pcbs.removefrom();
							if(nov!=0){
								nov->dblckedTime=1;
							nov->status = Ready;
							Scheduler::put(nov);
							head=semaphores.get(j)->pcbs.head;}
						}
				else break;
					}
	}
	}
unlock
				}
int KernSem::getValue(){return value;}

