/*
 * Lista.h
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */

#ifndef LISTA_H_
#define LISTA_H_

class KernSem;
struct element{
	KernSem* info;
		element* next;
		element(KernSem* x){
			info=x;
			next=0;
		}
	};
class Lista {
public:
    int size;
	element* head;
	element* tail;
	void add(KernSem* x);
	void remove(KernSem* x);
	KernSem* get(int index);
	Lista();
	virtual ~Lista();

};

#endif /* LISTA_H_ */
