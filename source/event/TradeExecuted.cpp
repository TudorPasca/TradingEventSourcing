#include "../../include/event/TradeExecuted.h"

TradeExecuted::TradeExecuted(std::string event_id, int buyer_id, int seller_id, std::string symbol, int quantity)
        : DomainEvent(std::move(event_id)), buyer_id_(buyer_id), seller_id_(seller_id), symbol_(std::move(symbol)),
          quantity_(quantity) {}

TradeExecuted::TradeExecuted(const std::string &json_string)
        : DomainEvent(nlohmann::json::parse(json_string)) {
    using json = nlohmann::json;
    try {
        json j = json::parse(json_string);
        std::string eventType_from_json = j.at("eventType").get<std::string>();
        if (eventType_from_json != TradeExecuted::EVENT_TYPE) {
            throw std::runtime_error("[OrderCancelled] Mismatched eventType. Expected 'TradeExecuted', got '" +
                                     eventType_from_json + "'.");
        }
        buyer_id_ = j.at("buyerId").get<int>();
        seller_id_ = j.at("sellerId").get<int>();
        quantity_ = j.at("quantity").get<int>();
        symbol_ = j.at("symbol").get<std::string>();
    } catch (const json::exception &e) {
        throw std::runtime_error(
                "[OrderCancelled] JSON parsing error: " + std::string(e.what()) + " from JSON: " + json_string);
    }
}

std::string TradeExecuted::toJson() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"eventId\": \"" << event_id_ << "\", ";
    oss << "\"timestamp\": \"" << getNanosecondsTimestamp() << "\", ";
    oss << "\"eventType\": \"TradeExecuted\", ";
    oss << "\"buyerId\": \"" << buyer_id_;
    oss << "\"sellerId\": \"" << seller_id_;
    oss << "\"symbol\": " << symbol_;
    oss << "\"quantity\": " << quantity_;
    oss << "}";
    return oss.str();
}
