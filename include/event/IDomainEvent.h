#pragma once

#include "nlohmann/json.hpp"
#include "../repository/IEventVisitor.h"
#include "../order/OrderType.h"
#include <string>
#include <chrono>

struct IDomainEvent {
    explicit IDomainEvent(std::string event_id);

    explicit IDomainEvent(const nlohmann::json &j);

    virtual ~IDomainEvent() = default;

    virtual void acceptVisitor(IEventVisitor &visitor) const = 0;

    virtual std::string toJson() const = 0;

    long long getNanosecondsTimestamp() const;

    std::string getEventId() const;

protected:
    std::chrono::system_clock::time_point timestamp_;
    std::string event_id_;
};
