#pragma once

#include "pch.h"

#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

#include "NativeModules.h"

namespace NativeModuleSample
{
    REACT_MODULE(FancyMath);
    struct FancyMath
    {
        REACT_CONSTANT(E, L"E");
        const double E = M_E;

        REACT_CONSTANT(Pi, L"Pi");
        const double Pi = M_PI;

        REACT_METHOD(add, L"add");
        double add(double a, double b) noexcept
        {
            double result = a + b;
            AddEvent(result);
            return result;
        }

        REACT_EVENT(AddEvent);
        std::function<void(double)> AddEvent;
    };
}