#include <iostream>
#include <thread>
#include <memory>
#include <string_view>
#include <utils/tsc.h>
#include <parser/feed_handler.h>
#include <parser/protocol.h>

int main() {
    auto sq = std::make_unique<SPSCQueue<MarketData, 1024*1024>>();
    
    std::thread network_thread(run_feed_handler, std::ref(*sq));

    MarketData data;
    while(true) {
        if(sq->pop(data)) {
            std::cout << "Symbol: " << std::string_view(data.symbol, 4) << "\nPrice: " << data.price << "\nID: " << data.exchange_id << "\n";
        }
    }

    network_thread.join();
    return 0;
}
