#ifndef LATEPLIST_H
#define LATEPLIST_H

#include "priQueue.h"
#include "Patient.h"

class LatePList : public priQueue<Patient*> {
public:
    using priQueue<Patient*>::enqueue;
    using priQueue<Patient*>::dequeue;
    using priQueue<Patient*>::peek;
    using priQueue<Patient*>::isEmpty;
    using priQueue<Patient*>::GetCount;
    using priQueue<Patient*>::print;

    void incrementWaits();
};

#endif
