#pragma once

#include "IDomainEvent.h"

class FundsDebited : public IDomainEvent {
public:
    static constexpr std::string EVENT_TYPE = "FundsDebited";

    FundsDebited(std::string event_id, int user_id, double quantity);

    explicit FundsDebited(const std::string &json_string);

    void acceptVisitor(IEventVisitor &visitor) const override;

    std::string toJson() const override;

    int getUserId() const;

    double getQuantity() const;

private:
    int user_id_;
    double quantity_;
};
