project(testEngine VERSION 0.1)

# get all source files in the source directory
file( GLOB_RECURSE  engineSRCS ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/third_party/*.cpp )

add_library(engine SHARED ${engineSRCS})

# required packages
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)


target_link_libraries(engine PRIVATE glm)
target_link_libraries(engine PUBLIC glfw)

# Link libraries on Linux and on Windows with a vcpkg installation
if (MSVC)
    target_link_libraries(engine PRIVATE GLEW::GLEW)
    
    target_compile_definitions(engine PRIVATE _BUILD_DLL=1)  # set the BUID_DLL define for dll export/import

    # post build step: copy the dll
    add_custom_command(TARGET engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:engine> ${CMAKE_SOURCE_DIR}/out/build/x64-Debug/app)
else (MSVC)
    target_link_libraries(engine PRIVATE GLEW)
    target_link_libraries(engine PRIVATE ${OPENGL_LIBRARIES})
    
    target_include_directories(engine PRIVATE ${OPENGL_INCLUDE_DIRS})
    
endif (MSVC)


target_include_directories(engine PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}
    )
