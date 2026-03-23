set(CMAKE_AUTORCC ON)
set(RCC_FILES resources.qrc)   

qt_add_executable(
    breakout
    main.cpp
    breakout.cpp
    ball.cpp
    brick.cpp
    paddle.cpp
    resources.qrc
    )

target_link_libraries(breakout PRIVATE Qt6::Widgets)

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)