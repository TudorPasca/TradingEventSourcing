#pragma once

#include "ICommand.h"

class WithdrawFundsCommand: public ICommand {
public:
    WithdrawFundsCommand(int user_id, double quantity);
private:
    int user_id_;
    double quantity_;
};