project(testEngine VERSION 0.1)

# get all source files in the source directory
file( GLOB_RECURSE  engineSRCS ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/third_party/*.cpp )

add_library(engine SHARED ${engineSRCS})

# required packages
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(engine PRIVATE glm)

# Link libraries on Linux and on Windows with a vcpkg installation
if (MSVC)
    target_link_libraries(engine PRIVATE GLEW::GLEW)
    #target_link_libraries(engine PRIVATE SDL2::SDL2 SDL2::SDL2main)

else (MSVC)
    target_link_libraries(engine PRIVATE GLEW)

    target_link_libraries(engine PRIVATE ${OPENGL_LIBRARIES})
    target_include_directories(engine PRIVATE /usr/include/SDL2)
    target_include_directories(engine PRIVATE ${OPENGL_INCLUDE_DIRS})
endif (MSVC)

target_link_libraries(engine PRIVATE glfw)

target_include_directories(engine PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}
    )
