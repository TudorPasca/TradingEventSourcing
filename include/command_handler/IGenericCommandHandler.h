#pragma once

#include <vector>
#include <memory>
#include "../event/IDomainEvent.h"

struct ICommand;

struct IGenericCommandHandler {
    virtual ~IGenericCommandHandler() = default;

    virtual std::vector<std::shared_ptr<IDomainEvent> > handleCommand(const ICommand &command) = 0;
};
