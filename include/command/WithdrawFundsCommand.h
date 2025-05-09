#pragma once

#include "Command.h"

class WithdrawFundsCommand: public Command {
public:
    WithdrawFundsCommand(int user_id, int quantity);
private:
    int user_id_;
    int quantity_;
};