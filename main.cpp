#include "Scheduler.h"
#include "UI.h"
#include <iostream>

int main()
{
    Scheduler system;
    UI ui;

    int mode = UI::getOperationMode();
    std::string outputFile = UI::getOutputFileName();
    system.setMode(mode); // Store mode inside Scheduler

    std::cout << "Reading patients from file: " << "\n";
    system.loadPatients();
    cout << "Loaded patients = " << system.getAllPatientCount() << endl;

    if (!system.simulationFinished())
    {
        std::cout << "Starting simulation...\n";
        if (mode == 1)
        {
            while (!system.simulationFinished())
            {
                system.simulate(); // 1 timestep or full?
                system.printStatus();
                std::cin.get();
            }
        }
        else
        {
            system.simulate();
        }
    }
    else
    {
        std::cout << "Simulation skipped. Nothing to simulate.\n";
    }

    std::cout << "Generating output file: " << outputFile << "\n";
    system.generateOutputFile(outputFile);
    std::cout << "Done!\n";

    return 0;
}
