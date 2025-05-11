#include "../../include/command_handler/WithdrawFundsCommandHandler.h"

#include "../../include/event/FundsDebited.h"

WithdrawFundsCommandHandler::WithdrawFundsCommandHandler(std::shared_ptr<AccountRepository> accountRepository,
                                                         std::shared_ptr<OrderBookRepository> orderBookRepository)
    : accountRepository(accountRepository), orderBookRepository(orderBookRepository) {
}

std::vector<std::shared_ptr<IDomainEvent> > WithdrawFundsCommandHandler::handleInternal(const WithdrawFundsCommand &command) {
    if (command.getQuantity() < 0.0)
        return {};
    std::shared_ptr<AccountAggregate> account = accountRepository->getAggregateByClientId(command.getUserId());
    return account->subtractBalance(command.getQuantity());
}
