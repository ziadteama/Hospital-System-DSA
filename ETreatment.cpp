// ETreatment.cpp

#include "ETreatment.h"
#include "Scheduler.h"

ETreatment::ETreatment(int duration)
    : Treatment(TreatmentType::Electrotherapy, duration) {}

bool ETreatment::canAssign(Scheduler& scheduler) {
    return scheduler.getNextEDevice() != nullptr;
}

void ETreatment::moveFromAllToWait(Scheduler& scheduler, Patient* patient) {
    scheduler.addToEWaiting(patient);
}
