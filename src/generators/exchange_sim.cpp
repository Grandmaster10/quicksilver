#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include "../parser/protocol.h"
#include "../utils/tsc.h"

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    MarketData data{};
    data.price = ((uint64_t)(150.00 * 100000));
    data.book = 100;
    std::memcpy(data.symbol, "AAPL", 4);
    data.call = 'B';
    data.exchange_id = 'B';

    std::cout << "Exchange Simulation\n";

    while (true) {
        data.timestamp = utils::rdtsc();
        sendto(sock, &data, sizeof(MarketData), 0, (sockaddr *)&addr, sizeof(addr));

        data.price += (0.01 * 100000);
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }

    return 0;
}