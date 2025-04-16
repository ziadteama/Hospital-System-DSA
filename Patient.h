// Patient.h
#ifndef PATIENT_H
#define PATIENT_H

#include "LinkedQueue.h"
#include "Treatment.h"
#include "Enums.h"  // We'll define enums separately

class Patient {
private:
    int id;
    PatientType type;
    int appointmentTime;
    int arrivalTime;
    PatientStatus status;

    LinkedQueue<Treatment*> requiredTreatments;

    int finishTime;
    int totalWaitingTime;
    int totalTreatmentTime;
    bool cancelled;
    bool rescheduled;

public:
    Patient(int id, PatientType type, int appointmentTime, int arrivalTime);

    int getID() const;
    PatientType getType() const;
    int getAppointmentTime() const;
    int getArrivalTime() const;
    PatientStatus getStatus() const;
    void setStatus(PatientStatus s);
    int getFinishTime() const;
    int getTotalWaitingTime() const;
    int getTotalTreatmentTime() const;

    void incrementWaitingTime();
    void setFinishTime(int time);
    void addTreatment(Treatment* treatment);
    void advanceTreatment();
    Treatment *getNextTreatment();
    void clearRemainingTreatments();
    bool hasMoreTreatments() const;

    void markCancelled();
    void markRescheduled();
    bool wasCancelled() const;
    bool wasRescheduled() const;

    LinkedQueue<Treatment*>& getTreatmentQueue();

    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif
