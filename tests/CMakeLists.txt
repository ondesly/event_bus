#
#  CMakeLists.txt
#  event_bus
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.08.2024.
#  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
#

project(tests)

#

function(add name)
    add_executable(${name} ${name}.cpp)

    target_link_libraries(${name} ondesly::event_bus)

    set_target_properties(${name} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

    add_test(NAME ${name} COMMAND ${name})
endfunction()

#

add("test_bus")
add("test_inner")
add("test_no_listener")
add("test_instant_dispatch")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    include(FetchContent)
    FetchContent_Declare(
            event_bus
            GIT_REPOSITORY https://github.com/gelldur/EventBus.git
            GIT_TAG v3.1.2
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE)

    FetchContent_MakeAvailable(event_bus)

    add("test_performance")
    target_link_libraries(test_performance EventBus)
endif ()
