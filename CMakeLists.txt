cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(frequencypp
    VERSION 0.1.1
    DESCRIPTION "C++17 type for temporal frequency"
    HOMEPAGE_URL "https://github.com/nokurn/frequencypp"
    LANGUAGES NONE
)

docs_early_return()

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# Require C++17 without extensions.  These variables inform the target
# properties.  By explicitly requiring C++17, rather than simply setting
# the language version with the cxx_std_17 compiler feature, CMake will
# always add the appropriate compiler flag.  This ensures that the flag
# is present in compile_commands.json.  This is important when the
# compiler, such as GCC, defaults to C++17 but the language server, such
# as clangd, does not.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Declare library ----

add_library(frequencypp_frequencypp INTERFACE)
add_library(frequencypp::frequencypp ALIAS frequencypp_frequencypp)

set_property(TARGET frequencypp_frequencypp
    PROPERTY
    EXPORT_NAME frequencypp
)

target_include_directories(frequencypp_frequencypp
    ${frequencypp_warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(frequencypp_frequencypp
    INTERFACE cxx_std_17
)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT frequencypp_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(AUTHOR_WARNING "Developer mode is intended for developers of frequencypp")
endif()

include(cmake/dev-mode.cmake)
