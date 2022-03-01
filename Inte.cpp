/*
 * Inte.cpp
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#include"Inte.h"
#include"PCB.h"
#include"Thread.h"
#include"SCHEDULE.H"
#include<dos.h>
#include"KernSem.h"
#include"Global.h"

//extern void tick();
#define lock {asm{pushf; cli;}}
#define unlock asm popf
unsigned tss,tsp,tbp,oldISeg,oldIOff;
 volatile Time counter=defaultTimeSlice;
extern Thread* MThread;
extern Global* global;
void inic(){
	lock
	asm{
		push es
		push ax

		mov ax,0
		mov es,ax // es = 0

		// pamti staru rutinu
		mov ax, word ptr es:0022h
		mov word ptr oldISeg, ax
		mov ax, word ptr es:0020h
		mov word ptr oldIOff, ax

		// postavlja novu rutinu
		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer

		// postavlja staru rutinu
        // na int 60h
		mov ax, oldISeg
		mov word ptr es:0182h, ax
		mov ax, oldIOff
		mov word ptr es:0180h, ax

		pop ax
		pop es

	}
	unlock
	MThread=new Thread();
	PCB::running=MThread->myPCB;
	PCB::running->status=Running;
	global=new Global();
	global->start();
}


void restore(){
	lock
	asm {

		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr oldISeg
		mov word ptr es:0022h, ax
		mov ax, word ptr oldIOff
		mov word ptr es:0020h, ax

		pop ax
		pop es

	}
	delete global;
	unlock
}
 void interrupt timer(...){

	 if(disp!=1){counter--; KernSem::time(); }
	 if(disp || counter==0){

	 asm{
		 mov tsp,sp
		 mov tss,ss
		 mov tbp,bp
	 }
	 PCB::running->ss=tss;
	 PCB::running->sp=tsp;
	 PCB::running->bp=tbp;

	 if(PCB::running->status==Running){
		 Scheduler::put(PCB::running);
		 PCB::running->status=Ready;
	 }PCB::running=Scheduler::get();
	 if (PCB::running==0)
	 PCB::running=global->myPCB;
	 PCB::running->status=Running;
	 counter=PCB::running->time;

	 tss=PCB::running->ss;
	 tbp=PCB::running->bp;
	 tsp=PCB::running->sp;
	 asm{
	 		 mov sp,tsp
	 		 mov ss,tss
	 		 mov bp,tbp
	 	 }
	 }
	 if(!disp) asm int 60h;
	 disp=0;
	 //tick();
 }


