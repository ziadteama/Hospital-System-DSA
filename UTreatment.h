#ifndef UTREATMENT_H
#define UTREATMENT_H

#include "Treatment.h"

class UTreatment : public Treatment {
public:
    UTreatment(int duration);
    virtual bool canAssign(Scheduler& scheduler) override;
    virtual void moveFromAllToWait(Scheduler& scheduler, Patient* patient) override;
};

#endif
