#pragma once
#include "protocol.h"
#include "../scq/spsc_queue.h"

void run_feed_handler(SPSCQueue<MarketData, 1024*1024>& sq);