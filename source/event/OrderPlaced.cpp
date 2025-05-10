#include "../../include/event/OrderPlaced.h"

OrderPlaced::OrderPlaced(std::string event_id, int user_id, Order::OrderType type, std::string symbol, int quantity,
                         double price)
    : IDomainEvent(std::move(event_id)), user_id_(user_id), type_(type), symbol_(std::move(symbol)),
      quantity_(quantity), price_(price) {
}

OrderPlaced::OrderPlaced(const std::string &json_string)
    : IDomainEvent(nlohmann::json::parse(json_string)) {
    using json = nlohmann::json;
    try {
        json j = json::parse(json_string);
        std::string eventType_from_json = j.at("eventType").get<std::string>();
        if (eventType_from_json != OrderPlaced::EVENT_TYPE) {
            throw std::runtime_error("[OrderPlaced] Mismatched eventType. Expected 'OrderPlaced', got '" +
                                     eventType_from_json + "'.");
        }
        user_id_ = j.at("userId").get<int>();
        quantity_ = j.at("quantity").get<int>();
        type_ = (j.at("orderType").get<std::string>() == "BUY") ? Order::OrderType::BUY : Order::OrderType::SELL;
        symbol_ = j.at("symbol").get<std::string>();
        price_ = j.at("price").get<double>();
    } catch (const json::exception &e) {
        throw std::runtime_error(
            "[OrderPlaced] JSON parsing error: " + std::string(e.what()) + " from JSON: " + json_string);
    }
}

void OrderPlaced::acceptVisitor(IEventVisitor &visitor) const {
    visitor.visit(*this);
}

std::string OrderPlaced::toJson() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"eventId\": \"" << event_id_ << "\", ";
    oss << "\"timestamp\": \"" << getNanosecondsTimestamp() << "\", ";
    oss << "\"eventType\": \"" << OrderPlaced::EVENT_TYPE << "\", ";
    oss << "\"userId\": \"" << user_id_;
    oss << "\"orderType\": " << (type_ == Order::OrderType::BUY ? "BUY" : "SELL") << ", ";
    oss << "\"symbol\": " << symbol_;
    oss << "\"quantity\": " << quantity_;
    oss << "\"price\": " << price_;
    oss << "}";
    return oss.str();
}

int OrderPlaced::getUserId() const {
    return user_id_;
}

Order::OrderType OrderPlaced::getType() const {
    return type_;
}

double OrderPlaced::getPrice() const {
    return price_;
}

int OrderPlaced::getQuantity() const {
    return quantity_;
}

std::string OrderPlaced::getSymbol() const {
    return symbol_;
}
