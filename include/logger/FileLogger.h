#pragma once

#include "ILogger.h"
#include "../event/DomainEvent.h"
#include <fstream>

class FileLogger: public ILogger {
public:
    explicit FileLogger(const std::string& filename);
    void log(const std::string& message) override;
    void log(const DomainEvent& event) override;
    void log(const DomainEvent *event) override;
private:
    std::ofstream out_;
};