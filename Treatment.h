// Treatment.h
#ifndef TREATMENT_H
#define TREATMENT_H

#include "Enums.h"
#include "Resource.h"
#include <iostream>

class Scheduler; // Forward declaration

class Treatment {
protected:
    TreatmentType type;
    int duration;
    int assignmentTime;
    Resource* assignedResource;

public:
    Treatment(TreatmentType type, int duration);
    virtual ~Treatment() {}

    TreatmentType getType() const;
    int getDuration() const;
    int getAssignmentTime() const;
    void setAssignmentTime(int time);

    Resource* getAssignedResource() const;
    void setAssignedResource(Resource* r);

    // Pure virtuals - to be overridden by ETreatment, UTreatment, XTreatment
    virtual bool canAssign(Scheduler& scheduler) = 0;
    virtual void moveFromAllToWait(Scheduler& scheduler, class Patient* patient) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Treatment& t);
};

#endif
