//
//  test_bus.cpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#include <cassert>
#include <iostream>

#include <event_bus/bus.hpp>

int main() {
    std::vector<int> values;

    struct event_t {
        int value;
    };

    auto listener =
        ev::bus{}.listen([&values](const event_t &event) {
            values.push_back(event.value);
        });

    ev::bus{}.dispatch(event_t{5});
    ev::bus{}.process();

    ev::bus{}.dispatch(event_t{6});
    ev::bus{}.process();
    ev::bus{}.process();

    listener = nullptr;

    ev::bus{}.dispatch(event_t{7});
    ev::bus{}.process();

    listener =
        ev::bus{}.listen([&values](const event_t &event) {
            values.push_back(event.value);
        });

    ev::bus{}.dispatch(event_t{8});
    ev::bus{}.process();

    assert(values.size() == 3);
    const std::vector<int> reference{5, 6, 8};
    assert(values == reference);

    return 0;
}
