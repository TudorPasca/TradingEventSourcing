#pragma once

#include "../event/DomainEvent.h"
#include <string>
#include <memory>

struct ILogger {
  virtual ~ILogger() = default;
  virtual void append(const std::string& message) = 0;
  virtual void append(const DomainEvent& event) = 0;
  virtual void append(const DomainEvent *event) = 0;
  virtual std::vector<std::unique_ptr<DomainEvent>> getAllEvents() = 0;
};