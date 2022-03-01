/*
 * hello.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: OS1
 */

#include <iostream.h>
#include "Thread.h"
#include"Inte.h"
#include"Semaphor.h"
#include "Queue.h"
#include"Lista.h"
#include"KernSem.h"
#include"Global.h"
Thread* MThread;
Global* global;
#define lock {asm{pushf; cli;}}
#define unlock asm popf

/*Semaphor *s;
class A : public Thread{

	Semaphor* prvi,* drugi;
	public:
		A(Semaphor* p, Semaphor* d,StackSize stackSize= defaultStackSize, Time timeSlice =defaultTimeSlice)
			:Thread(stackSize,timeSlice){
					prvi = p;
					drugi = d;
				}
		void run(){

			for (int i = 0; i< 4; i++){
				prvi->wait(37);
				cout<< prvi->val() << " "<< PCB::running->getID() << " "<<i<<"  "<< drugi->val()<<endl;
				drugi->signal(0);
			}
		}
		~A(){
								waitToComplete();
							}
	};


	class B : public Thread{

	Semaphor* prvi,* drugi;
		public:
			B(Semaphor* p, Semaphor* d,StackSize stackSize= defaultStackSize, Time timeSlice =defaultTimeSlice)
		:Thread(stackSize,timeSlice){
				prvi = p;
				drugi = d;
			}
			void run(){

				for (int i = 0; i< 4; i++){
					prvi->wait(0);
					cout<< prvi->val() << " "<< PCB::running->getID() << " "<<i<<"  "<< drugi->val()<<endl;
						drugi->signal(2);
				}
			}

			~B(){
											waitToComplete();
										}
		};
	class C : public Thread{

			Semaphor* prvi , *drugi;
				public:
					C(Semaphor* p, Semaphor* d,StackSize stackSize= defaultStackSize, Time timeSlice =defaultTimeSlice)
								:Thread(stackSize,timeSlice){
										prvi = p;
										drugi = d;
									}
					void run(){

					for (int i = 0; i< 4; i++){
					prvi->wait(15);
					cout<< prvi->val() << " "<< PCB::running->getID() << " "<<i<<"  "<< drugi->val()<<endl;
						}
					}
					~C(){
						waitToComplete();
					}
				};

	class D : public Thread{

			Semaphor* prvi , *drugi;
		public:
			D(Semaphor* p, Semaphor* d,StackSize stackSize= defaultStackSize, Time timeSlice =defaultTimeSlice)
						:Thread(stackSize,timeSlice){
								prvi = p;
								drugi = d;
							}
			void run(){

				for (int i = 0; i< 4; i++){
									prvi->wait(11);
				cout<< prvi->val() << " "<< PCB::running->getID() << " "<<i<<"  "<< drugi->val()<<endl;

								}
			}
			~D(){
				waitToComplete();
			}
		};
class MyClass:public Thread{
public:
	MyClass(int x, Time y):Thread(x,y){}
	void run();
};
void MyClass::run(){
	lock
	cout<<"MyClass 1 before"<<endl;
	unlock
	s->wait(0);
	lock
    cout<<"MyClass 12 after"<<endl;
	unlock

}
class MyClass2:public Thread{
public:
	MyClass2(int x, Time y):Thread(x,y){}
	void run();
};

void MyClass2::run(){
	lock
		cout<<"MyClass 2 before"<<endl;

	unlock

	s->wait(0);
lock
	cout<<"MyClass 2 after"<<endl;

unlock



}
class MyClass3:public Thread{
	public: MyClass3(int x, Time y):Thread(x,y){}
	void run();
};
void MyClass3::run(){


	lock
	cout<<"MyClass3 before"<<endl;
unlock


s->wait(5);
s->signal(0);
lock
cout<<"Class3 after"<<endl;
unlock
}

*/
int userMain(int argc, char* argv[]);
void main(int argc, char* argv[])
{
	/*inic();
	s=new Semaphor(0);
    Semaphor*s = new Semaphor(0);
	Semaphor*s2 = new Semaphor(0);
	Semaphor*s3 = new Semaphor(0);
	Semaphor*s4 = new Semaphor(0);
	A* t1 = new A(s,s2);
	B* t2 = new B(s2,s3);
	C* t3 = new C(s3,s4);
	D* t4 = new D(s4,s);
    t1->start();
	t2->start();
	t3->start();
	t4->start();

	delete t1;
	delete t2;
	delete t3;
	delete t4;
/*MyClass3* x=new MyClass3(4096,500);
x->start();
x->waitToComplete();*/

/*for(int i=0;i<3000000;i++)
	for(int j=0;j<3000000;j++){}*/

	//restore();
	inic();
	userMain(argc, argv);
	restore();

}


