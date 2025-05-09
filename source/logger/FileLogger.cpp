#include "../../include/logger/FileLogger.h"

FileLogger::FileLogger(const std::string &filename) {
    out_.open(filename);
    if (!out_.is_open()) {
        throw std::runtime_error("[FileLogger] Failed to open log file: " + filename);
    }
}

void FileLogger::log(const std::string &message) {
    if (out_.is_open())
        out_ << message << std::endl;
}

void FileLogger::log(const DomainEvent &event) {
    if (out_.is_open())
        out_ << event.toJson() << std::endl;
}

void FileLogger::log(const DomainEvent *event) {
    if (event != nullptr && out_.is_open())
        out_ << event->toJson() << std::endl;
}