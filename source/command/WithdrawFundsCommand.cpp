#include "../../include/command/WithdrawFundsCommand.h"

WithdrawFundsCommand::WithdrawFundsCommand(int user_id, double quantity)
        : user_id_(user_id), quantity_(quantity) {}