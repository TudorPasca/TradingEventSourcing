#include <utility>

#include "../../include/command_handler/CancelOrderCommandHandler.h"

#include "../../include/event/OrderCancelled.h"

CancelOrderCommandHandler::CancelOrderCommandHandler(std::shared_ptr<AccountRepository> accountRepository,
                                                     std::shared_ptr<OrderBookRepository> orderBookRepository)
    : accountRepository(accountRepository), orderBookRepository(orderBookRepository) {
}

std::vector<std::shared_ptr<IDomainEvent>>
CancelOrderCommandHandler::handleInternal(const CancelOrderCommand &command) {
    if (command.getQuantity() < 0 || command.getPrice() < 0.0)
        return {};
    std::shared_ptr<OrderBookAggregate> orderBook = orderBookRepository->getAggregate();
    if (command.getType() == Order::BUY) {
        return orderBook->cancelOrder(Order::BuyOrder(command.getUserId(), command.getSymbol(), command.getQuantity(),
                                                      command.getPrice()));
    }
    return orderBook->placeOrder(Order::SellOrder(command.getUserId(), command.getSymbol(), command.getQuantity(),
                                                  command.getPrice()));
}
