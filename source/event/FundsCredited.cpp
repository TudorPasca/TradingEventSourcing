#include "../../include/event/FundsCredited.h"
#include <sstream>

FundsCredited::FundsCredited(std::string event_id, int user_id, double quantity)
        : IDomainEvent(std::move(event_id)), user_id_(user_id), quantity_(quantity) {}

FundsCredited::FundsCredited(const std::string &json_string)
        : IDomainEvent(nlohmann::json::parse(json_string)) {
    using json = nlohmann::json;
    try {
        json j = json::parse(json_string);
        std::string eventType_from_json = j.at("eventType").get<std::string>();
        if (eventType_from_json != FundsCredited::EVENT_TYPE) {
            throw std::runtime_error("[FundsCredited] Mismatched eventType. Expected 'FundsCredited', got '" +
                                     eventType_from_json + "'.");
        }
        user_id_ = j.at("userId").get<int>();
        quantity_ = j.at("quantity").get<int>();
    } catch (const json::exception &e) {
        throw std::runtime_error(
                "FundsCredited JSON parsing error: " + std::string(e.what()) + " from JSON: " + json_string);
    }
}

void FundsCredited::acceptVisitor(IEventVisitor &visitor) const {
    visitor.visit(*this);
}

std::string FundsCredited::toJson() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"eventId\": \"" << event_id_ << "\", ";
    oss << "\"timestamp\": " << getNanosecondsTimestamp() << ", ";
    oss << "\"eventType\": \"" << FundsCredited::EVENT_TYPE << "\", ";
    oss << "\"userId\": " << user_id_ << ", ";
    oss << "\"quantity\": " << quantity_;
    oss << "}";
    return oss.str();
}

int FundsCredited::getUserId() const {
    return user_id_;
}

double FundsCredited::getQuantity() const {
    return quantity_;
}
