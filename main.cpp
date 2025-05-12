#include <iostream>
#include <memory>

#include "include/command_dispatcher/CommandDispatcher.h"
#include "include/command_handler/CancelOrderCommandHandler.h"
#include "include/command_handler/DepositFundsCommandHandler.h"
#include "include/command_handler/PlaceOrderCommandHandler.h"
#include "include/command_handler/WithdrawFundsCommandHandler.h"
#include "include/event/IDomainEvent.h"
#include "include/event/FundsCredited.h"
#include "include/event_store/FileEventStore.h"
#include "include/input_parser/InputParser.h"
#include "include/repository/AccountRepository.h"
#include "include/repository/OrderBookRepository.h"

int main() {
    ///Rehydration
    auto eventStore = std::make_shared<FileEventStore>("event_log.txt");
    auto orderBookRepository = std::make_shared<OrderBookRepository>();
    auto accountRepository = std::make_shared<AccountRepository>();
    std::vector<std::unique_ptr<IDomainEvent>> events = eventStore->getAllEvents();
    orderBookRepository->rehydrate(events);
    accountRepository->rehydrate(events);

    accountRepository->displayState(std::cout);
    orderBookRepository->displayState(std::cout);

    ///Initialization
    InputParser parser;

    auto cancelOrderCommandHandler = std::make_shared<CancelOrderCommandHandler>(accountRepository, orderBookRepository);
    auto placeOrderCommandHandler = std::make_shared<PlaceOrderCommandHandler>(accountRepository, orderBookRepository);
    auto depositFundsCommandHandler = std::make_shared<DepositFundsCommandHandler>(accountRepository, orderBookRepository);
    auto withdrawFundsCommandHandler = std::make_shared<WithdrawFundsCommandHandler>(accountRepository, orderBookRepository);

    CommandDispatcher commandDispatcher(eventStore);
    commandDispatcher.registerHandler<CancelOrderCommand>(cancelOrderCommandHandler);
    commandDispatcher.registerHandler<PlaceOrderCommand>(placeOrderCommandHandler);
    commandDispatcher.registerHandler<DepositFundsCommand>(depositFundsCommandHandler);
    commandDispatcher.registerHandler<WithdrawFundsCommand>(withdrawFundsCommandHandler);

    ///Application loop
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "stop")
            break;
        try {
            std::unique_ptr<ICommand> command = parser.parseCommand(line);
            commandDispatcher.dispatch(*command);
            std::cout << "[Main] Command executed successfully" << std::endl;
        } catch (std::exception& e) {
            std::cerr << "[Main] Command failed: " << e.what() << std::endl;
        }
    }

    return 0;
}
