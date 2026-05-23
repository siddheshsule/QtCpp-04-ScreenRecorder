cmake_minimum_required(VERSION 3.19)
project(QtCpp-04-ScreenRecorder LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(QtCpp-04-ScreenRecorder
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(QtCpp-04-ScreenRecorder
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS QtCpp-04-ScreenRecorder
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET QtCpp-04-ScreenRecorder
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
