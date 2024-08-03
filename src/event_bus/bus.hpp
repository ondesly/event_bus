//
//  bus.hpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include "event_bus/bus_impl.hpp"

namespace ev {
    class listener;

    class bus {
    public:
        bus() : m_bus(s_bus ? s_bus : (s_bus = std::make_unique<bus_impl>())) {}

    public:
        template <class EventCallback, class Event = callback_argument<EventCallback>>
        std::unique_ptr<listener> listen(EventCallback &&callback) const {
            return m_bus->listen(std::forward<std::function<void(const Event &)>>(callback));
        }

        void unlisten(const listener_id_t listener_id, const event_id_t event_id) const {
            m_bus->unlisten(listener_id, event_id);
        }

        template <class Event>
        void dispatch(Event event) const {
            m_bus->dispatch(std::move(event));
        }

        void process() const { m_bus->process(); }

    private:
        inline static std::shared_ptr<bus_impl> s_bus;
        const std::shared_ptr<bus_impl> m_bus;
    };
} // namespace ev
