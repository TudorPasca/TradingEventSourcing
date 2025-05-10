#pragma once

#include "IDomainEvent.h"

class FundsCredited : public IDomainEvent {
public:
    static constexpr std::string EVENT_TYPE = "FundsCredited";

    FundsCredited(std::string event_id, int user_id, double quantity);

    explicit FundsCredited(const std::string &json_string);

    void acceptVisitor(IEventVisitor &visitor) override;

    std::string toJson() const override;

private:
    int user_id_;
    double quantity_;
};
