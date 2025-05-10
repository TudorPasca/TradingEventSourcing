#include "../../include/event/TradeExecuted.h"

TradeExecuted::TradeExecuted(std::string event_id, int buyer_id, int seller_id, std::string symbol, int quantity, double price)
        : IDomainEvent(std::move(event_id)), buyer_id_(buyer_id), seller_id_(seller_id), symbol_(std::move(symbol)),
          quantity_(quantity), price_(price) {}

TradeExecuted::TradeExecuted(const std::string &json_string)
        : IDomainEvent(nlohmann::json::parse(json_string)) {
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
        price_ = j.at("price").get<double>();
    } catch (const json::exception &e) {
        throw std::runtime_error(
                "[OrderCancelled] JSON parsing error: " + std::string(e.what()) + " from JSON: " + json_string);
    }
}

void TradeExecuted::acceptVisitor(IEventVisitor &visitor) const {
    visitor.visit(*this);
}

std::string TradeExecuted::toJson() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"eventId\": \"" << event_id_ << "\", ";
    oss << "\"timestamp\": \"" << getNanosecondsTimestamp() << "\", ";
    oss << "\"eventType\": \"" << TradeExecuted::EVENT_TYPE << "\", ";
    oss << "\"buyerId\": \"" << buyer_id_;
    oss << "\"sellerId\": \"" << seller_id_;
    oss << "\"symbol\": " << symbol_;
    oss << "\"quantity\": " << quantity_;
    oss << "\"price\": " << price_;
    oss << "}";
    return oss.str();
}

int TradeExecuted::getSellerId() const {
    return seller_id_;
}

int TradeExecuted::getBuyerId() const {
    return buyer_id_;
}

std::string TradeExecuted::getSymbol() const {
    return symbol_;
}

int TradeExecuted::getQuantity() const {
    return quantity_;
}

double TradeExecuted::getPrice() const {
    return price_;
}

