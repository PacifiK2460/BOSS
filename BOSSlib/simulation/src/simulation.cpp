#include <simulation.h>

namespace Simulation {
    Simulation::Simulation(uint64_t ticksPerSecond) : ticksPerSecond(ticksPerSecond), state(SimulationState::STOPPED) {
        this->processes = std::vector<std::shared_ptr<Process::Process>>();
        this->resources = std::vector<std::shared_ptr<Resource::Resource>>();

        // std::thread(&logicLoop).detach();
        std::thread logicThread(&Simulation::logicLoop, this);
    }

    Simulation::Simulation() : Simulation(60) {}

    std::vector<std::shared_ptr<Process::Process>>* Simulation::getProcesses() {
        return &this->processes;
    }

    std::shared_ptr<Process::Process> Simulation::getProcess(std::string processId) {
        std::lock_guard<std::mutex> lock(simulationMutex);
        auto process = std::find_if(this->processes.begin(), this->processes.end(), [processId](std::shared_ptr<Process::Process> process) {
            return process->getId() == processId;
            });

        if (process != this->processes.end()) {
            return *process;
        }
        throw std::runtime_error("Process not found");
    }

    std::shared_ptr<Resource::Resource> Simulation::getResource(std::string resourceId) {
        std::lock_guard<std::mutex> lock(simulationMutex);
        auto resource = std::find_if(this->resources.begin(), this->resources.end(), [resourceId](std::shared_ptr<Resource::Resource> resource) {
            return resource->getId() == resourceId;
            });

        if (resource != this->resources.end()) {
            return *resource;
        }
        throw std::runtime_error("Resource not found");
    }

    std::vector<std::shared_ptr<Resource::Resource>>* Simulation::getResources() {
        return &this->resources;
    }

    void Simulation::addProcess(Process::Process process) {
        std::lock_guard<std::mutex> lock(simulationMutex);
        this->processes.push_back(std::make_shared<Process::Process>(process));
    }

    void Simulation::addResource(Resource::Resource resource) {
        std::lock_guard<std::mutex> lock(simulationMutex);
        this->resources.push_back(std::make_shared<Resource::Resource>(resource));
    }

    void Simulation::removeProcess(std::string processId) {
        std::lock_guard<std::mutex> lock(simulationMutex);
        this->processes.erase(std::remove_if(this->processes.begin(), this->processes.end(), [processId](std::shared_ptr<Process::Process> process) {
            return process->getId() == processId;
            }), this->processes.end());
    }

    void Simulation::removeResource(std::string resourceId) {
        std::lock_guard<std::mutex> lock(simulationMutex);
        this->resources.erase(std::remove_if(this->resources.begin(), this->resources.end(), [resourceId](std::shared_ptr<Resource::Resource> resource) {
            return resource->getId() == resourceId;
            }), this->resources.end());
    }

    void Simulation::start() {
        std::lock_guard<std::mutex> lock(simulationMutex);
        this->state = SimulationState::RUNNING;
    }

    void Simulation::stop() {
        std::lock_guard<std::mutex> lock(simulationMutex);
        this->state = SimulationState::STOPPED;
    }

    void Simulation::logicLoop() {
        while (true) {
            if (this->state == SimulationState::RUNNING) {
                std::lock_guard<std::mutex> lock(simulationMutex);
                for (auto process : this->processes) {
                    process->prepare();
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / this->ticksPerSecond));
        }
    }

}