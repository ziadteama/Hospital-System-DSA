#include "LatePList.h"

void LatePList::incrementWaits() {
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
