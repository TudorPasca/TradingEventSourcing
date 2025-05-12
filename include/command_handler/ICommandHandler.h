#pragma once
#include "IGenericCommandHandler.h"
#include "../command/ICommand.h"
#include "../event/IDomainEvent.h"

template<typename TCommand>
struct ICommandHandler: public IGenericCommandHandler {
    std::vector<std::shared_ptr<IDomainEvent>> handleCommand(const ICommand &command) override {
        const auto *specificCommand = dynamic_cast<const TCommand *>(&command);
        if (specificCommand == nullptr) {
            throw std::runtime_error("[ICommandHandler] Command does not exist");
        }
        return handleInternal(*specificCommand);
    }

protected:
    virtual std::vector<std::shared_ptr<IDomainEvent>> handleInternal(const TCommand &command) = 0;
};
