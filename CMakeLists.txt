#
#  CMakeLists.txt
#  event_bus
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.08.2024.
#  Copyright © 2024 Dmitrii Torkhov. All rights reserved.
#

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(event_bus
        VERSION 0.1.0
        LANGUAGES CXX)

#########
# Build #
#########

add_subdirectory(src)

###########
# Testing #
###########

enable_testing()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif ()
