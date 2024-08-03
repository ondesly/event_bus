//
//  test_cross.cpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.08.2024.
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

    std::unique_ptr<ev::listener> inner_listener;

    auto listener = ev::bus{}.listen([&values, &inner_listener](const event_t &event) {
        values.push_back(event.value);

        inner_listener =
            ev::bus{}.listen([&values](const event_t &inner_event) { values.push_back(inner_event.value); });

        auto inner_listener2 =
            ev::bus{}.listen([&values](const event_t &inner_event) { values.push_back(inner_event.value + 1); });

        ev::bus{}.dispatch(event_t{event.value + 1});
    });

    ev::bus{}.dispatch(event_t{5});
    ev::bus{}.process();
    ev::bus{}.process();

    assert(values.size() == 3);
    const std::vector<int> reference{5, 6, 6};
    assert(values == reference);

    return 0;
}
