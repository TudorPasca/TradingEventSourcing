#include "../../include/command/PlaceOrderCommand.h"

PlaceOrderCommand::PlaceOrderCommand(int user_id, Order::OrderType type, std::string symbol, int quantity, double price)
    : user_id_(user_id), type_(type), symbol_(std::move(symbol)), quantity_(quantity), price_(price) {
}

std::unique_ptr<PlaceOrderCommand> PlaceOrderCommand::fromTokens(const std::vector<std::string> &tokens) {
    if (tokens.size() - 1 != PlaceOrderCommand::ARGUMENT_COUNT) {
        throw std::runtime_error("[PlaceOrderCommand] Wrong number of arguments");
    }
    int userId = stoi(tokens[1]);
    Order::OrderType type;
    if (tokens[2] == "BUY") {
        type = Order::OrderType::BUY;
    } else if (tokens[2] == "SELL") {
        type = Order::OrderType::SELL;
    } else {
        throw std::runtime_error("[PlaceOrderCommand] Order type must be BUY or SELL");
    }
    std::string symbol = tokens[3];
    int quantity = stoi(tokens[4]);
    double price = stod(tokens[5]);
    if (quantity <= 0 || price < 0.0) {
        throw std::runtime_error("[PlaceOrderCommand] Quantity and price must have positive values");
    }
    return std::make_unique<PlaceOrderCommand>(userId, type, symbol, quantity, price);
}
