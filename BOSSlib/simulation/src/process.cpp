#include <generic_process.h>

namespace Process {
    Process::Process(std::string name, ProcessResourceIntensity intensity) {
        this->name = name;
        this->intensity = intensity;
        this->id = nanoid::generate();
    }

    void Process::setName(std::string new_name) {
        this->name = new_name;
    }

    std::string Process::getName() {
        return this->name;
    }

    std::string Process::getId() {
        return this->id;
    }

    ProcessResourceIntensity Process::getIntensity() {
        return this->intensity;
    }

    std::vector<Resource::ResourceSlot>* Process::getResources() {
        return &this->resources;
    }

    void Process::prepare() {
        for (auto& resource : this->resources) {
            resource.prepare(this->intensity);
        }
    }

    void Process::addResource(Resource::Resource* resource, uint64_t amount) {
        this->resources.push_back(Resource::ResourceSlot(resource, amount));
    }
    void Process::removeResource(std::string resourceId) {
        if (std::find_if(this->resources.begin(), this->resources.end(), [resourceId](Resource::ResourceSlot slot) {
            return slot.getResource()->getId() == resourceId;
            }) == this->resources.end()) {
            throw std::runtime_error("Resource not found");
        }
    }

    void Process::runProcess() {
        this->state = ProcessState::RUNNING;
    }

    void Process::blockProcess() {
        this->state = ProcessState::BLOCKED;
    }

    void Process::unblockProcess() {
        this->state = ProcessState::READY;
    }
}