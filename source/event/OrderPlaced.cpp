#include "../../include/event/OrderPlaced.h"

OrderPlaced::OrderPlaced(std::string event_id, int user_id, Order::OrderType type, std::string symbol, int quantity)
        : DomainEvent(std::move(event_id)), user_id_(user_id), type_(type), symbol_(std::move(symbol)),
          quantity_(quantity) {}

std::string OrderPlaced::toJson() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"eventId\": \"" << event_id_ << "\", ";
    oss << "\"timestamp\": \"" << getFormattedTimestamp() << "\", ";
    oss << "\"eventType\": \"OrderPlaced\", ";
    oss << "\"userId\": \"" << user_id_;
    oss << "\"orderType\": " << (type_ == Order::OrderType::BUY ? "BUY" : "SELL") << ", ";
    oss << "\"symbol\": " << symbol_;
    oss << "\"quantity\": " << quantity_;
    oss << "}";
    return oss.str();
}