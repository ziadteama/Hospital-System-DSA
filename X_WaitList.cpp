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
        if (i == idx) target = p;
        else temp.enqueue(p);
    }

    while (!temp.isEmpty()) {
        Patient* p = nullptr;
        temp.dequeue(p);
        this->enqueue(p);
    }

    return target;
}
