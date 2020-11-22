
project(testApp VERSION 0.1)

add_executable(testApp ${PROJECT_SOURCE_DIR}/src/main.cpp
		${PROJECT_SOURCE_DIR}/src/test.cpp)

#add_library(engine SHARED)
#set_property(TARGET engine PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/build/engine)

target_link_libraries(testApp engine)

target_include_directories(testApp PUBLIC ${CMAKE_SOURCE_DIR}/engine/include)
