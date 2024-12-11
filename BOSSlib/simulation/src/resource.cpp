#include <generic_resource.h>

namespace Resource {
    Resource::Resource(std::string name, uint64_t totalAmount) {
        this->name = name;
        this->id = nanoid::generate();
        this->totalAmount = totalAmount;
        this->freeAmount = totalAmount;
    }

    std::string Resource::getName() {
        return this->name;
    }

    std::string Resource::getId() {
        return this->id;
    }

    uint64_t Resource::getTotalAmount() {
        return this->totalAmount;
    }

    ResourceSlot::ResourceSlot(Resource* resource, uint64_t amount) {
        this->resource = resource;
        this->amount = amount;
        this->baseAmount = amount;
    }

    void Resource::use(uint64_t amount) {
        if(amount > this->freeAmount) {
            throw std::runtime_error("Not enough resources");
        }

        this->freeAmount -= amount;
    }

    uint64_t Resource::getFreeAmount() {
        return this->freeAmount;
    }

    Resource* ResourceSlot::getResource() {
        return this->resource;
    }

    uint64_t ResourceSlot::getAmount() {
        return this->amount;
    }

    void ResourceSlot::prepare(uint64_t amount) {
        if (amount == 0) {
            this->amount = this->baseAmount;
        }
        else {
            double_t ratio = (double_t)this->baseAmount;
            amount /= 10;
            ratio += (double_t)amount * (double_t)this->baseAmount;
            this->amount = (uint64_t) ratio;

            this->resource->use(this->amount);
        }
    }
}