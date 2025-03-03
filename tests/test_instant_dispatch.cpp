//
//  test_instant_dispatch.cpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 10.01.2025.
//  Copyright © 2025 Dmitrii Torkhov. All rights reserved.
//

#include <cassert>
#include <iostream>

#include <event_bus/bus.hpp>

int main() {
    std::vector<int> values;

    struct event_t {
        int value;
    };

    auto listener = ev::bus{}.listen([&values](const event_t &event) { values.push_back(event.value); });

    ev::bus{}.process();

    ev::bus{}.dispatch(event_t{5});
    ev::bus{}.dispatch_instantly(event_t{10});

    {
        const std::vector<int> reference{10};
        assert(values == reference);
    }

    ev::bus{}.process();

    {
        const std::vector<int> reference{10, 5};
        assert(values == reference);
    }

    listener.reset();
    ev::bus{}.dispatch_instantly(event_t{15});

    {
        const std::vector<int> reference{10, 5};
        assert(values == reference);
    }

    return 0;
}
