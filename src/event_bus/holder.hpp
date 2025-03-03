//
//  caller.hpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <any>
#include <functional>
#include <unordered_map>

#include <event_bus/types.hpp>

namespace ev {
    class holder_i {
    public:
        virtual ~holder_i() = default;
        virtual void add_listener(listener_id_t listener_id, std::any callback) = 0;
        virtual void remove_listener(listener_id_t listener_id) = 0;
        virtual void dispatch(const std::any &event) = 0;
    };

    template <class Event>
    class holder final : public holder_i {
    public:
        using callback_t = std::function<void(const Event &)>;

    public:
        void add_listener(listener_id_t listener_id, std::any callback) override {
            m_listeners.emplace(listener_id, std::any_cast<callback_t>(std::move(callback)));
        }

        void remove_listener(listener_id_t listener_id) override { m_listeners.erase(listener_id); }

        void dispatch(const std::any &any_event) override {
            const auto &event = std::any_cast<Event>(any_event);
            for (const auto &[_, callback] : m_listeners) {
                callback(event);
            }
        }

    private:
        std::unordered_map<listener_id_t, callback_t> m_listeners;
    };
} // namespace ev
