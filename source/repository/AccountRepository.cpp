#include "../../include/repository/AccountRepository.h"

#include "../../include/event/FundsCredited.h"
#include "../../include/event/FundsDebited.h"
#include "../../include/event/TradeExecuted.h"

void AccountRepository::processEvent(const IDomainEvent &event) {
    event.acceptVisitor(*this);
}

void AccountRepository::visit(const FundsCredited &event) {
    int clientId = event.getUserId();
    if (accounts.find(clientId) == accounts.end()) {
        accounts[clientId] = std::make_shared<AccountAggregate>(clientId);
    }
    accounts[clientId]->addBalance(event.getQuantity());
}

void AccountRepository::visit(const FundsDebited &event) {
    int clientId = event.getUserId();
    double quantity = event.getQuantity();
    if (accounts.find(clientId) == accounts.end() || accounts[clientId]->getBalance() < quantity) {
        throw std::runtime_error("[AccountRepository] Withdrawal failed. Insufficient funds for client " + clientId);
    }
    accounts[clientId]->subtractBalance(quantity);
}

void AccountRepository::visit(const TradeExecuted &event) {
    int buyerId = event.getBuyerId();
    int sellerId = event.getSellerId();
    double totalPrice = event.getQuantity() * event.getPrice();
    if (accounts.find(buyerId) == accounts.end() || accounts[buyerId]->getBalance() < totalPrice) {
        throw std::runtime_error("[AccountRepository] Transaction failed. Insufficient funds for buyer " + buyerId);
    }
    if (accounts.find(sellerId) == accounts.end()) {
        accounts[sellerId] = std::make_shared<AccountAggregate>(sellerId);
    }
    accounts[sellerId]->addBalance(totalPrice);
    accounts[buyerId]->subtractBalance(totalPrice);
}

void AccountRepository::visit(const OrderCancelled &event) {}

void AccountRepository::visit(const OrderPlaced &event) {}

std::shared_ptr<AccountAggregate> AccountRepository::getAggregateByClientId(const int &clientId) {
    if (accounts.find(clientId) == accounts.end()) {
        accounts[clientId] = std::make_shared<AccountAggregate>(clientId);
    }
    return accounts[clientId];
}




