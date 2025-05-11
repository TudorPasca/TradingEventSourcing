#pragma once

#include "IAggregate.h"
#include "../event/IDomainEvent.h"

class AccountAggregate: public IAggregate {
public:
    explicit AccountAggregate(int user_id);

    double getBalance() const;
    std::vector<std::shared_ptr<IDomainEvent>> addBalance(double sum);
    std::vector<std::shared_ptr<IDomainEvent>> subtractBalance(double sum);
private:
    int user_id_;
    double balance_;
};
