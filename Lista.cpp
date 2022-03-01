/*
 * Lista.cpp
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */

#include "Lista.h"
Lista::Lista() {
	size=0;
head=0;
tail=0;
}

Lista::~Lista() {
	// TODO Auto-generated destructor stub
}
void Lista::add(KernSem* x)
	{
			if(head==0)
				tail=head=new element(x);
			else{
				tail->next=new element(x);
				tail=tail->next;
			}
			size++;
		}

void Lista::remove(KernSem* x){
	element* pom=head;
	element* pret=head;
	while(pom->info!=x) {pret=pom;pom=pom->next;}
	if(pom==head) {head=head->next; delete pom;return;}
	pret->next=pom->next;
	delete pom;
	size--;
}
KernSem* Lista::get(int index){
	int i=0;
	element*pom=head;
	while(i!=index) {pom=pom->next; i++;}
	return pom->info;
}

