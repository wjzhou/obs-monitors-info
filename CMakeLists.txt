cmake_minimum_required(VERSION 3.1.0)

project(obs-monitors-info VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Gui REQUIRED)

set(SOURCES
  main.cc
  monitor_name.cc
)

if (WIN32)
  set(SOURCES ${SOURCES} monitor_name_win32.cc)
  # These are copied from obs
  add_definitions(-DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS)
endif()

add_executable(obs-monitors-info ${SOURCES})

target_link_libraries(obs-monitors-info Qt5::Core Qt5::Gui)

if (WIN32)
  #copy the qt dlls
  file(GLOB QT_BIN_FILES
  "${Qt5Core_DIR}/../../../bin/Qt5Core.dll"
  "${Qt5Core_DIR}/../../../bin/Qt5Gui.dll")
  file(GLOB QT_PLAT_BIN_FILES
  "${Qt5Core_DIR}/../../../plugins/platforms/qwindows.dll")

  foreach(BinFile ${QT_BIN_FILES})
    get_filename_component(Directory  ${BinFile} DIRECTORY)
    get_filename_component(Name ${BinFile} NAME_WE)
    get_filename_component(Ext ${BinFile} EXT)

    add_custom_command(TARGET obs-monitors-info POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${Directory}/${Name}$<$<CONFIG:Debug>:d>${Ext}"
      $<TARGET_FILE_DIR:obs-monitors-info>)
  endforeach()

  add_custom_command(TARGET obs-monitors-info POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E make_directory
      "$<TARGET_FILE_DIR:obs-monitors-info>/plugins/platforms")

  foreach(BinFile ${QT_PLAT_BIN_FILES})
    get_filename_component(Directory  ${BinFile} DIRECTORY)
    get_filename_component(Name ${BinFile} NAME_WE)
    get_filename_component(Ext ${BinFile} EXT)

    add_custom_command(TARGET obs-monitors-info POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${Directory}/${Name}$<$<CONFIG:Debug>:d>${Ext}"
      "$<TARGET_FILE_DIR:obs-monitors-info>/plugins/platforms")
  endforeach()
endif()