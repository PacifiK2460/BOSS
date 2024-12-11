#pragma once
#include <nanoid/nanoid.h>
#include <string>

namespace Resource {
    class Resource {
        std::string name;
        std::string id;
        uint64_t totalAmount;
        uint64_t freeAmount;

    public:
        Resource(std::string name, uint64_t totalAmount);
        std::string getName();
        std::string getId();
        uint64_t getTotalAmount();
        uint64_t getFreeAmount();
        void use(uint64_t amount);
    };

    class ResourceSlot {
        Resource* resource;
        uint64_t amount;
        uint64_t baseAmount;
    public:
        ResourceSlot(Resource* resource, uint64_t amount);
        Resource* getResource();
        uint64_t getAmount();
        void prepare(uint64_t amount);
    };

}