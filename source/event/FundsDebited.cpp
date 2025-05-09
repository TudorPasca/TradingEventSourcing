#include "../../include/event/FundsDebited.h"

FundsDebited::FundsDebited(std::string event_id, int user_id, int quantity)
        : IDomainEvent(std::move(event_id)), user_id_(user_id), quantity_(quantity) {}

FundsDebited::FundsDebited(const std::string &json_string)
        : IDomainEvent(nlohmann::json::parse(json_string)) {
    using json = nlohmann::json;
    try {
        json j = json::parse(json_string);
        std::string eventType_from_json = j.at("eventType").get<std::string>();
        if (eventType_from_json != FundsDebited::EVENT_TYPE) {
            throw std::runtime_error("[FundsDebited] Mismatched eventType. Expected 'FundsDebited', got '" +
                                     eventType_from_json + "'.");
        }
        user_id_ = j.at("userId").get<int>();
        quantity_ = j.at("quantity").get<int>();
    } catch (const json::exception &e) {
        throw std::runtime_error(
                "[FundsDebited] JSON parsing error: " + std::string(e.what()) + " from JSON: " + json_string);
    }
}

std::string FundsDebited::toJson() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"eventId\": \"" << event_id_ << "\", ";
    oss << "\"timestamp\": \"" << getNanosecondsTimestamp() << "\", ";
    oss << "\"eventType\": \"" << FundsDebited::EVENT_TYPE << "\", ";
    oss << "\"userId\": " << user_id_ << ", ";
    oss << "\"quantity\": " << quantity_;
    oss << "}";
    return oss.str();
}