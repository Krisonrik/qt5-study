cmake_minimum_required(VERSION 3.9)

project(SaveStream_Design_Test)

if(MSVC)
  set(DISABLE "__pragma(warning(push,0))")
  set(ENABLE "__pragma(warning(pop))")
endif()


set(PROJECT_SRCS
${PROJECT_SOURCE_DIR}/src/SaveStream_Design_Test.cpp
)

set(PROJECT_RCC
${PROJECT_SOURCE_DIR}/resource/savestream.qrc
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5Widgets REQUIRED)

source_group("src" FILES ${PROJECT_SRCS})
source_group("resource"     FILES ${PROJECT_RCC})

add_executable(${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_RCC})

target_compile_definitions(${PROJECT_NAME} PUBLIC
                          HVR_WINDOWS_DISABLE_ALL_WARNING=${DISABLE}
                          HVR_WINDOWS_ENABLE_ALL_WARNING=${ENABLE})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets SaveStream_UI)
# target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${CMAKE_PROJECT_NAME}/apps)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        DESTINATION bin COMPONENT install-app)
