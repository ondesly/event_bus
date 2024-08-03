//
//  test_preformace.cpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include <dexode/EventBus.hpp>
#include <event_bus/bus.hpp>

namespace {
    namespace constant {
        constexpr size_t listeners_count = 1000;
        constexpr size_t events_count = 1000;
    } // namespace constant
} // namespace

int main() {
    struct simple_event {
        int value;
    };

    long gelldur_duration = 0;
    {
        auto bus = std::make_shared<dexode::EventBus>();

        std::vector<std::unique_ptr<dexode::EventBus::Listener>> listeners;
        listeners.resize(constant::listeners_count);

        size_t sum = 0;
        for (auto &listener : listeners) {
            listener = std::make_unique<dexode::EventBus::Listener>(bus);
            listener->listen([&sum](const simple_event &event) { sum += event.value; });
        }

        const auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < constant::events_count; ++i) {
            bus->postpone(simple_event{1});
            bus->process();
        }

        gelldur_duration =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start)
                .count();

        assert(sum == constant::listeners_count * constant::events_count);
    }

    long duration = 0;
    {
        const auto bus = ev::bus{};

        std::vector<std::unique_ptr<ev::listener>> listeners;
        listeners.resize(constant::listeners_count);

        size_t sum = 0;
        for (auto &listener : listeners) {
            listener = bus.listen([&sum](const simple_event &event) { sum += event.value; });
        }

        const auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < constant::events_count; ++i) {
            bus.dispatch(simple_event{1});
            bus.process();
        }

        duration =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start)
                .count();

        assert(sum == constant::listeners_count * constant::events_count);
    }

    assert(duration * 9 / 10 < gelldur_duration);

    return 0;
}
