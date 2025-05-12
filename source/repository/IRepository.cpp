#include "../../include/repository/IRepository.h"

void IRepository::rehydrate(const std::vector<std::unique_ptr<IDomainEvent>> &events) {
    for (const auto &event: events) {
        processEvent(*event);
    }
}
