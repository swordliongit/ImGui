#pragma once

#include <cstdint>
#include <string_view>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "clock.hpp"

class WindowClass
{
public:
    void Draw(std::string_view label);

private:
    Clock clock;
};

void render(WindowClass &window_class);
