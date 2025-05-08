#include "../../include/event/TradeExecuted.h"

TradeExecuted::TradeExecuted(std::string event_id, int buyer_id, int seller_id, std::string symbol, int quantity)
        : DomainEvent(std::move(event_id)), buyer_id_(buyer_id), seller_id_(seller_id), symbol_(std::move(symbol)),
          quantity_(quantity) {}

std::string TradeExecuted::toJson() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"eventId\": \"" << event_id_ << "\", ";
    oss << "\"timestamp\": \"" << getFormattedTimestamp() << "\", ";
    oss << "\"eventType\": \"TradeExecuted\", ";
    oss << "\"buyerId\": \"" << buyer_id_;
    oss << "\"sellerId\": \"" << seller_id_;
    oss << "\"symbol\": " << symbol_;
    oss << "\"quantity\": " << quantity_;
    oss << "}";
    return oss.str();
}
