#pragma once
#include <generic_resource.h>
#include <generic_process.h>

#include <iostream>
#include <mutex>
#include <vector>
#include <memory>
#include <thread>
#include <algorithm>

namespace Simulation {
    static std::mutex simulationMutex;

    enum SimulationState {
        RUNNING,
        STOPPED
    };

    class Simulation {
    protected:
        uint64_t ticksPerSecond;
        std::vector<std::shared_ptr<Process::Process>> processes;
        std::vector<std::shared_ptr<Resource::Resource>> resources;
        SimulationState state;
        void logicLoop();
    public:
        Simulation();
        Simulation(uint64_t ticksPerSecond);
        std::vector<std::shared_ptr<Process::Process>>* getProcesses();
        std::vector<std::shared_ptr<Resource::Resource>>* getResources();
        std::shared_ptr<Process::Process> getProcess(std::string processId);
        std::shared_ptr<Resource::Resource> getResource(std::string resourceId);
        void addProcess(Process::Process process);
        void addResource(Resource::Resource resource);
        void removeProcess(std::string processId);
        void removeResource(std::string resourceId);

        void start();
        void stop();
    };
}