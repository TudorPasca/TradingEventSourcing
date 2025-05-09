#pragma once

#include "ILogger.h"
#include "../event/DomainEvent.h"
#include <fstream>

class FileLogger: public ILogger {
public:
    explicit FileLogger(std::string filename);
    void append(const std::string& message) override;
    void append(const DomainEvent& event) override;
    void append(const DomainEvent *event) override;
    std::vector<std::unique_ptr<DomainEvent>> getAllEvents() override;
private:
    std::ofstream out_fs_;
    std::ifstream in_fs_;
    std::string filename_;

    static std::string getEventTypeFromJson(const std::string & json_str);
};