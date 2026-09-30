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

add_compile_options(-Wall -Wextra -Werror -pedantic)

add_executable(cshell)
target_sources(cshell
    PRIVATE
        src/main.c
)
target_compile_definitions(cshell
    PRIVATE
        CSHELL_VERSION="${PROJECT_VERSION}"
)