//
//  test_no_listener.cpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#include <event_bus/bus.hpp>

int main() {
    struct event_t {};

    ev::bus{}.dispatch(event_t{});
    ev::bus{}.process();

    ev::bus{}.listen([](const event_t &) {});
    ev::bus{}.process();

    return 0;
}
