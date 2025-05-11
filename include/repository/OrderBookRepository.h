#pragma once

#include "IRepository.h"
#include "../aggregate/OrderBookAggregate.h"

class OrderBookRepository : public IRepository, public IEventVisitor {
public:
    void processEvent(const IDomainEvent &event) override;

    void visit(const FundsCredited &event) override;

    void visit(const FundsDebited &event) override;

    void visit(const OrderPlaced &event) override;

    void visit(const OrderCancelled &event) override;

    void visit(const TradeExecuted &event) override;

private:
    OrderBookAggregate orderBook;
};
