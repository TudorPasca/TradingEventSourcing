#pragma once

#include "ICommand.h"

class WithdrawFundsCommand: public ICommand {
public:
    WithdrawFundsCommand(int user_id, int quantity);
private:
    int user_id_;
    int quantity_;
};