//
//  listener.hpp
//  event_bus
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.08.2024.
//  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <event_bus/types.hpp>

namespace ev {

    class listener {
    public:
        listener(listener_id_t id, event_id_t event_id);
        ~listener();

    private:
        const listener_id_t m_id;
        const event_id_t m_event_id;
    };

} // namespace event_bus
