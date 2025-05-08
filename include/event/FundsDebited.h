#pragma once

#include "DomainEvent.h"

class FundsDebited: public DomainEvent {
public:
    FundsDebited(std::string event_id, int user_id, int quantity);
    std::string toJson() const override;

private:
    int user_id_;
    int quantity_;
};