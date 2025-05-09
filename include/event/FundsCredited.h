#pragma once

#include "DomainEvent.h"

class FundsCredited: public DomainEvent {
public:
    FundsCredited(std::string event_id, int user_id, int quantity);
    explicit FundsCredited(const std::string &json_string);

    std::string toJson() const override;

private:
    int user_id_;
    int quantity_;
};