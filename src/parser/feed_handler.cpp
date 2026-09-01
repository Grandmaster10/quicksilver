#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <parser/protocol.h>
#include "../utils/socket_utils.h"
#include "../utils/tsc.h"
#include "../scq/spsc_queue.h"

void run_feed_handler(SPSCQueue<MarketData, 1024*1024>& sq) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (sockaddr *)&addr, sizeof(addr));
    utils::non_blocking(sock);

    std::cout << "Feed Handler\n";
    alignas(64) char buffer[1024];
    while(true) {
        ssize_t read = recv(sock, buffer, sizeof(buffer), 0);

        if(read == sizeof(MarketData)) {
            auto* data = reinterpret_cast<MarketData *>(buffer);

            while(!sq.push(*data));
        }
    }
}