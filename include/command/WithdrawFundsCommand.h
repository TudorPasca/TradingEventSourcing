#pragma once

#include <memory>
#include <vector>

#include "ICommand.h"

class WithdrawFundsCommand : public ICommand {
public:
    static constexpr std::string COMMAND_NAME = "withdraw_funds";
    static constexpr int ARGUMENT_COUNT = 2;

    WithdrawFundsCommand(int user_id, double quantity);

    static std::unique_ptr<WithdrawFundsCommand> fromTokens(const std::vector<std::string> &tokens);

    int getUserId() const;
    double getQuantity() const;
private:
    int user_id_;
    double quantity_;
};
