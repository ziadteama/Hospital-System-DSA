#include "EarlyPList.h"

// Optional reschedule logic (not implemented unless needed)
void EarlyPList::reschedule(Patient* patient, int newAppointmentTime) {
    if (patient) {
        this->enqueue(patient, newAppointmentTime);
    }
}

// ✅ Add 1 to each patient's wait time
void EarlyPList::incrementWaits() {
    int count = this->GetCount();
    Patient* p = nullptr;
    int pri;

    for (int i = 0; i < count; ++i) {
        this->dequeue(p, pri);
        if (p)
            p->incrementWaitingTime();
        this->enqueue(p, pri);
    }
}
