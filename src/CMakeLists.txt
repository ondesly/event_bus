#
#  CMakeLists.txt
#  event_bus
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.08.2024.
#  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
#

add_library(event_bus STATIC
        event_bus/bus.hpp
        event_bus/bus_impl.hpp
        event_bus/holder.hpp
        event_bus/listener.hpp
        event_bus/listener.cpp
        event_bus/types.hpp
)
add_library(ondesly::event_bus ALIAS event_bus)

target_include_directories(event_bus
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

set_target_properties(event_bus PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
