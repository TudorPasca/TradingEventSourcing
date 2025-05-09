#pragma once

#include "nlohmann/json.hpp"
#include "../order/Order.h"
#include <string>
#include <chrono>

struct DomainEvent {
    explicit DomainEvent(std::string event_id);
    explicit DomainEvent(const nlohmann::json &j);

    virtual ~DomainEvent() = default;

    virtual std::string toJson() const = 0;
    long long getNanosecondsTimestamp() const;
protected:
    std::chrono::system_clock::time_point timestamp_;
    std::string event_id_;
};