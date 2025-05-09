#pragma once

#include "DomainEvent.h"

class OrderPlaced: public DomainEvent {
public:
    OrderPlaced(std::string event_id, int user_id, Order::OrderType type, std::string symbol, int quantity);
    explicit OrderPlaced(const std::string &json_string);

    std::string toJson() const override;

private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
};