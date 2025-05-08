#include "../../include/event/DomainEvent.h"

DomainEvent::DomainEvent(std::string event_id)
        : event_id_(std::move(event_id)), timestamp_(std::chrono::system_clock::now()) {}

std::string DomainEvent::getFormattedTimestamp() const {
    using namespace std::chrono_literals;
    return std::format("{:%Y %m %d %H %M}", timestamp_);
}