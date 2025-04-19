#include "Scheduler.h"
#include "UI.h"
#include "ETreatment.h"
#include "UTreatment.h"
#include "XTreatment.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

Scheduler::Scheduler()
{
    currentTime = 1;
    totalPatients = 0;
    cancelProbability = 0;
    rescheduleProbability = 0;
    srand(time(nullptr));
}

void Scheduler::loadPatients()
{
    std::ifstream inFile("input.txt");
    if (!inFile.is_open())
    {
        std::cerr << "ERROR: Cannot open input file.\n";
        return;
    }

    int numE, numU, numX;
    inFile >> numE >> numU >> numX;

    for (int i = 1; i <= numE; ++i)
        eDevices.enqueue(new Resource(i, TreatmentType::Electrotherapy, 1));

    for (int i = 1; i <= numU; ++i)
        uDevices.enqueue(new Resource(i, TreatmentType::UltrasoundTherapy, 1));

    int *xCapacities = new int[numX];
    for (int i = 0; i < numX; ++i)
        inFile >> xCapacities[i];

    for (int i = 1; i <= numX; ++i)
        xRooms.enqueue(new Resource(i, TreatmentType::GymExercises, xCapacities[i - 1]));

    delete[] xCapacities;

    inFile >> cancelProbability >> rescheduleProbability;
    inFile >> totalPatients;
    if (totalPatients <= 0)
    {
        std::cerr << "No patients to load from file.\n";
    }

    for (int pid = 1; pid <= totalPatients; ++pid)
    {
        char typeChar;
        int appointment, arrival, numTreatments;
        inFile >> typeChar >> appointment >> arrival >> numTreatments;

        PatientType pType = (typeChar == 'N') ? PatientType::Normal : PatientType::Recovering;
        Patient *p = new Patient(pid, pType, appointment, arrival);

        for (int t = 0; t < numTreatments; ++t)
        {
            char tType;
            int duration;
            inFile >> tType >> duration;

            Treatment *treatment = nullptr;
            switch (tType)
            {
            case 'E':
                treatment = new ETreatment(duration);
                break;
            case 'U':
                treatment = new UTreatment(duration);
                break;
            case 'X':
                treatment = new XTreatment(duration);
                break;
            }

            if (treatment)
                p->addTreatment(treatment);
        }

        allPatients.enqueue(p);
    }

    inFile.close();
}


int Scheduler::getAllPatientCount() const {
    return allPatients.GetCount();
}

bool Scheduler::simulationFinished() const
{
    bool done =
        allPatients.isEmpty() &&
        earlyPatients.isEmpty() &&
        latePatients.isEmpty() &&
        eWaiting.isEmpty() &&
        uWaiting.isEmpty() &&
        xWaiting.isEmpty() &&
        inTreatment.isEmpty();

    if (done)
        std::cout << "[SimulationFinished] All queues empty at time " << currentTime << std::endl;

    return done;
}

