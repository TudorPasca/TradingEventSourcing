#pragma once

#include "../event/IDomainEvent.h"
#include <string>
#include <memory>

struct IEventStore {
  virtual ~IEventStore() = default;
  virtual void append(const std::string& message) = 0;
  virtual void append(const IDomainEvent& event) = 0;
  virtual void append(const IDomainEvent *event) = 0;
  virtual std::vector<std::unique_ptr<IDomainEvent>> getAllEvents() = 0;
};