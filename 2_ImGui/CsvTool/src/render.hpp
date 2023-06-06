#pragma once

#include <string_view>
#include <vector>

#include <imgui.h>
#include <implot.h>

class WindowClass
{
public:
    constexpr static auto popUpFlags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
    constexpr static auto popUpSize = ImVec2(300.0F, 100.0F);

public:
    void Draw(std::string_view label);

private:
    void DrawSizeButtons();
    void DrawIoButtons();
    void DrawTable();

    void DrawSavePopup();
    void DrawLoadPopup();
    void DrawValuePopup(const int row_clicked, const int col_clicked);

    void SaveToFile(std::string_view filename);
    void LoadFromFile(std::string_view filename);

    template <typename T>
    void PlotCellValue(std::string_view formatter, const T value);
    void SetPopupLayout();

private:
    std::int32_t numCols = 0;
    std::int32_t numRows = 0;
    std::vector<std::vector<float>> data;
    char filenameBuffer[512] = "test.csv";
};

void render(WindowClass &window_obj);