void Scheduler::simulate()
{
    if (simulationMode == 1)
        std::cout << "\n=== SIMULATION STARTED ===\n";

    while (!simulationFinished())
    {
        // STEP 1: Move newly arrived patients
        while (!allPatients.isEmpty())
        {
            Patient *p = nullptr;
            if (!allPatients.peek(p) || !p || p->getArrivalTime() > currentTime)
                break;

            allPatients.dequeue(p);

            if (p->getArrivalTime() < p->getAppointmentTime())
            {
                earlyPatients.enqueue(p, p->getAppointmentTime());
            }
            else if (p->getArrivalTime() > p->getAppointmentTime())
            {
                int penalty = (p->getArrivalTime() - p->getAppointmentTime()) / 2;
                int adjustedPT = p->getAppointmentTime() + penalty;
                latePatients.enqueue(p, currentTime + 2);  // <== key change here
            }
            else
            {
                Treatment *t = p->getNextTreatment();
                if (t)
                    t->moveFromAllToWait(*this, p);
            }
        }

        // STEP 2: Move late patients after delay
        int lateCount = latePatients.GetCount();
        for (int i = 0; i < lateCount; ++i)
        {
            Patient *p = nullptr;
            int pri;
            if (latePatients.dequeue(p, pri))
            {
                if (p && currentTime >= pri)
                {
                    Treatment *t = p->getNextTreatment();
                    if (t)
                        t->moveFromAllToWait(*this, p);
                }
                else
                {
                    latePatients.enqueue(p, pri);
                }
            }
        }

        // STEP 2.5: Move early patients ready
        int earlyCount = earlyPatients.GetCount();
        for (int i = 0; i < earlyCount; ++i)
        {
            Patient *p = nullptr;
            int pri;
            if (earlyPatients.dequeue(p, pri))
            {
                if (p && currentTime >= pri)
                {
                    Treatment *t = p->getNextTreatment();
                    if (t)
                        t->moveFromAllToWait(*this, p);
                }
                else
                {
                    earlyPatients.enqueue(p, pri);
                }
            }
        }

        // STEP 3: Cancel from X_WaitList
        if (rand() % 100 < cancelProbability)
        {
            Patient *toCancel = xWaiting.attemptCancellation(cancelProbability);
            if (toCancel)
            {
                toCancel->markCancelled();
                toCancel->setFinishTime(currentTime);
                toCancel->clearRemainingTreatments();
                finishedPatients.push(toCancel);

                if (simulationMode == 1)
                {
                    std::cout << "Patient P" << toCancel->getID()
                              << " cancelled from X-Waiting\n";
                }
            }
        }

        // STEP 4: Assign resources
        assignResources();

        // STEP 5: Update inTreatment
        updateInTreatment();

        // STEP 6: Reschedule
        if (rand() % 100 < rescheduleProbability && !earlyPatients.isEmpty())
        {
            Patient *resP = nullptr;
            int oldPri;
            if (earlyPatients.dequeue(resP, oldPri))
            {
                if (!resP->wasRescheduled() && currentTime < oldPri)
                {
                    int newPT = oldPri + 5 + rand() % 10;
                    resP->markRescheduled();
                    earlyPatients.enqueue(resP, newPT);

                    if (simulationMode == 1)
                    {
                        std::cout << "Patient P" << resP->getID()
                                  << " rescheduled to PT=" << newPT << "\n";
                    }
                }
                else
                {
                    earlyPatients.enqueue(resP, oldPri);
                }
            }
        }

        // STEP 7: Increment wait times
        eWaiting.incrementWaits();
        uWaiting.incrementWaits();
        xWaiting.incrementWaits();
        earlyPatients.incrementWaits();
        latePatients.incrementWaits();

        // STEP 8: Print and advance
        if (simulationMode == 1)
        {
            printStatus();
            std::cout << "\nPress Enter to continue...\n";
            std::cin.get();
        }

        currentTime++;

        if (currentTime > 200)
        {
            std::cout << "⚠️ Timestep limit reached (200). Breaking.\n";
            break;
        }
    }

    if (simulationMode == 0)
        std::cout << "Silent Mode: Simulation completed. Output file generated.\n";
}

void Scheduler::assignResources()
{
    // Electrotherapy
    while (!eDevices.isEmpty() && !eWaiting.isEmpty())
    {
        Patient *p;
        eWaiting.dequeue(p);
        Resource *r = nullptr;
        eDevices.dequeue(r);
        if (!p || !r)
            continue;

        Treatment *t = p->getNextTreatment();
        if (!t)
            continue;

        r->assign();
        t->setAssignmentTime(currentTime);
        t->setAssignedResource(r);
        inTreatment.enqueue(p, currentTime + t->getDuration());
    }

    // UltrasoundTherapy
    while (!uDevices.isEmpty() && !uWaiting.isEmpty())
    {
        Patient *p;
        uWaiting.dequeue(p);
        Resource *r = nullptr;
        uDevices.dequeue(r);
        if (!p || !r)
            continue;

        Treatment *t = p->getNextTreatment();
        if (!t)
            continue;

        r->assign();
        t->setAssignmentTime(currentTime);
        t->setAssignedResource(r);
        inTreatment.enqueue(p, currentTime + t->getDuration());
    }

    // GymExercises
    int count = xWaiting.GetCount();
    for (int i = 0; i < count && !xRooms.isEmpty(); ++i)
    {
        Patient *p;
        if (!xWaiting.dequeue(p) || !p)
            continue;

        Resource *room = nullptr;
        xRooms.dequeue(room);
        if (!room || !room->isAvailable())
        {
            xRooms.enqueue(room);
            xWaiting.enqueue(p);
            continue;
        }

        Treatment *t = p->getNextTreatment();
        if (!t)
            continue;

        room->assign();
        t->setAssignmentTime(currentTime);
        t->setAssignedResource(room);
        inTreatment.enqueue(p, currentTime + t->getDuration());

        if (room->isAvailable())
            xRooms.enqueue(room);
    }
}

