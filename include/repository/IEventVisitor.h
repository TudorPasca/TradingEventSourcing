#pragma once

class OrderPlaced;
class OrderCancelled;
class TradeExecuted;
class FundsCredited;
class FundsDebited;

struct IEventVisitor {
    virtual ~IEventVisitor() = default;

    virtual void visit(const FundsCredited &event) = 0;
    virtual void visit(const FundsDebited &event) = 0;
    virtual void visit(const OrderPlaced &event) = 0;
    virtual void visit(const OrderCancelled &event) = 0;
    virtual void visit(const TradeExecuted &event) = 0;
};
