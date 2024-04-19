#include <iostream>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "render.hpp"

void WindowClass::Draw(std::string_view label)
{
    constexpr static auto window_flags =
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;

    // Window 1
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(1280.0F, 720.0F));
    ImGui::Begin(label.data(), nullptr, window_flags);

    // Drawers
    DrawMenu();
    ImGui::SameLine();
    DrawContent();
    ImGui::Separator();
    DrawActions();
    DrawFilter();

    ImGui::End();

    // constexpr static auto window_flags =
    //     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
    //     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
    // constexpr static auto window_size = ImVec2(1280.0F, 720.0F);
    // constexpr static auto window_pos = ImVec2(0.0F, 0.0F);

    // ImGui::SetNextWindowSize(window_size);
    // ImGui::SetNextWindowPos(window_pos);

    // ImGui::Begin(label.data(), nullptr, window_flags);

    // ImGui::End();
}

void WindowClass::DrawMenu()
{
    ImGui::Text("DrawMenu");
}

void WindowClass::DrawContent()
{
    ImGui::Text("DrawContent");
}
void WindowClass::DrawActions()
{
    ImGui::Text("DrawActions");
}

void WindowClass::DrawFilter()
{
    ImGui::Text("DrawFilter");
}

void render(WindowClass &window_obj)
{
    window_obj.Draw("Label");
}
