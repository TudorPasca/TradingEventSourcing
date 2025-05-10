#include "../../include/command/CancelOrderCommand.h"

CancelOrderCommand::CancelOrderCommand(int user_id, Order::OrderType type, std::string symbol, int quantity, double price)
        : user_id_(user_id), type_(type), symbol_(std::move(symbol)), quantity_(quantity), price_(price) {}
