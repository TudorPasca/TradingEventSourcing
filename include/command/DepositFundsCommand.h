#pragma once

#include "ICommand.h"

class DepositFundsCommand: public ICommand {
public:
    DepositFundsCommand(int user_id, int quantity);
private:
    int user_id_;
    int quantity_;
};