#include <cstddef>
#include <filesystem>
#include <iostream>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "render.hpp"

void WindowClass::Draw(std::string_view label) {
    constexpr static auto window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                         ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;

    // Window 1
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(1280.0F, 720.0F));
    ImGui::Begin(label.data(), nullptr, window_flags);

    // Drawers
    DrawMenu();
    ImGui::Separator();
    DrawContent();
    ImGui::Separator();
    DrawActions();
    ImGui::Separator();
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

void WindowClass::DrawMenu() {
    if (ImGui::Button("Go Up")) {
        if (currentPath.has_parent_path()) {
            currentPath = currentPath.parent_path();
        }
    }

    ImGui::SameLine();
    ImGui::Text("Current Directory: %s", currentPath.string().c_str());
}

void WindowClass::DrawContent() {
    for (const auto& entry : fs::directory_iterator(currentPath)) {
        const auto is_selected = entry.path() == selectedEntry;
        const auto is_directory = entry.is_directory();
        const auto is_file = entry.is_regular_file();

        auto entry_name = entry.path().filename().string();
        if (is_directory)
            entry_name = "[D]" + entry_name;
        else if (is_file)
            entry_name = "[F]" + entry_name;
        // if entry is selected, selectedEntry will be set to entry.path(),
        // thus making is_selected variable true in the next iteration/frame,
        // making the label highlighted
        if (ImGui::Selectable(entry_name.c_str(), is_selected)) {
            if (is_directory)
                currentPath /= entry.path().filename();

            selectedEntry = entry.path();
        }
    }
}
void WindowClass::DrawActions() {
    if (fs::is_directory(selectedEntry))
        ImGui::Text("Selected dir: %s", selectedEntry.string().c_str());
    else if (fs::is_regular_file(selectedEntry))
        ImGui::Text("Selected file: %s", selectedEntry.string().c_str());
    else
        ImGui::Text("Nothing selected");

    if (fs::is_regular_file(selectedEntry) && ImGui::Button("Open"))
        openFileWithDefaultEditor();

    ImGui::SameLine();

    if (ImGui::Button("Rename"))
        ImGui::OpenPopup("Rename File");

    ImGui::SameLine();

    if (ImGui::Button("Delete"))
        ImGui::OpenPopup("Delete File");

    renameFilePopUp();
    deleteFilePopUp();
}

void WindowClass::DrawFilter() {
    static char extension_filter[16] = {'\0'};
    ImGui::Text("Filter by Extension");
    ImGui::SameLine();
    // ### makes it a hidden label
    ImGui::InputText("###inFilter", extension_filter, sizeof(extension_filter));

    if (std::strlen(extension_filter) == 0)
        return;

    auto filtered_file_count = std::size_t{0};
    for (const auto& entry : fs::directory_iterator(currentPath)) {
        if (!fs::is_regular_file(entry)) {
            continue;
        }
        if (entry.path().extension().string() == extension_filter)
            ++filtered_file_count;
    }

    ImGui::Text("Number of files: %zu", filtered_file_count);
}

void WindowClass::renameFilePopUp() {
    if (ImGui::BeginPopupModal("Rename File")) {
        static char buffer_name[512] = {'\0'};
        ImGui::Text("New Name: ");
        ImGui::InputText("###newName", buffer_name, sizeof(buffer_name));
        ImGui::EndPopup();
    }
}

void WindowClass::deleteFilePopUp() {
    if (ImGui::BeginPopupModal("Rename File")) {
        ImGui::EndPopup();
    }
}

void WindowClass::openFileWithDefaultEditor() {
    ;
}


void render(WindowClass& window_obj) {
    window_obj.Draw("Label");
}
