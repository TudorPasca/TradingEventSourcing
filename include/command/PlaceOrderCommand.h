#pragma once

#include <memory>

#include "../order/OrderType.h"
#include "ICommand.h"
#include <string>
#include <vector>

class PlaceOrderCommand : public ICommand {
public:
    static constexpr std::string COMMAND_NAME = "place_order";
    static constexpr int ARGUMENT_COUNT = 5;

    PlaceOrderCommand(int user_id, Order::OrderType type, std::string symbol, int quantity, double price);

    static std::unique_ptr<PlaceOrderCommand> fromTokens(const std::vector<std::string> &tokens);

private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
    double price_;
};
