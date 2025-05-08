#pragma once

#include "DomainEvent.h"

class TradeExecuted: public DomainEvent {
public:
    TradeExecuted(std::string event_id, int buyer_id, int seller_id, std::string symbol, int quantity);
    std::string toJson() const override;

private:
    int buyer_id_;
    int seller_id_;
    std::string symbol_;
    int quantity_;
};