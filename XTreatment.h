#ifndef XTREATMENT_H
#define XTREATMENT_H

#include "Treatment.h"

class XTreatment : public Treatment {
public:
    XTreatment(int duration);
    virtual bool canAssign(Scheduler& scheduler) override;
    virtual void moveFromAllToWait(Scheduler& scheduler, Patient* patient) override;
};

#endif
