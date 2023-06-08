#pragma once

#include <numbers>
#include <string_view>
#include <tuple>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

class WindowClass
{
public:
    constexpr static auto PI = std::numbers::pi_v<float>;
    constexpr static auto circleRadius = 250.0F;
    constexpr static auto offset = PI / 2.0F;
    constexpr static auto innerRadius = 5.0F;
    constexpr static auto hrsClockHandLength = 0.95F;
    constexpr static auto minsClockHandLength = 0.85F;
    constexpr static auto secsClockHandLength = 0.75F;
    constexpr static auto hrsStrokesLength = 0.90F;
    constexpr static auto minsStrokesLength = 0.95F;

public:
    WindowClass() : secs(0), mins(0), hrs(0), center({}){};
    void Draw(std::string_view label);

private:
    void DrawCircle(const float radius);
    void DrawClockHand(const float radius,
                       const float theta,
                       const ImColor color);
    void DrawAllHourStrokes();
    void DrawAllMinuteStrokes();
    void DrawDigitalClock();

    void GetTime();
    std::tuple<float, float, float> GetTheta();

public:
    std::int32_t secs;
    std::int32_t mins;
    std::int32_t hrs;

private:
    ImVec2 center;
};

void render(WindowClass &window_obj);
