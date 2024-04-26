#pragma once

#include <cstdint>
#include <string_view>

#include <filesystem>

namespace fs = std::filesystem;

class WindowClass
{
public:
    WindowClass() : currentPath(fs::current_path()), selectedEntry(fs::path()) {
    }
    void Draw(std::string_view label);

private:
    void DrawMenu();
    void DrawContent();
    void DrawActions();
    void DrawFilter();

    void openFileWithDefaultEditor();
    void renameFilePopUp();
    void deleteFilePopUp();

    fs::path currentPath;
    fs::path selectedEntry;
};


void render(WindowClass& window_obj);
