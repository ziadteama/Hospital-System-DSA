// UI.cpp

#include "UI.h"
#include <iostream>
#include <iomanip>
using namespace std;

int UI::getOperationMode()
{
    int mode;
    cout << "Select mode: (0) Silent, (1) Interactive: ";
    cin >> mode;
    return mode;
}

string UI::getInputFileName()
{
    string fileName;
    cout << "Enter input file name: ";
    cin >> fileName;
    return fileName;
}

string UI::getOutputFileName()
{
    string fileName;
    cout << "Enter output file name: ";
    cin >> fileName;
    return fileName + ".txt";
}

void UI::printSystemStatus(
    int currentTime,
    const LinkedQueue<Patient *> &allPatients,
    const priQueue<Patient *> &inTreatment,
    const ArrayStack<Patient *> &finishedPatients,
    const LinkedQueue<Resource *> &eDevices,
    const LinkedQueue<Resource *> &uDevices,
    const LinkedQueue<Resource *> &xRooms,
    const LinkedQueue<Patient *> &eWaiting,
    const LinkedQueue<Patient *> &uWaiting,
    const LinkedQueue<Patient *> &xWaiting,
    const priQueue<Patient *> &latePatients,
    const priQueue<Patient *> &earlyPatients)
{
    using namespace std;
    cout << "\nCurrent Timestep: " << currentTime << "\n";

    cout << "===============   ALL List   ===============\n";
    cout << allPatients.GetCount() << " patients total: ";
    allPatients.print();

    cout << "============== Waiting Lists ==============\n";
    cout << eWaiting.GetCount() << " Electrotherapy patients: ";
    eWaiting.print();
    cout << uWaiting.GetCount() << " UltrasoundTherapy patients: ";
    uWaiting.print();
    cout << xWaiting.GetCount() << " GymExercises patients: ";
    xWaiting.print();

    cout << "===============   Early List   ================\n";
    cout << earlyPatients.GetCount() << " patients: ";
    earlyPatients.print();

    cout << "===============   Late List   ================\n";
    cout << latePatients.GetCount() << " patients: ";
    latePatients.print();

    cout << "===============   Avail E-devices ===============\n";
    cout << eDevices.GetCount() << " Electro devices: ";
    eDevices.print();

    cout << "===============   Avail U-devices ===============\n";
    cout << uDevices.GetCount() << " Ultrasound devices: ";
    uDevices.print();

    cout << "===============   Avail X-rooms ===============\n";
    xRooms.print();

    cout << "============  In-treatment List ================\n";
    cout << inTreatment.GetCount() << " patients: ";
    inTreatment.print();

    cout << "-------------------------------------------------------\n";
    cout << finishedPatients.GetCount() << " Finished patients: ";

    cout << finishedPatients.GetCount() << " Finished patients: ";

    ArrayStack<Patient *> copy = finishedPatients;
    Patient *p = nullptr;
    while (!copy.isEmpty())
    {
        copy.pop(p);
        if (p)
        {
            cout << "P" << std::setw(2) << std::setfill('0') << p->getID()
                 << "_" << (p->getType() == PatientType::Normal ? "N" : "R") << ", ";
        }
    }
    cout << endl;

    cout << endl;
}
