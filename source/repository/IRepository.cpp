#include "../../include/repository/IRepository.h"

void IRepository::rehydrate(const std::vector<IDomainEvent> &events) {
    for (const auto &event: events) {
        processEvent(event);
    }
}
