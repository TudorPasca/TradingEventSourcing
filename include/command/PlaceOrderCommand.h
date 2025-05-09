#pragma once

#include "../order/Order.h"
#include "Command.h"
#include <string>

class PlaceOrderCommand: public Command {
public:
    PlaceOrderCommand(int user_id, Order::OrderType type, std::string symbol, int quantity);
private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
};