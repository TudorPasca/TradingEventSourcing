#pragma once

#include "IAggregate.h"

class AccountAggregate: public IAggregate {
public:
    explicit AccountAggregate(int user_id);

    double getBalance() const;
    void addBalance(double sum);
    void subtractBalance(double sum);
private:
    int user_id_;
    double balance_;
};
