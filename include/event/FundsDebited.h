#pragma once

#include "DomainEvent.h"

class FundsDebited: public DomainEvent {
public:
    FundsDebited(std::string event_id, int user_id, int quantity);
    explicit FundsDebited(const std::string &json_string);

    std::string toJson() const override;

private:
    int user_id_;
    int quantity_;
};