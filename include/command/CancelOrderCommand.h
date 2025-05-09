#pragma once

#include "../order/Order.h"
#include "ICommand.h"
#include <string>

class CancelOrderCommand: public ICommand {
public:
    CancelOrderCommand(int user_id, Order::OrderType type, std::string symbol, int quantity);
private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
};