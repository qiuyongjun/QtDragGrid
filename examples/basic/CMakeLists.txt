set(YJDRAGGRID_BASIC_EXAMPLE_SOURCES
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    CardWidget.cpp
    CardWidget.h
    CardWidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(YJDragGridDemo
        MANUAL_FINALIZATION
        ${YJDRAGGRID_BASIC_EXAMPLE_SOURCES}
    )
else()
    if(ANDROID)
        add_library(YJDragGridDemo SHARED ${YJDRAGGRID_BASIC_EXAMPLE_SOURCES})
    else()
        add_executable(YJDragGridDemo ${YJDRAGGRID_BASIC_EXAMPLE_SOURCES})
    endif()
endif()

target_link_libraries(YJDragGridDemo PRIVATE YJDragGrid::YJDragGrid Qt${QT_VERSION_MAJOR}::Widgets)

set(QSS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/style.qss")
add_custom_command(TARGET YJDragGridDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${QSS_FILE}" "$<TARGET_FILE_DIR:YJDragGridDemo>/style.qss"
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.YJDragGridDemo)
endif()

set_target_properties(YJDragGridDemo PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(YJDragGridDemo)
endif()

if(YJDRAGGRID_INSTALL AND YJDRAGGRID_INSTALL_EXAMPLES)
    install(TARGETS YJDragGridDemo
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION .
    )

    install(FILES "${QSS_FILE}"
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
