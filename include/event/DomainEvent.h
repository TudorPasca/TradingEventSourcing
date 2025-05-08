#pragma once

#include <string>
#include <chrono>

namespace Order {
    enum OrderType {
        BUY, SELL
    };
}

struct DomainEvent {
    DomainEvent(std::string event_id);
    virtual ~DomainEvent() = default;

    virtual std::string toJson() const = 0;
    std::string getFormattedTimestamp() const;
protected:
    std::chrono::system_clock::time_point timestamp_;
    std::string event_id_;
};