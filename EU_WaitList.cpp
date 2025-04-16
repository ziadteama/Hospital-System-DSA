#include "EU_WaitList.h"

// Insert patient in sorted order based on appointment time (or adjusted PT)
void EU_WaitList::insertSorted(Patient* patient) {
    if (!patient) return;

    LinkedQueue<Patient*> temp;
    Patient* current = nullptr;

    while (!this->isEmpty()) {
        this->dequeue(current);
        if (current->getAppointmentTime() > patient->getAppointmentTime()) {
            temp.enqueue(patient);
            patient = nullptr;
        }
        temp.enqueue(current);
    }

    if (patient)
        temp.enqueue(patient);

    while (!temp.isEmpty()) {
        temp.dequeue(current);
        this->enqueue(current);
    }
}

// ✅ Add 1 to each patient's wait time
void EU_WaitList::incrementWaits() {
    int count = this->GetCount();
    Patient* p = nullptr;

    for (int i = 0; i < count; ++i) {
        this->dequeue(p);
        if (p)
            p->incrementWaitingTime();
        this->enqueue(p);
    }
}
