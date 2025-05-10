#pragma once

#include "../command/ICommand.h"
#include <memory>
#include <vector>

#include "../command/CancelOrderCommand.h"
#include "../command/DepositFundsCommand.h"
#include "../command/WithdrawFundsCommand.h"

class PlaceOrderCommand;

class InputParser {
public:
    static std::unique_ptr<ICommand> parseCommand(const std::string &commandLine);
private:
    static std::vector<std::string> splitBySeparator(const std::string &str, char delimiter = ' ');
    static std::unique_ptr<PlaceOrderCommand> parsePlaceOrderCommand(const std::vector<std::string> &tokens);
    static std::unique_ptr<CancelOrderCommand> parseCancelOrderCommand(const std::vector<std::string> &tokens);
    static std::unique_ptr<DepositFundsCommand> parseDepositFundsCommand(const std::vector<std::string> &tokens);
    static std::unique_ptr<WithdrawFundsCommand> parseWithdrawFundsCommand(const std::vector<std::string> &tokens);
};
