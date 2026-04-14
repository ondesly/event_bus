//
//  test_thread_safe_dispatch.cpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 14.04.2026.
//  Copyright © 2026 Dmitrii Torkhov. All rights reserved.
//

#include <algorithm>
#include <cassert>
#include <thread>
#include <vector>

#include <event_bus/bus.hpp>

int main() {
    struct event_t {
        int value;
    };

    std::vector<int> values;

    auto listener = ev::bus{}.listen([&values](const event_t &event) { values.push_back(event.value); });
    ev::bus{}.process();

    constexpr int thread_count = 4;
    constexpr int events_per_thread = 250;

    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    for (int thread_index = 0; thread_index < thread_count; ++thread_index) {
        threads.emplace_back([thread_index]() {
            for (int event_index = 0; event_index < events_per_thread; ++event_index) {
                ev::bus{}.dispatch_thread_safe(event_t{thread_index * events_per_thread + event_index});
            }
        });
    }

    for (auto &thread : threads) {
        thread.join();
    }

    ev::bus{}.process();
    assert(values.size() == thread_count * events_per_thread);

    return 0;
}
