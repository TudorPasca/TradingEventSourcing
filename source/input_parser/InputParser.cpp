#include "../../include/input_parser/InputParser.h"
#include <sstream>
#include <stdexcept>

#include "../../include/command/PlaceOrderCommand.h"
#include "../../include/order/Order.h"

std::unique_ptr<ICommand> InputParser::parseCommand(const std::string &commandLine) {
    if (commandLine.empty()) {
        throw std::runtime_error("[InputParser] Command cannot be empty");
    }
    std::vector<std::string> tokens = splitBySeparator(commandLine);
    if (tokens.empty()) {
        throw std::runtime_error("[InputParser] Invalid command format");
    }
    const std::string &commandType = tokens[0];
    std::unique_ptr<ICommand> command;
    if (commandType == PlaceOrderCommand::COMMAND_NAME) {
        command = PlaceOrderCommand::fromTokens(tokens);
    } else if (commandType == CancelOrderCommand::COMMAND_NAME) {
        command = CancelOrderCommand::fromTokens(tokens);
    } else if (commandType == DepositFundsCommand::COMMAND_NAME) {
        command = DepositFundsCommand::fromTokens(tokens);
    } else if (commandType == WithdrawFundsCommand::COMMAND_NAME) {
        command = WithdrawFundsCommand::fromTokens(tokens);
    }
    return command;
}

std::vector<std::string> InputParser::splitBySeparator(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

