#include "../../include/event/IDomainEvent.h"

IDomainEvent::IDomainEvent(std::string event_id)
        : event_id_(std::move(event_id)), timestamp_(std::chrono::system_clock::now()) {}

IDomainEvent::IDomainEvent(const nlohmann::json& j) {
    try {
        event_id_ = j.at("eventId").get<std::string>();
        long long nanoseconds_since_epoch = j.at("timestamp").get<long long>();
        timestamp_ = std::chrono::system_clock::time_point(
                std::chrono::nanoseconds(nanoseconds_since_epoch)
        );
    } catch (const nlohmann::json::exception& e) {
        throw std::runtime_error("[IDomainEvent] JSON parsing error: " + std::string(e.what()) + " in JSON: " + j.dump(2));
    }
}

long long IDomainEvent::getNanosecondsTimestamp() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(timestamp_.time_since_epoch()).count();
}