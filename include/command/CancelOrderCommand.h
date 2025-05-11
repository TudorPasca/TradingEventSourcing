#pragma once

#include <memory>

#include "../order/OrderType.h"
#include "ICommand.h"
#include <string>
#include <vector>

class CancelOrderCommand: public ICommand {
public:
    static constexpr std::string COMMAND_NAME = "cancel_order";
    static constexpr int ARGUMENT_COUNT = 5;

    CancelOrderCommand(int user_id, Order::OrderType type, std::string symbol, int quantity, double price);

    static std::unique_ptr<CancelOrderCommand> fromTokens(const std::vector<std::string> &tokens);

    int getUserId() const;
    Order::OrderType getType() const;
    std::string getSymbol() const;
    int getQuantity() const;
    double getPrice() const;
private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
    double price_;
};
