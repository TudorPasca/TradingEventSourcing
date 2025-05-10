#include "../../include/command/WithdrawFundsCommand.h"

WithdrawFundsCommand::WithdrawFundsCommand(int user_id, double quantity)
    : user_id_(user_id), quantity_(quantity) {
}

std::unique_ptr<WithdrawFundsCommand> WithdrawFundsCommand::fromTokens(const std::vector<std::string> &tokens) {
    if (tokens.size() - 1 != WithdrawFundsCommand::ARGUMENT_COUNT) {
        throw std::runtime_error("[WithdrawFundsCommand] Wrong number of arguments");
    }
    int userId = stoi(tokens[1]);
    double quantity = stod(tokens[2]);
    if (quantity <= 0.0) {
        throw std::runtime_error("[WithdrawFundsCommand] Quantity cannot be negative");
    }
    return std::make_unique<WithdrawFundsCommand>(userId, quantity);
}
