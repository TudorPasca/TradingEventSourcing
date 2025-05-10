#pragma once

#include "IEventStore.h"
#include "../event/IDomainEvent.h"
#include <fstream>

class FileEventStore: public IEventStore {
public:
    explicit FileEventStore(std::string filename);
    void append(const std::string& message) override;
    void append(const IDomainEvent& event) override;
    void append(const IDomainEvent *event) override;
    std::vector<std::unique_ptr<IDomainEvent>> getAllEvents() override;
private:
    std::ofstream out_fs_;
    std::ifstream in_fs_;
    std::string filename_;

    static std::string getEventTypeFromJson(const std::string & json_str);
};