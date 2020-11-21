#pragma once

#include <iostream>
#include <vector>
#include <memory>

namespace grafik
{
    struct Color
    {
        Color(float r, float g, float b) : r(r), g(g), b(b)
        {
            a = 1;
        }

//        Color(float Hue, float S, float v)
//        {
//            // from Wikipedia HSV->RGB conversion:
//            float h1 = floor(Hue / 60);    // degrees
//            float f = Hue / 60 - h1;

//        }

        float r, g, b, a;
    };
}
