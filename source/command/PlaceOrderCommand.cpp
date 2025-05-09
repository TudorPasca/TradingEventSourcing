#include "../../include/command/PlaceOrderCommand.h"

PlaceOrderCommand::PlaceOrderCommand(int user_id, Order::OrderType type, std::string symbol, int quantity)
        : user_id_(user_id), type_(type), symbol_(std::move(symbol)), quantity_(quantity) {}