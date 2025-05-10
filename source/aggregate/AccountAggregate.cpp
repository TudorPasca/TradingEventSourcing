#include "../../include/aggregate/AccountAggregate.h"

#include <stdexcept>

AccountAggregate::AccountAggregate(int user_id)
    : user_id_(user_id) {
    balance_ = 0.0;
}

void AccountAggregate::addBalance(double sum) {
    balance_ += sum;
}

void AccountAggregate::subtractBalance(double sum) {
    if (sum > balance_) {
        throw std::runtime_error(
            "[AccountAggregate] Failed to withdraw. Insufficient balance in account of user " + user_id_);
    }
    balance_ -= sum;
}
