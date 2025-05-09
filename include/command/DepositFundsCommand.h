#pragma once

#include "Command.h"

class DepositFundsCommand: public Command {
public:
    DepositFundsCommand(int user_id, int quantity);
private:
    int user_id_;
    int quantity_;
};