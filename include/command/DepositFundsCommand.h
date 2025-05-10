#pragma once

#include "ICommand.h"

class DepositFundsCommand: public ICommand {
public:
    DepositFundsCommand(int user_id, double quantity);
private:
    int user_id_;
    double quantity_;
};