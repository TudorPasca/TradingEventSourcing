#include <utility>

#include "../../include/command_dispatcher/CommandDispatcher.h"

#include <iostream>

CommandDispatcher::CommandDispatcher(std::shared_ptr<IEventStore> event_store)
    : event_store_(std::move(event_store)) {
}

void CommandDispatcher::dispatch(const ICommand &command) {
    std::type_index commandTypeIndex(typeid(command));
    auto it = handlers_.find(commandTypeIndex);
    if (it == handlers_.end()) {
        throw std::runtime_error("[CommandDispatcher] Unknown command type");
    }
    std::vector<std::shared_ptr<IDomainEvent> > events = it->second->handleCommand(command);
    for (const auto &event: events) {
        if (event != nullptr) {
            event_store_->append(*event);
        }
    }
}
