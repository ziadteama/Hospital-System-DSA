#ifndef EARLYPLIST_H
#define EARLYPLIST_H

#include "priQueue.h"
#include "Patient.h"

class EarlyPList : public priQueue<Patient*> {
public:
    using priQueue<Patient*>::enqueue;
    using priQueue<Patient*>::dequeue;
    using priQueue<Patient*>::peek;
    using priQueue<Patient*>::isEmpty;
    using priQueue<Patient*>::GetCount;
    using priQueue<Patient*>::print;

    void reschedule(Patient* patient, int newAppointmentTime);

    // ✅ Add this:
    void incrementWaits();
};

#endif
