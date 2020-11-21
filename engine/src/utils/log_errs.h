#pragma once

#include <iostream>

void error_callback(int code, const char* description)
{
    std::cout << "glfw error. code: " << code << description << std::endl;
}
