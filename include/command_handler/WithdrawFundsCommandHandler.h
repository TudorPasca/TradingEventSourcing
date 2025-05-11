#pragma once
#include "ICommandHandler.h"
#include "../command/WithdrawFundsCommand.h"
#include "../repository/AccountRepository.h"
#include "../repository/OrderBookRepository.h"

class WithdrawFundsCommandHandler : public ICommandHandler<WithdrawFundsCommand> {
public:
    WithdrawFundsCommandHandler(std::shared_ptr<AccountRepository> accountRepository,
                                std::shared_ptr<OrderBookRepository> orderBookRepository);

protected:
    std::vector<std::shared_ptr<IDomainEvent> > handleInternal(const WithdrawFundsCommand &command) override;

private:
    std::shared_ptr<AccountRepository> accountRepository;
    std::shared_ptr<OrderBookRepository> orderBookRepository;
};
