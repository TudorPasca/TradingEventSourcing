#pragma once
#include "ICommandHandler.h"
#include "../repository/AccountRepository.h"
#include "../repository/OrderBookRepository.h"

class PlaceOrderCommand;

struct PlaceOrderCommandHandler : public ICommandHandler<PlaceOrderCommand> {
public:
    PlaceOrderCommandHandler(std::shared_ptr<AccountRepository> accountRepository,
                             std::shared_ptr<OrderBookRepository> orderBookRepository);

protected:
    std::vector<std::shared_ptr<IDomainEvent> > handleInternal(const PlaceOrderCommand &command) override;

private:
    std::shared_ptr<AccountRepository> accountRepository;
    std::shared_ptr<OrderBookRepository> orderBookRepository;
};
