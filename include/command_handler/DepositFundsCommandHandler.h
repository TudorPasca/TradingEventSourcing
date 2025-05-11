#pragma once
#include "ICommandHandler.h"
#include "../command/DepositFundsCommand.h"
#include "../repository/AccountRepository.h"
#include "../repository/OrderBookRepository.h"

struct DepositFundsCommandHandler : public ICommandHandler<DepositFundsCommand> {
public:
    DepositFundsCommandHandler(std::shared_ptr<AccountRepository> accountRepository,
                               std::shared_ptr<OrderBookRepository> orderBookRepository);

protected:
    std::vector<std::shared_ptr<IDomainEvent> > handleInternal(const DepositFundsCommand &command) override;

private:
    std::shared_ptr<AccountRepository> accountRepository;
    std::shared_ptr<OrderBookRepository> orderBookRepository;
};
