#pragma once
#include "ICommandHandler.h"
#include "../command/CancelOrderCommand.h"
#include "../repository/AccountRepository.h"
#include "../repository/OrderBookRepository.h"

struct CancelOrderCommandHandler : public ICommandHandler<CancelOrderCommand> {
public:
    CancelOrderCommandHandler(std::shared_ptr<AccountRepository> accountRepository,
                              std::shared_ptr<OrderBookRepository> orderBookRepository);

protected:
    std::vector<std::shared_ptr<IDomainEvent> > handleInternal(const CancelOrderCommand &command) override;

private:
    std::shared_ptr<AccountRepository> accountRepository;
    std::shared_ptr<OrderBookRepository> orderBookRepository;
};
