#include "../../include/command/DepositFundsCommand.h"

DepositFundsCommand::DepositFundsCommand(int user_id, double quantity)
    : user_id_(user_id), quantity_(quantity) {
}

std::unique_ptr<DepositFundsCommand> DepositFundsCommand::fromTokens(const std::vector<std::string> &tokens) {
    if (tokens.size() - 1 != DepositFundsCommand::ARGUMENT_COUNT) {
        throw std::runtime_error("[DepositFundsCommand] Wrong number of arguments");
    }
    int userId = stoi(tokens[1]);
    double quantity = stod(tokens[2]);
    if (quantity <= 0.0) {
        throw std::runtime_error("[DepositFundsCommand] Quantity cannot be negative");
    }
    return std::make_unique<DepositFundsCommand>(userId, quantity);
}

int DepositFundsCommand::getUserId() const {
    return user_id_;
}

double DepositFundsCommand::getQuantity() const {
    return quantity_;
}
