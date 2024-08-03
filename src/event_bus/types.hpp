//
//  types.hpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>

namespace ev {

    // Listener

    using listener_id_t = size_t;
    constexpr listener_id_t invalid_listener_id = 0;

    // Event

    using event_id_t = uintptr_t;

    template <typename T>
    event_id_t get_event_id() {
        static T *type;
        return reinterpret_cast<event_id_t>(&type);
    }

    // Callback

    template <typename F, typename Event>
    Event callback_argument_helper(void (F::*)(Event) const) {
        return {};
    }

    template <typename F>
    decltype(callback_argument_helper(&F::operator())) callback_argument_helper(F) {
        return;
    }

    template <typename Event>
    using callback_argument = decltype(callback_argument_helper(std::declval<Event>()));
} // namespace ev
