add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# Add the new advanced_app executable
add_executable(advanced_app advanced_main.cpp)
target_link_libraries(advanced_app PRIVATE ${CMAKE_PROJECT_NAME}_lib)
