#pragma once

#include "IRepository.h"
#include "../aggregate/OrderBookAggregate.h"

class OrderBookRepository : public IRepository, public IEventVisitor {
public:
    OrderBookRepository();

    void processEvent(const IDomainEvent &event) override;

    void visit(const FundsCredited &event) override;

    void visit(const FundsDebited &event) override;

    void visit(const OrderPlaced &event) override;

    void visit(const OrderCancelled &event) override;

    void visit(const TradeExecuted &event) override;

    std::shared_ptr<OrderBookAggregate> getAggregate();

    void displayState(std::ostream &stream) const override;
private:
    std::shared_ptr<OrderBookAggregate> orderBook;
};