void Scheduler::updateInTreatment()
{
    bool handled = false;
    int count = inTreatment.GetCount();

    for (int i = 0; i < count && !handled; ++i)
    {
        Patient *p = nullptr;
        int finishTime = 0;
        if (!inTreatment.dequeue(p, finishTime) || !p)
            continue;

        if (finishTime > currentTime)
        {
            inTreatment.enqueue(p, finishTime); // Not ready yet → requeue
            continue;
        }

        // ✅ Patient is ready to be processed
        Treatment *current = p->getNextTreatment(); // should be peek
        if (current)
        {
            Resource *r = current->getAssignedResource();
            if (r)
            {
                r->release();
                switch (r->getType())
                {
                case TreatmentType::Electrotherapy:
                    eDevices.enqueue(r);
                    break;
                case TreatmentType::UltrasoundTherapy:
                    uDevices.enqueue(r);
                    break;
                case TreatmentType::GymExercises:
                    if (r->isAvailable())
                        xRooms.enqueue(r);
                    break;
                }
            }
        }

        // ✅ Mark current treatment as finished (advance)
        p->advanceTreatment(); // <-- remove the current treatment

        if (p->hasMoreTreatments())
        {
            Treatment *next = p->getNextTreatment(); // next treatment (peek again)
            if (next)
                next->moveFromAllToWait(*this, p);
        }
        else
        {
            p->setFinishTime(currentTime);
            finishedPatients.push(p);
        }

        handled = true; // Only one patient per timestep
    }
}

