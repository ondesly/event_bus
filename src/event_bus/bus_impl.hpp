//
//  bus_impl.hpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "event_bus/holder.hpp"
#include "event_bus/listener.hpp"
#include "event_bus/types.hpp"

namespace ev {
    class bus_impl {
    public:
        template <class Event>
        std::unique_ptr<listener> listen(std::function<void(const Event &)> &&callback) {
            static_assert(is_event_valid<Event>(), "invalid event");

            const auto listener_id = new_listener_id();
            const auto event_id = get_event_id<Event>();

            m_listeners_to_add.emplace_back(listener_id, event_id, callback);
            ensure_holder<Event>(event_id);

            return std::make_unique<listener>(listener_id, event_id);
        }

        void unlisten(const listener_id_t listener_id, const event_id_t event_id) {
            m_listeners_to_remove.emplace_back(listener_id, event_id);
        }

        template <class Event>
        void dispatch(Event event) {
            static_assert(is_event_valid<Event>(), "invalid event");

            const auto event_id = get_event_id<Event>();
            m_events_to_dispatch.emplace_back(event_id, std::move(event));
        }

        template <class Event>
        void ensure_holder(const event_id_t event_id) {
            if (m_listeners.count(event_id)) {
                return;
            }

            m_listeners.emplace(event_id, std::make_unique<holder<Event>>());
        }

        void process() {
            update_listeners();

            std::vector<std::tuple<event_id_t, std::any>> events_to_dispatch;
            events_to_dispatch.reserve(m_events_to_dispatch.size());
            std::swap(events_to_dispatch, m_events_to_dispatch);

            for (const auto &[event_id, event] : events_to_dispatch) {
                if (const auto &holder = m_listeners[event_id]) {
                    holder->dispacth(event);
                }
            }
        }

    private:
        listener_id_t m_last_listener_id{invalid_listener_id};

        std::unordered_map<event_id_t, std::unique_ptr<holder_i>> m_listeners;

        std::vector<std::tuple<event_id_t, std::any>> m_events_to_dispatch;
        std::vector<std::tuple<listener_id_t, event_id_t, std::any>> m_listeners_to_add;
        std::vector<std::tuple<listener_id_t, event_id_t>> m_listeners_to_remove;

    private:
        listener_id_t new_listener_id() { return ++m_last_listener_id; }

        void update_listeners() {
            if (!m_listeners_to_add.empty()) {
                for (const auto &[listener_id, event_id, callback] : m_listeners_to_add) {
                    const auto &holder = m_listeners[event_id];
                    holder->add_listener(listener_id, callback);
                }
                m_listeners_to_add.clear();
            }
            if (!m_listeners_to_remove.empty()) {
                for (const auto &[listener_id, event_id] : m_listeners_to_remove) {
                    const auto &holder = m_listeners[event_id];
                    holder->remove_listener(listener_id);
                }
                m_listeners_to_remove.clear();
            }
        }
    };

} // namespace ev
