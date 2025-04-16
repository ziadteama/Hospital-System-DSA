// X_WaitList.h
#ifndef X_WAIT_LIST_H
#define X_WAIT_LIST_H

#include "EU_WaitList.h"

class X_WaitList : public EU_WaitList {
public:
    // Attempt to cancel a patient with a given probability
    // Returns pointer to cancelled patient if successful, nullptr otherwise
    Patient* attemptCancellation(int cancelProbability);
    void incrementWaits();  // ✅ This line was missing!
};

#endif

