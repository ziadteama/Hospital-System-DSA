#include "X_WaitList.h"

void X_WaitList::incrementWaits() {
    int count = this->GetCount();
    for (int i = 0; i < count; ++i) {
        Patient* p = nullptr;
        this->dequeue(p);
        if (p) p->incrementWaitingTime();
        this->enqueue(p);
    }
}

Patient* X_WaitList::attemptCancellation(int /*probability*/) {
    if (this->isEmpty()) return nullptr;

    int count = this->GetCount();
    int idx = rand() % count;

    LinkedQueue<Patient*> temp;
    Patient* target = nullptr;

    for (int i = 0; i < count; ++i) {
        Patient* p = nullptr;
        this->dequeue(p);

        if (!p) continue; // ❗ Defensive: skip broken pointers

        if (i == idx)
            target = p;
        else
            temp.enqueue(p);
    }

    while (!temp.isEmpty()) {
        Patient* p = nullptr;
        temp.dequeue(p);
        if (p) this->enqueue(p);  // ❗ Only enqueue if valid
    }

    return target; // ❗ May still be null if something went wrong
}
