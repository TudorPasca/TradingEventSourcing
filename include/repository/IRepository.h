#pragma once
#include "../event/IDomainEvent.h"

struct IRepository {
    virtual ~IRepository() = default;
    virtual void processEvent(const IDomainEvent &event) = 0;
    virtual void rehydrate(const std::vector<IDomainEvent>& events);
};
