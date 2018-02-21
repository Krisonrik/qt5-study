cmake_minimum_required(VERSION 3.9)

project(SaveStream_UI)

if(MSVC)
  set(DLLIMPORT "__declspec(dllimport)")
  set(DLLEXPORT "__declspec(dllexport)")
  set(DISABLE "__pragma(warning(push,0))")
  set(ENABLE "__pragma(warning(pop))")
endif()

set(PROJECT_SRCS
${PROJECT_SOURCE_DIR}/src/MainWindow.cpp
${PROJECT_SOURCE_DIR}/src/StatusPanel.cpp
)

set(PROJECT_INCS
${PROJECT_SOURCE_DIR}/include/Hvr/SaveStream_UI/MainWindow.h
${PROJECT_SOURCE_DIR}/include/Hvr/SaveStream_UI/StatusPanel.h
)

# set(PROJECT_RCC
# ${PROJECT_SOURCE_DIR}/resource/dockwidgets.qrc
# )

source_group("include" FILES ${PROJECT_INCS})
source_group("src"     FILES ${PROJECT_SRCS})
# source_group("resource"     FILES ${PROJECT_RCC})


set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
# find_package(Qt5PrintSupport REQUIRED)


add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS} ${PROJECT_INCS}) 

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

target_compile_definitions(${PROJECT_NAME} PUBLIC
                          HVR_WINDOWS_DISABLE_ALL_WARNING=${DISABLE}
                          HVR_WINDOWS_ENABLE_ALL_WARNING=${ENABLE})

target_compile_definitions(${PROJECT_NAME} INTERFACE
                          SAVESTREAM_WIDGETS_DLL=${DLLIMPORT})

target_compile_definitions(${PROJECT_NAME} PRIVATE
                          SAVESTREAM_WIDGETS_DLL=${DLLEXPORT})

target_compile_definitions(${PROJECT_NAME} PRIVATE
                          # QT_PRINTSUPPORT_LIB
                          )

target_include_directories(${PROJECT_NAME} PUBLIC
                          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

# target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

set_property(TARGET ${PROJECT_NAME} PROPERTY
            FOLDER ${CMAKE_PROJECT_NAME}/modules)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib COMPONENT install-app
        LIBRARY DESTINATION lib COMPONENT install-app
        RUNTIME DESTINATION bin COMPONENT install-app)

install(FILES ${PROJECT_SOURCE_DIR}/include/Hvr/Sample/Sample.h
        DESTINATION include/Hvr/Sample)

export(TARGETS ${PROJECT_NAME}
      APPEND FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Targets.cmake)

file(APPEND ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
    "find_dependency(OpenCV REQUIRED)\n")
