/*
 * Event.h
 *
 *  Created on: May 31, 2020
 *      Author: OS1
 */

#ifndef _event_h_
#define _event_h_
#define PREPAREENTRY(entryNo, callOldRout)\
		void interrupt newRout##entryNo(...);\
		IVTEntry ivtEntry##entryNo(entryNo, newRout##entryNo);\
		void interrupt newRout##entryNo(...) {\
			ivtEntry##entryNo.signalLinkedEvent();\
			if (callOldRout == 1)\
				ivtEntry##entryNo.callOldRoutine();\
		}
typedef unsigned char IVTNo;
class KernelEv;
class Event {
public:
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();
protected:
 friend class KernelEv;
 void signal(); // can call KernelEv
private:
 KernelEv* myImpl;
};
#endif
