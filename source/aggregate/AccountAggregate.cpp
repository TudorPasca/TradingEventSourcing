#include "../../include/aggregate/AccountAggregate.h"

#include <stdexcept>

#include "../../include/event/FundsCredited.h"
#include "../../include/event/FundsDebited.h"

AccountAggregate::AccountAggregate(int user_id)
    : user_id_(user_id) {
    balance_ = 0.0;
}

double AccountAggregate::getBalance() const {
    return balance_;
}


std::vector<std::shared_ptr<IDomainEvent>> AccountAggregate::addBalance(double sum) {
    balance_ += sum;
    auto event = std::make_shared<FundsCredited>(1, user_id_, sum);
    return {event};
}

std::vector<std::shared_ptr<IDomainEvent>> AccountAggregate::subtractBalance(double sum) {
    if (sum > balance_) {
        throw std::runtime_error(
            "[AccountAggregate] Failed to withdraw. Insufficient balance in account of user " + user_id_);
    }
    balance_ -= sum;
    auto event = std::make_shared<FundsDebited>("1", user_id_, sum);
    return {event};
}
