//
//  listener.cpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#include "event_bus/listener.hpp"
#include "event_bus/bus.hpp"

ev::listener::listener(const listener_id_t id, event_id_t event_id) : m_id(id), m_event_id(event_id) {}

ev::listener::~listener() { bus{}.unlisten(m_id, m_event_id); }
