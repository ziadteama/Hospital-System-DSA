#ifndef ETREATMENT_H
#define ETREATMENT_H

#include "Treatment.h"

class ETreatment : public Treatment {
public:
    ETreatment(int duration);
    virtual bool canAssign(Scheduler& scheduler) override;
    virtual void moveFromAllToWait(Scheduler& scheduler, Patient* patient) override;
};

#endif
