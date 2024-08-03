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
