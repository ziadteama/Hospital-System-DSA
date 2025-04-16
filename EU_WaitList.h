#ifndef EU_WAIT_LIST_H
#define EU_WAIT_LIST_H

#include "LinkedQueue.h"
#include "Patient.h"

class EU_WaitList : public LinkedQueue<Patient*> {
public:
    using LinkedQueue<Patient*>::enqueue;
    using LinkedQueue<Patient*>::dequeue;
    using LinkedQueue<Patient*>::peek;
    using LinkedQueue<Patient*>::isEmpty;
    using LinkedQueue<Patient*>::GetCount;
    using LinkedQueue<Patient*>::print;

    // Inserts in sorted order by appointmentTime or adjusted priority
    void insertSorted(Patient* patient);

    // ✅ Adds 1 to each patient's wait time
    void incrementWaits();
};

#endif
