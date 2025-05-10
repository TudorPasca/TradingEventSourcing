#pragma once

#include "../order/Order.h"
#include "ICommand.h"
#include <string>

class PlaceOrderCommand: public ICommand {
public:
    PlaceOrderCommand(int user_id, Order::OrderType type, std::string symbol, int quantity, double price);
private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
    double price_;
};