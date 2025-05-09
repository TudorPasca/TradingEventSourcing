#pragma once

#include "nlohmann/json.hpp"
#include <string>
#include <chrono>

namespace Order {
    enum OrderType {
        BUY, SELL
    };
}

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