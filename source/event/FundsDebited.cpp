#include "../../include/event/FundsDebited.h"

FundsDebited::FundsDebited(std::string event_id, int user_id, int quantity)
        : DomainEvent(std::move(event_id)), user_id_(user_id), quantity_(quantity) {}

std::string FundsDebited::toJson() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"eventId\": \"" << event_id_ << "\", ";
    oss << "\"timestamp\": \"" << getFormattedTimestamp() << "\", ";
    oss << "\"eventType\": \"FundsDebited\", ";
    oss << "\"userId\": " << user_id_ << ", ";
    oss << "\"quantity\": " << quantity_;
    oss << "}";
    return oss.str();
}