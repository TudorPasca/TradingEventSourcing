#pragma once

#include "IDomainEvent.h"

class TradeExecuted : public IDomainEvent {
public:
    static constexpr std::string EVENT_TYPE = "TradeExecuted";

    TradeExecuted(std::string event_id, int buyer_id, int seller_id, std::string symbol, int quantity, double price);

    explicit TradeExecuted(const std::string &json_string);

    void acceptVisitor(IEventVisitor &visitor) override;

    std::string toJson() const override;

private:
    int buyer_id_;
    int seller_id_;
    std::string symbol_;
    int quantity_;
    double price_;
};
