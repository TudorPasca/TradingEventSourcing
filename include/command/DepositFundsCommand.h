#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ICommand.h"

class DepositFundsCommand: public ICommand {
public:
    static constexpr std::string COMMAND_NAME = "deposit_funds";
    static constexpr int ARGUMENT_COUNT = 2;

    DepositFundsCommand(int user_id, double quantity);

    static std::unique_ptr<DepositFundsCommand> fromTokens(const std::vector<std::string> &tokens);

private:
    int user_id_;
    double quantity_;
};