#pragma once

#include "../event/DomainEvent.h"
#include <string>

struct ILogger {
  virtual ~ILogger() = default;
  virtual void log(const std::string& message) = 0;
  virtual void log(const DomainEvent& event) = 0;
  virtual void log(const DomainEvent *event) = 0;
};