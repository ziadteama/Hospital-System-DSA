// Scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "LinkedQueue.h"
#include "PriQueue.h"
#include "ArrayStack.h"
#include "Patient.h"
#include "Resource.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "EarlyPList.h"
#include <string>

class Scheduler {
private:
    // Master clock
    int currentTime;

    // Configuration from input
    int totalPatients;
    int cancelProbability;
    int rescheduleProbability;

    // Patient lists
    LinkedQueue<Patient*> allPatients;
    EarlyPList earlyPatients;
    PriQueue<Patient*> latePatients;

    EU_WaitList eWaiting;
    EU_WaitList uWaiting;
    X_WaitList xWaiting;

    PriQueue<Patient*> inTreatment;
    ArrayStack<Patient*> finishedPatients;

    // Resources
    LinkedQueue<Resource*> eDevices;
    LinkedQueue<Resource*> uDevices;
    LinkedQueue<Resource*> xRooms;

public:
    Scheduler();

    void loadPatients(const std::string& inputFileName);
    void simulate();
    void generateOutputFile(const std::string& outputFileName);

    // Helpers used by Treatment subclasses
    void addToEWaiting(Patient* p);
    void addToUWaiting(Patient* p);
    void addToXWaiting(Patient* p);

    // Resource access helpers
    Resource* getNextEDevice();
    Resource* getNextUDevice();
    Resource* getNextXRoom();
    void returnEDevice(Resource* r);
    void returnUDevice(Resource* r);
    void returnXRoom(Resource* r);

    // Status checks
    bool simulationFinished() const;

    // UI access
    friend class UI;
};

#endif
