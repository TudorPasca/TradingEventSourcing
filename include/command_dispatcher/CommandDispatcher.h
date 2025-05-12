#pragma once

#include <typeindex>

#include "../event_store/IEventStore.h"
#include "../command_handler/ICommandHandler.h"

struct ICommand;

class CommandDispatcher {
public:
    explicit CommandDispatcher(std::shared_ptr<IEventStore> event_store);

    template <typename TCommand>
    void registerHandler(std::shared_ptr<ICommandHandler<TCommand>> handler) {
        handlers_[typeid(TCommand)] = handler;
    }

    void dispatch(const ICommand& command);
private:
    std::shared_ptr<IEventStore> event_store_;
    std::unordered_map<std::type_index, std::shared_ptr<IGenericCommandHandler>> handlers_;
};
