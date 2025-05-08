#pragma once

#include "DomainEvent.h"

class OrderCancelled: public DomainEvent {
public:
    OrderCancelled(std::string event_id, int user_id, Order::OrderType type, std::string symbol, int quantity);
    std::string toJson() const override;

private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
};