#pragma once
#include <generic_resource.h>
#include <vector>
#include <algorithm>
#include <nanoid/nanoid.h>

namespace Process {
    enum ProcessResourceIntensity {
        NONE = 0,
        LOW = 1,
        MEDIUM = 3,
        HIGH = 8,
        EXTREME = 10
    };

    enum ProcessState {
        NEW,
        BLOCKED,
        READY,
        RUNNING
    };

    class Process {
    protected:
        std::string name;
        std::string id;
        ProcessResourceIntensity intensity;
        std::vector<Resource::ResourceSlot> resources;
        ProcessState state;

    public:
        Process(std::string name, ProcessResourceIntensity intensity);
        std::string getName();
        std::string getId();
        ProcessResourceIntensity getIntensity();
        std::vector<Resource::ResourceSlot>* getResources();

        void prepare();
        void setName(std::string new_name);
        void addResource(Resource::Resource* resource, uint64_t amount);
        void removeResource(std::string resourceId);
        void runProcess();
        void blockProcess();
        void unblockProcess();
    };
}