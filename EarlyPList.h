// EarlyPList.h
#ifndef EARLYPLIST_H
#define EARLYPLIST_H

#include "PriQueue.h"
#include "Patient.h"

class EarlyPList : public PriQueue<Patient*> {
public:
    // Reschedule a patient to a new appointment time
    void reschedule(Patient* patient, int newAppointmentTime);
};

#endif
