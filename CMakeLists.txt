cmake_minimum_required(VERSION 4.4.3)
project(cshell
    VERSION 0.0.1
    SPDX_LICENSE "MIT"
    DESCRIPTION "A custom shell implementation written in c."
    HOMEPAGE_URL "https://github.com/dksifoua/cshell"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Enable testing and build tests" ON)

include(FetchContent)

add_executable(cshell)
target_compile_definitions(cshell PUBLIC CSHELL_VERSION="${PROJECT_VERSION}")
target_compile_options(cshell PRIVATE -Wall -Wextra -Werror -pedantic)
target_link_libraries(cshell PRIVATE cshell_lib)
target_sources(cshell PRIVATE src/main.c)

add_library(cshell_lib)
target_compile_definitions(cshell_lib PUBLIC _POSIX_C_SOURCE=200809L)
target_compile_options(cshell_lib PRIVATE -Wall -Wextra -Werror -pedantic)
target_sources(cshell_lib
    PRIVATE
        src/command.c
        src/utils.c

    PUBLIC
        FILE_SET cshell_headers
        TYPE HEADERS
        BASE_DIRS
            include
        FILES
            include/cshell/command.h
            include/cshell/utils.h
)

if(BUILD_TESTING)
    FetchContent_Declare(cmocka
        GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
        GIT_TAG cmocka-2.0.2
        SYSTEM
    )
    FetchContent_MakeAvailable(cmocka)

    enable_testing()

    add_executable(cshell_test)
    target_compile_options(cshell_test PRIVATE -Wall -Wextra -Werror -pedantic)
    target_sources(cshell_test PRIVATE tests/utils_test.c)
    target_link_libraries(cshell_test PRIVATE cshell_lib cmocka)
    add_test(NAME cshell_test COMMAND cshell_test)
endif()