void Scheduler::generateOutputFile(const std::string &outputFileName)
{
    std::ofstream outFile(outputFileName);
    if (!outFile.is_open())
    {
        std::cerr << "ERROR: Cannot open output file.\n";
        return;
    }

    Patient *p = nullptr;

    int totalWT = 0, totalTT = 0;
    int nWT = 0, nTT = 0, rWT = 0, rTT = 0;
    int nCount = 0, rCount = 0;
    int cancelledCount = 0, rescheduledCount = 0;
    int earlyCount = 0, lateCount = 0;
    int totalLatePenalty = 0;

    outFile << "PID  PType  PT  VT  FT  WT  TT  Cancel  Resc\n";

    while (!finishedPatients.isEmpty())
    {
        finishedPatients.pop(p);
        if (!p)
            continue;

        int pt = p->getAppointmentTime();
        int vt = p->getArrivalTime();
        int ft = p->getFinishTime();
        int wt = p->getTotalWaitingTime();
        int tt = p->getTotalTreatmentTime();
        bool cancel = p->wasCancelled();
        bool resch = p->wasRescheduled();
        bool early = vt < pt;
        bool late = vt > pt;

        outFile << "P" << p->getID() << "  ";
        outFile << (p->getType() == PatientType::Normal ? "N" : "R") << "      ";
        outFile << pt << "  " << vt << "  " << ft << "  ";
        outFile << wt << "  " << tt << "  ";
        outFile << (cancel ? "T" : "F") << "       ";
        outFile << (resch ? "T" : "F") << "\n";

        // Stats
        totalWT += wt;
        totalTT += tt;

        if (p->getType() == PatientType::Normal)
        {
            nWT += wt;
            nTT += tt;
            nCount++;
        }
        else
        {
            rWT += wt;
            rTT += tt;
            rCount++;
        }

        if (cancel) cancelledCount++;
        if (resch) rescheduledCount++;
        if (early) earlyCount++;
        if (late)
        {
            lateCount++;
            int penalty = (vt - pt) / 2;
            totalLatePenalty += penalty;
        }
    }

    int totalCount = nCount + rCount;

    outFile << "\nTotal number of timesteps = " << currentTime - 1 << "\n";
    outFile << "Total number of all, N, and R patients = "
            << totalCount << ", " << nCount << ", " << rCount << "\n";

    outFile << "Average total waiting time for all, N, and R patients = ";
    outFile << (totalCount ? (float)totalWT / totalCount : 0) << ", ";
    outFile << (nCount ? (float)nWT / nCount : 0) << ", ";
    outFile << (rCount ? (float)rWT / rCount : 0) << "\n";

    outFile << "Average total treatment time for all, N, and R patients = ";
    outFile << (totalCount ? (float)totalTT / totalCount : 0) << ", ";
    outFile << (nCount ? (float)nTT / nCount : 0) << ", ";
    outFile << (rCount ? (float)rTT / rCount : 0) << "\n";

    outFile << "Percentage of patients whose cancellation is accepted (%) = ";
    outFile << (totalCount ? (float)cancelledCount * 100 / totalCount : 0) << " %\n";

    outFile << "Percentage of patients whose rescheduling is accepted (%) = ";
    outFile << (totalCount ? (float)rescheduledCount * 100 / totalCount : 0) << " %\n";

    outFile << "Percentage of early patients (%) = ";
    outFile << (totalCount ? (float)earlyCount * 100 / totalCount : 0) << " %\n";

    outFile << "Percentage of late patients (%) = ";
    outFile << (totalCount ? (float)lateCount * 100 / totalCount : 0) << " %\n";

    outFile << "Average late penalty = ";
    outFile << (lateCount ? (float)totalLatePenalty / lateCount : 0) << " timestep(s)\n";

    outFile.close();
}

// ====================== Scheduler Helper Methods ======================

Resource *Scheduler::getNextEDevice()
{
    if (eDevices.isEmpty())
        return nullptr;
    Resource *r = nullptr;
    eDevices.dequeue(r);
    return r;
}

Resource *Scheduler::getNextUDevice()
{
    if (uDevices.isEmpty())
        return nullptr;
    Resource *r = nullptr;
    uDevices.dequeue(r);
    return r;
}

Resource *Scheduler::getNextXRoom()
{
    if (xRooms.isEmpty())
        return nullptr;
    Resource *r = nullptr;
    xRooms.dequeue(r);
    return r;
}

void Scheduler::addToEWaiting(Patient *p)
{
    if (!p)
    {
        std::cout << "[FATAL] Tried to add null patient to XWaiting at timestep " << currentTime << "\n";
        return;
    }
    eWaiting.insertSorted(p);
}

void Scheduler::addToUWaiting(Patient *p)
{
    if (!p)
    {
        std::cout << "[FATAL] Tried to add null patient to XWaiting at timestep " << currentTime << "\n";
        return;
    }
    uWaiting.insertSorted(p);
}

void Scheduler::addToXWaiting(Patient *p)
{
    if (!p)
    {
        std::cout << "[FATAL] Tried to add null patient to XWaiting at timestep " << currentTime << "\n";
        return;
    }
    xWaiting.insertSorted(p);
}

void Scheduler::returnEDevice(Resource *r)
{
    if (r)
        eDevices.enqueue(r);
}

void Scheduler::returnUDevice(Resource *r)
{
    if (r)
        uDevices.enqueue(r);
}

void Scheduler::returnXRoom(Resource *r)
{
    if (r && r->isAvailable())
        xRooms.enqueue(r);
}

void Scheduler::printStatus()
{
    UI::printSystemStatus(
        currentTime,
        allPatients,
        inTreatment,
        finishedPatients,
        eDevices,
        uDevices,
        xRooms,
        eWaiting,
        uWaiting,
        xWaiting,
        latePatients,
        earlyPatients);
}
