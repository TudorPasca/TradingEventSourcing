#include "../../include/command_handler/DepositFundsCommandHandler.h"

DepositFundsCommandHandler::DepositFundsCommandHandler(std::shared_ptr<AccountRepository> accountRepository,
                                                       std::shared_ptr<OrderBookRepository> orderBookRepository)
    : accountRepository(accountRepository), orderBookRepository(orderBookRepository) {
}

std::vector<std::shared_ptr<IDomainEvent> > DepositFundsCommandHandler::handleInternal(const DepositFundsCommand &command) {
    if (command.getQuantity() < 0.0)
        return {};
    std::shared_ptr<AccountAggregate> account = accountRepository->getAggregateByClientId(command.getUserId());
    return account->addBalance(command.getQuantity());
}
