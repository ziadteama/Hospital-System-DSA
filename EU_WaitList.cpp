#include "EU_WaitList.h"

// Insert patient in sorted order based on appointment time (or adjusted PT)
void EU_WaitList::insertSorted(Patient* patient) {
    if (!patient) return;

    LinkedQueue<Patient*> temp;
    Patient* current = nullptr;
    bool inserted = false;

    while (!this->isEmpty()) {
        this->dequeue(current);
        if (!current) continue;  // safeguard

        if (!inserted && current->getAppointmentTime() > patient->getAppointmentTime()) {
            temp.enqueue(patient);
            inserted = true;
        }
        temp.enqueue(current);
    }

    if (!inserted)
        temp.enqueue(patient);

    while (!temp.isEmpty()) {
        temp.dequeue(current);
        if (current)  // safeguard
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
