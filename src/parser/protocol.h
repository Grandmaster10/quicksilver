#pragma once
#include <cstdint>

#pragma pack(push, 1)
struct MarketData {
    uint64_t timestamp;
    uint64_t price;          // Decimal price * 100000 to avoid using floating point ALU (eg. 150.05 becomes 15005000)
    uint32_t book;           // Order size
    char symbol[4];         
    char call;              // B = bid, A = ask
    uint8_t exchange_id;
};

#pragma pack(pop)