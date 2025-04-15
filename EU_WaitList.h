// EU_WaitList.h
#ifndef EU_WAIT_LIST_H
#define EU_WAIT_LIST_H

#include "LinkedQueue.h"
#include "Patient.h"

class EU_WaitList : public LinkedQueue<Patient*> {
public:
    // Insert patient in sorted position based on appointment time
    void insertSorted(Patient* patient);

    // Calculate total treatment latency for this waitlist
    int calculateTreatmentLatency() const;
};

#endif
