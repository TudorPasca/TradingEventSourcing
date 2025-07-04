cmake_minimum_required(VERSION 3.30)
project(TradingEventSourcing)

set(CMAKE_CXX_STANDARD 20)

add_executable(TradingEventSourcing main.cpp
        source/event/IDomainEvent.cpp
        source/event/FundsCredited.cpp
        source/event/FundsDebited.cpp
        source/event/OrderCancelled.cpp
        source/event/OrderPlaced.cpp
        source/event/TradeExecuted.cpp
        source/event_store/FileEventStore.cpp
        source/command/WithdrawFundsCommand.cpp
        source/command/PlaceOrderCommand.cpp
        source/command/CancelOrderCommand.cpp
        source/command/DepositFundsCommand.cpp
        source/input_parser/InputParser.cpp
)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(TradingEventSourcing PRIVATE nlohmann_json::nlohmann_json)