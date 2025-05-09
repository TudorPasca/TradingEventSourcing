#include <iostream>
#include "../../include/logger/FileLogger.h"
#include "../../include/event/FundsCredited.h"
#include "../../include/event/OrderPlaced.h"
#include "../../include/event/OrderCancelled.h"
#include "../../include/event/FundsDebited.h"
#include "../../include/event/TradeExecuted.h"

FileLogger::FileLogger(std::string filename)
        : filename_(std::move(filename)) {
    out_fs_.open(filename_);
    if (!out_fs_.is_open()) {
        throw std::runtime_error("[FileLogger] Failed to open log file for WRITING: " + filename_);
    }
}

void FileLogger::append(const std::string &message) {
    if (out_fs_.is_open())
        out_fs_ << message << std::endl;
}

void FileLogger::append(const IDomainEvent &event) {
    if (out_fs_.is_open())
        out_fs_ << event.toJson() << std::endl;
}

void FileLogger::append(const IDomainEvent *event) {
    if (event != nullptr && out_fs_.is_open())
        out_fs_ << event->toJson() << std::endl;
}

std::string FileLogger::getEventTypeFromJson(const std::string &json_str) {
    std::string targetKey = R"("eventType": ")";
    size_t keyPos = json_str.find(targetKey);
    if (keyPos == std::string::npos) {
        throw std::runtime_error("[FileLogger] Failed to find event type for log entry");
    }
    size_t valueStartPos = keyPos + targetKey.length();
    size_t valueEndPos = json_str.find('\"', valueStartPos);
    if (valueEndPos == std::string::npos) {
        throw std::runtime_error("[FileLogger] Failed to find event type for log entry");
    }
    return json_str.substr(valueStartPos, valueEndPos - valueStartPos);
}

std::vector<std::unique_ptr<IDomainEvent>> FileLogger::getAllEvents() {
    std::vector<std::unique_ptr<IDomainEvent>> events;
    in_fs_.open(filename_);
    if (!in_fs_.is_open()) {
        throw std::runtime_error("[FileLogger] Failed to open log file for READING: " + filename_);
    }
    std::string entry;
    while (std::getline(in_fs_, entry)) {
        if (entry.empty() || entry.find('{') == std::string::npos) {
            continue;
        }
        try {
            std::string eventType = getEventTypeFromJson(entry);
            if (eventType == "FundsCredited") {
                events.push_back(std::make_unique<FundsCredited>(entry));
            } else if (eventType == "FundsDebited") {
                events.push_back(std::make_unique<FundsDebited>(entry));
            } else if (eventType == "OrderCancelled") {
                events.push_back(std::make_unique<OrderCancelled>(entry));
            } else if (eventType == "OrderPlaced") {
                events.push_back(std::make_unique<OrderPlaced>(entry));
            } else if (eventType == "TradeExecuted") {
                events.push_back(std::make_unique<TradeExecuted>(entry));
            }
        } catch (const std::exception &e) {
            std::cerr << "[FileLogger] Error parsing events from log at \"" + entry + "\":" << e.what() << std::endl;
        }
    }
    return events;
}