cmake_minimum_required(VERSION 3.16)

project(YJDragGrid VERSION 0.3.0 LANGUAGES CXX)

set(YJDRAGGRID_IS_TOP_LEVEL OFF)
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(YJDRAGGRID_IS_TOP_LEVEL ON)
endif()

set(YJDRAGGRID_DEFAULT_BUILD_EXAMPLES ${YJDRAGGRID_IS_TOP_LEVEL})
if(DEFINED ENV{CI})
    set(YJDRAGGRID_DEFAULT_BUILD_EXAMPLES OFF)
endif()

set(YJDRAGGRID_BUILD_EXAMPLES_WAS_DEFINED OFF)
if(DEFINED YJDRAGGRID_BUILD_EXAMPLES)
    set(YJDRAGGRID_BUILD_EXAMPLES_WAS_DEFINED ON)
endif()
set(YJDRAGGRID_BUILD_DEMO_WAS_DEFINED OFF)
if(DEFINED YJDRAGGRID_BUILD_DEMO)
    set(YJDRAGGRID_BUILD_DEMO_WAS_DEFINED ON)
endif()

option(YJDRAGGRID_BUILD_SHARED "Build YJDragGrid as a shared library" OFF)
option(YJDRAGGRID_BUILD_EXAMPLES "Build YJDragGrid example applications" ${YJDRAGGRID_DEFAULT_BUILD_EXAMPLES})
option(YJDRAGGRID_BUILD_DEMO "Compatibility alias for YJDRAGGRID_BUILD_EXAMPLES" ${YJDRAGGRID_BUILD_EXAMPLES})
option(YJDRAGGRID_BUILD_TESTS "Build YJDragGrid tests" ${YJDRAGGRID_IS_TOP_LEVEL})
option(YJDRAGGRID_INSTALL "Install YJDragGrid targets and headers" ON)
option(YJDRAGGRID_INSTALL_EXAMPLES "Install YJDragGrid example applications" OFF)

# Prefer the new option when both switches exist so stale demo cache cannot reopen examples.
set(YJDRAGGRID_ENABLE_EXAMPLES ${YJDRAGGRID_BUILD_EXAMPLES})
if(YJDRAGGRID_BUILD_EXAMPLES_WAS_DEFINED)
    set(YJDRAGGRID_ENABLE_EXAMPLES ${YJDRAGGRID_BUILD_EXAMPLES})
elseif(YJDRAGGRID_BUILD_DEMO_WAS_DEFINED)
    set(YJDRAGGRID_ENABLE_EXAMPLES ${YJDRAGGRID_BUILD_DEMO})
endif()
set(YJDRAGGRID_BUILD_EXAMPLES ${YJDRAGGRID_ENABLE_EXAMPLES} CACHE BOOL "Build YJDragGrid example applications" FORCE)
set(YJDRAGGRID_BUILD_DEMO ${YJDRAGGRID_ENABLE_EXAMPLES} CACHE BOOL "Compatibility alias for YJDRAGGRID_BUILD_EXAMPLES" FORCE)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(YJDRAGGRID_BUILD_TESTS)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)
endif()

set(YJDRAGGRID_LIBRARY_TYPE STATIC)
if(YJDRAGGRID_BUILD_SHARED)
    set(YJDRAGGRID_LIBRARY_TYPE SHARED)
endif()

set(YJDRAGGRID_PUBLIC_HEADERS
    include/YJDragGrid/YJDragGridGlobal.h
    include/YJDragGrid/DragGridLayout.h
    include/YJDragGrid/DragGridWidget.h
)

set(YJDRAGGRID_COMPAT_HEADERS
    include/DragGridLayout.h
    include/DragGridWidget.h
)

set(YJDRAGGRID_SOURCES
    src/DragGridLayout.cpp
    src/DragGridWidget.cpp
)

add_library(YJDragGrid ${YJDRAGGRID_LIBRARY_TYPE}
    ${YJDRAGGRID_PUBLIC_HEADERS}
    ${YJDRAGGRID_COMPAT_HEADERS}
    ${YJDRAGGRID_SOURCES}
)

add_library(YJDragGrid::YJDragGrid ALIAS YJDragGrid)
add_library(DragGrid ALIAS YJDragGrid)

target_compile_features(YJDragGrid PUBLIC cxx_std_17)
target_include_directories(YJDragGrid
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(YJDragGrid PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_compile_definitions(YJDragGrid PRIVATE YJDRAGGRID_LIBRARY)
if(NOT YJDRAGGRID_BUILD_SHARED)
    target_compile_definitions(YJDragGrid PUBLIC YJDRAGGRID_STATIC)
endif()

set_target_properties(YJDragGrid PROPERTIES
    OUTPUT_NAME YJDragGrid
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME YJDragGrid
)

if(YJDRAGGRID_ENABLE_EXAMPLES)
    add_subdirectory(examples/basic)
endif()

if(YJDRAGGRID_BUILD_TESTS)
    enable_testing()

    set(TEST_FILES
        tests/TestDragGridLayout.cpp
        tests/TestDragGridWidget.cpp
    )

    foreach(test_file ${TEST_FILES})
        get_filename_component(test_name ${test_file} NAME_WE)
        add_executable(${test_name} ${test_file})
        target_link_libraries(${test_name} PRIVATE YJDragGrid::YJDragGrid Qt${QT_VERSION_MAJOR}::Test)
        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()
endif()

if(YJDRAGGRID_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    install(TARGETS YJDragGrid
        EXPORT YJDragGridTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    install(DIRECTORY include/YJDragGrid
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
    )

    install(FILES ${YJDRAGGRID_COMPAT_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(EXPORT YJDragGridTargets
        FILE YJDragGridTargets.cmake
        NAMESPACE YJDragGrid::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/YJDragGrid
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/YJDragGridConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/YJDragGridConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/YJDragGrid
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/YJDragGridConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/YJDragGridConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/YJDragGridConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/YJDragGrid
    )
endif()
