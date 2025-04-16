// UTreatment.cpp

#include "UTreatment.h"
#include "Scheduler.h"

UTreatment::UTreatment(int duration)
    : Treatment(TreatmentType::UltrasoundTherapy, duration) {}

bool UTreatment::canAssign(Scheduler& scheduler) {
    return scheduler.getNextUDevice() != nullptr;
}

void UTreatment::moveFromAllToWait(Scheduler& scheduler, Patient* patient) {
    scheduler.addToUWaiting(patient);
}
