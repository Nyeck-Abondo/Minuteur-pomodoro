#include "../../include/renderUi.h"

namespace App {
    namespace Uigraphics {
        void UiStyleDark() {
            ImGuiStyle& style = ImGui::GetStyle();

            //Definition du style global des fentres
            style.WindowPadding = ImVec2(4.0f, 8.0f);
            style.FramePadding = ImVec2(4.0f, 4.0f);
            style.ItemInnerSpacing = ImVec2(0.0f, 0.0f);
            style.ItemSpacing = ImVec2(8.0f, 2.0f);
            style.IndentSpacing = 16;
            style.GrabMinSize = 20;

            //borders
            style.WindowBorderSize = 1;
            style.ChildBorderSize = 1;
            style.PopupBorderSize = 1;
            style.FrameBorderSize = 0;

            //rounding
            style.WindowRounding = 4;
            style.ChildRounding = 6;
            style.FrameRounding = 4;
            style.PopupRounding = 4;
            style.GrabRounding = 4;

            //windows
            style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
            style.WindowBorderHoverPadding = 4;
            style.WindowMenuButtonPosition = ImGuiDir_Right;

            //position
            style.ColorButtonPosition = ImGuiDir_Right;
            style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            style.SelectableTextAlign = ImVec2(0.5f, 0.5f);
            style.SeparatorTextAlign.x = 1.00f;
            style.SeparatorTextBorderSize = 1;
            style.SeparatorTextPadding = ImVec2(0, 0);

            //minimals
            style.WindowMinSize = ImVec2(50.0f, 60.0f);
            style.ColumnsMinSpacing = 6.0f;

            //definitions des couleurs principales
            const ImVec4 orange  = ImVec4(255.0f/255.0f, 144.0f/255.0f, 000/255.0f, 1.00f);
            const ImVec4 purple  = ImVec4(192.0f/255.0f, 0.0f/255.0f, 255/255.0f, 1.00f);
            const ImVec4 yellow  = ImVec4(240.0f/255.0f, 210.0f/255.0f, 000/255.0f, 1.00f);
            const ImVec4 purple02 = ImVec4(198.0f / 255.0f, 54.0f / 255.0f, 1.0f, 1.0f);

            //definitions des couleurs secondaires
            const ImVec4 black0 = ImVec4(0.04f, 0.05f, 0.07f, 1.00f);
            const ImVec4 black1 = ImVec4(0.08f, 0.09f, 0.11f, 1.00f);
            const ImVec4 black2 = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
            const ImVec4 black3 = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);
            const ImVec4 black4 = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
            const ImVec4 black5 = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);

            //application des couleurs sur l'interface
            style.Colors[ImGuiCol_Text]                      = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled]              = ImVec4(39.0f / 255.0f, 39.0f / 255.0f , 39.0f/255.0f, 1.0f);
            style.Colors[ImGuiCol_WindowBg]                  = black1;
            style.Colors[ImGuiCol_ChildBg]                   = ImVec4(0.09f, 0.10f, 0.12f, 1.00f);
            style.Colors[ImGuiCol_PopupBg]                   = black1;
            style.Colors[ImGuiCol_Border]                    = black4;
            style.Colors[ImGuiCol_BorderShadow]              = black1;
            style.Colors[ImGuiCol_FrameBg]                   = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
            style.Colors[ImGuiCol_FrameBgHovered]            = black4;
            style.Colors[ImGuiCol_FrameBgActive]             = black4;
            style.Colors[ImGuiCol_TitleBg]                   = black0;
            style.Colors[ImGuiCol_TitleBgActive]             = black0;
            style.Colors[ImGuiCol_TitleBgCollapsed]          = black1;
            style.Colors[ImGuiCol_MenuBarBg]                 = black2;
            style.Colors[ImGuiCol_ScrollbarBg]               = black0;
            style.Colors[ImGuiCol_ScrollbarGrab]             = black3;
            style.Colors[ImGuiCol_ScrollbarGrabHovered]      = purple;
            style.Colors[ImGuiCol_ScrollbarGrabActive]       = purple;
            style.Colors[ImGuiCol_CheckMark]                 = purple;
            style.Colors[ImGuiCol_SliderGrab]                = purple;
            style.Colors[ImGuiCol_SliderGrabActive]          = purple;
            style.Colors[ImGuiCol_Button]                    = ImVec4(0.10f, 0.11f, 0.14f, 1.00f);
            style.Colors[ImGuiCol_ButtonHovered]             = purple;
            style.Colors[ImGuiCol_ButtonActive]              = black5;
            style.Colors[ImGuiCol_Header]                    = black3;
            style.Colors[ImGuiCol_HeaderHovered]             = purple;
            style.Colors[ImGuiCol_HeaderActive]              = purple;
            style.Colors[ImGuiCol_Separator]                 = ImVec4(0.13f, 0.15f, 0.19f, 1.00f);
            style.Colors[ImGuiCol_SeparatorHovered]          = purple;
            style.Colors[ImGuiCol_SeparatorActive]           = purple;
            style.Colors[ImGuiCol_ResizeGripHovered]         = purple;
            style.Colors[ImGuiCol_ResizeGripActive]          = purple;
            style.Colors[ImGuiCol_TabHovered]                = black3;
            style.Colors[ImGuiCol_Tab]                       = black1;
            style.Colors[ImGuiCol_TabSelected]               = black3;
            style.Colors[ImGuiCol_TabSelectedOverline]       = purple;
            style.Colors[ImGuiCol_TabDimmed]                 = black1;
            style.Colors[ImGuiCol_TabDimmedSelected]         = black1;
            style.Colors[ImGuiCol_TabDimmedSelectedOverline] = black2;
            style.Colors[ImGuiCol_PlotLines]                 = black5;
            style.Colors[ImGuiCol_PlotLinesHovered]          = black2;
            style.Colors[ImGuiCol_PlotHistogram]             = black5;
            style.Colors[ImGuiCol_PlotHistogramHovered]      = black2;
            style.Colors[ImGuiCol_TextSelectedBg]            = ImVec4(39.0f / 255.0f, 39.0f / 255.0f , 39.0f/255.0f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingHighlight]     = purple;
            style.Colors[ImGuiCol_NavWindowingDimBg]         = ImVec4(0.0f, 0.0f, 0.0f, 63.0/255.0f);
            style.Colors[ImGuiCol_ModalWindowDimBg]          = ImVec4(0.0f, 0.0f, 0.0f, 63.0/255.0f);

        }
        void UiStyleLigth() {
            ImGuiStyle& style = ImGui::GetStyle();

            //Definition du style global des fentres
            style.WindowPadding = ImVec2(4.0f, 8.0f);
            style.FramePadding = ImVec2(4.0f, 4.0f);
            style.ItemInnerSpacing = ImVec2(0.0f, 0.0f);
            style.ItemSpacing = ImVec2(8.0f, 2.0f);
            style.IndentSpacing = 16;
            style.GrabMinSize = 20;

            //borders
            style.WindowBorderSize = 1;
            style.ChildBorderSize = 1;
            style.PopupBorderSize = 1;
            style.FrameBorderSize = 0;

            //rounding
            style.WindowRounding = 4;
            style.ChildRounding = 6;
            style.FrameRounding = 4;
            style.PopupRounding = 4;
            style.GrabRounding = 4;

            //windows
            style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
            style.WindowBorderHoverPadding = 4;
            style.WindowMenuButtonPosition = ImGuiDir_Right;

            //position
            style.ColorButtonPosition = ImGuiDir_Right;
            style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            style.SelectableTextAlign = ImVec2(0.5f, 0.5f);
            style.SeparatorTextAlign.x = 1.00f;
            style.SeparatorTextBorderSize = 1;
            style.SeparatorTextPadding = ImVec2(0, 0);

            //minimals
            style.WindowMinSize = ImVec2(50.0f, 60.0f);
            style.ColumnsMinSpacing = 6.0f;

            //definitions des couleurs principales
            const ImVec4 orange  = ImVec4(255.0f/255.0f, 144.0f/255.0f, 000/255.0f, 1.00f);
            const ImVec4 purple  = ImVec4(192.0f/255.0f, 0.0f/255.0f, 255/255.0f, 1.00f);
            const ImVec4 white  = ImVec4(246.0f/255.0f , 244.0f/255.0f, 240.0f/255.0f, 1.0f);
            const ImVec4 purple02 = ImVec4(198.0f / 255.0f, 54.0f / 255.0f, 1.0f, 1.0f);

            //definitions des couleurs secondaires
            const ImVec4 black0 = ImVec4(0.04f, 0.05f, 0.07f, 1.00f);
            const ImVec4 black1 = ImVec4(0.08f, 0.09f, 0.11f, 1.00f);
            const ImVec4 black2 = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
            const ImVec4 black3 = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);
            const ImVec4 black4 = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
            const ImVec4 black5 = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);

            //application des couleurs sur l'interface
            style.Colors[ImGuiCol_Text]                      = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled]              = ImVec4(39.0f / 255.0f, 39.0f / 255.0f , 39.0f/255.0f, 1.0f);
            style.Colors[ImGuiCol_WindowBg]                  = black1;
            style.Colors[ImGuiCol_ChildBg]                   = ImVec4(0.09f, 0.10f, 0.12f, 1.00f);
            style.Colors[ImGuiCol_PopupBg]                   = black1;
            style.Colors[ImGuiCol_Border]                    = black4;
            style.Colors[ImGuiCol_BorderShadow]              = black1;
            style.Colors[ImGuiCol_FrameBg]                   = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
            style.Colors[ImGuiCol_FrameBgHovered]            = black4;
            style.Colors[ImGuiCol_FrameBgActive]             = black4;
            style.Colors[ImGuiCol_TitleBg]                   = black0;
            style.Colors[ImGuiCol_TitleBgActive]             = black0;
            style.Colors[ImGuiCol_TitleBgCollapsed]          = black1;
            style.Colors[ImGuiCol_MenuBarBg]                 = black2;
            style.Colors[ImGuiCol_ScrollbarBg]               = black0;
            style.Colors[ImGuiCol_ScrollbarGrab]             = black3;
            style.Colors[ImGuiCol_ScrollbarGrabHovered]      = white;
            style.Colors[ImGuiCol_ScrollbarGrabActive]       = white;
            style.Colors[ImGuiCol_CheckMark]                 = white;
            style.Colors[ImGuiCol_SliderGrab]                = white;
            style.Colors[ImGuiCol_SliderGrabActive]          = white;
            style.Colors[ImGuiCol_Button]                    = ImVec4(0.10f, 0.11f, 0.14f, 1.00f);
            style.Colors[ImGuiCol_ButtonHovered]             = white;
            style.Colors[ImGuiCol_ButtonActive]              = black5;
            style.Colors[ImGuiCol_Header]                    = black3;
            style.Colors[ImGuiCol_HeaderHovered]             = white;
            style.Colors[ImGuiCol_HeaderActive]              = white;
            style.Colors[ImGuiCol_Separator]                 = ImVec4(0.13f, 0.15f, 0.19f, 1.00f);
            style.Colors[ImGuiCol_SeparatorHovered]          = white;
            style.Colors[ImGuiCol_SeparatorActive]           = white;
            style.Colors[ImGuiCol_ResizeGripHovered]         = white;
            style.Colors[ImGuiCol_ResizeGripActive]          = white;
            style.Colors[ImGuiCol_TabHovered]                = black3;
            style.Colors[ImGuiCol_Tab]                       = black1;
            style.Colors[ImGuiCol_TabSelected]               = black3;
            style.Colors[ImGuiCol_TabSelectedOverline]       = white;
            style.Colors[ImGuiCol_TabDimmed]                 = black1;
            style.Colors[ImGuiCol_TabDimmedSelected]         = black1;
            style.Colors[ImGuiCol_TabDimmedSelectedOverline] = black2;
            style.Colors[ImGuiCol_PlotLines]                 = black5;
            style.Colors[ImGuiCol_PlotLinesHovered]          = black2;
            style.Colors[ImGuiCol_PlotHistogram]             = black5;
            style.Colors[ImGuiCol_PlotHistogramHovered]      = black2;
            style.Colors[ImGuiCol_TextSelectedBg]            = ImVec4(39.0f / 255.0f, 39.0f / 255.0f , 39.0f/255.0f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingHighlight]     = white;
            style.Colors[ImGuiCol_NavWindowingDimBg]         = ImVec4(0.0f, 0.0f, 0.0f, 63.0/255.0f);
            style.Colors[ImGuiCol_ModalWindowDimBg]          = ImVec4(0.0f, 0.0f, 0.0f, 63.0/255.0f);
        }
        void UiStyleOrange() {
            ImGuiStyle& style = ImGui::GetStyle();

            //Definition du style global des fentres
            style.WindowPadding = ImVec2(4.0f, 8.0f);
            style.FramePadding = ImVec2(4.0f, 4.0f);
            style.ItemInnerSpacing = ImVec2(0.0f, 0.0f);
            style.ItemSpacing = ImVec2(8.0f, 2.0f);
            style.IndentSpacing = 16;
            style.GrabMinSize = 20;

            //borders
            style.WindowBorderSize = 1;
            style.ChildBorderSize = 1;
            style.PopupBorderSize = 1;
            style.FrameBorderSize = 0;

            //rounding
            style.WindowRounding = 4;
            style.ChildRounding = 6;
            style.FrameRounding = 4;
            style.PopupRounding = 4;
            style.GrabRounding = 4;

            //windows
            style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
            style.WindowBorderHoverPadding = 4;
            style.WindowMenuButtonPosition = ImGuiDir_Right;

            //position
            style.ColorButtonPosition = ImGuiDir_Right;
            style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            style.SelectableTextAlign = ImVec2(0.5f, 0.5f);
            style.SeparatorTextAlign.x = 1.00f;
            style.SeparatorTextBorderSize = 1;
            style.SeparatorTextPadding = ImVec2(0, 0);

            //minimals
            style.WindowMinSize = ImVec2(50.0f, 60.0f);
            style.ColumnsMinSpacing = 6.0f;

            //definitions des couleurs principales
            const ImVec4 orange  = ImVec4(241.0f/255.0f, 61.0f/255.0f, 000/255.0f, 1.00f);
            const ImVec4 purple  = ImVec4(192.0f/255.0f, 0.0f/255.0f, 255/255.0f, 1.00f);
            const ImVec4 yellow  = ImVec4(240.0f/255.0f, 210.0f/255.0f, 000/255.0f, 1.00f);
            const ImVec4 purple02 = ImVec4(198.0f / 255.0f, 54.0f / 255.0f, 1.0f, 1.0f);

            //definitions des couleurs secondaires
            const ImVec4 black0 = ImVec4(0.04f, 0.05f, 0.07f, 1.00f);
            const ImVec4 black1 = ImVec4(0.08f, 0.09f, 0.11f, 1.00f);
            const ImVec4 black2 = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
            const ImVec4 black3 = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);
            const ImVec4 black4 = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
            const ImVec4 black5 = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);

            //application des couleurs sur l'interface
            style.Colors[ImGuiCol_Text]                      = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled]              = ImVec4(39.0f / 255.0f, 39.0f / 255.0f , 39.0f/255.0f, 1.0f);
            style.Colors[ImGuiCol_WindowBg]                  = black1;
            style.Colors[ImGuiCol_ChildBg]                   = ImVec4(0.09f, 0.10f, 0.12f, 1.00f);
            style.Colors[ImGuiCol_PopupBg]                   = black1;
            style.Colors[ImGuiCol_Border]                    = black4;
            style.Colors[ImGuiCol_BorderShadow]              = black1;
            style.Colors[ImGuiCol_FrameBg]                   = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
            style.Colors[ImGuiCol_FrameBgHovered]            = black4;
            style.Colors[ImGuiCol_FrameBgActive]             = black4;
            style.Colors[ImGuiCol_TitleBg]                   = black0;
            style.Colors[ImGuiCol_TitleBgActive]             = black0;
            style.Colors[ImGuiCol_TitleBgCollapsed]          = black1;
            style.Colors[ImGuiCol_MenuBarBg]                 = black2;
            style.Colors[ImGuiCol_ScrollbarBg]               = black0;
            style.Colors[ImGuiCol_ScrollbarGrab]             = black3;
            style.Colors[ImGuiCol_ScrollbarGrabHovered]      = orange;
            style.Colors[ImGuiCol_ScrollbarGrabActive]       = orange;
            style.Colors[ImGuiCol_CheckMark]                 = orange;
            style.Colors[ImGuiCol_SliderGrab]                = orange;
            style.Colors[ImGuiCol_SliderGrabActive]          = orange;
            style.Colors[ImGuiCol_Button]                    = ImVec4(0.10f, 0.11f, 0.14f, 1.00f);
            style.Colors[ImGuiCol_ButtonHovered]             = orange;
            style.Colors[ImGuiCol_ButtonActive]              = black5;
            style.Colors[ImGuiCol_Header]                    = black3;
            style.Colors[ImGuiCol_HeaderHovered]             = orange;
            style.Colors[ImGuiCol_HeaderActive]              = orange;
            style.Colors[ImGuiCol_Separator]                 = ImVec4(0.13f, 0.15f, 0.19f, 1.00f);
            style.Colors[ImGuiCol_SeparatorHovered]          = orange;
            style.Colors[ImGuiCol_SeparatorActive]           = orange;
            style.Colors[ImGuiCol_ResizeGripHovered]         = orange;
            style.Colors[ImGuiCol_ResizeGripActive]          = orange;
            style.Colors[ImGuiCol_TabHovered]                = black3;
            style.Colors[ImGuiCol_Tab]                       = black1;
            style.Colors[ImGuiCol_TabSelected]               = black3;
            style.Colors[ImGuiCol_TabSelectedOverline]       = orange;
            style.Colors[ImGuiCol_TabDimmed]                 = black1;
            style.Colors[ImGuiCol_TabDimmedSelected]         = black1;
            style.Colors[ImGuiCol_TabDimmedSelectedOverline] = black2;
            style.Colors[ImGuiCol_PlotLines]                 = black5;
            style.Colors[ImGuiCol_PlotLinesHovered]          = black2;
            style.Colors[ImGuiCol_PlotHistogram]             = black5;
            style.Colors[ImGuiCol_PlotHistogramHovered]      = black2;
            style.Colors[ImGuiCol_TextSelectedBg]            = ImVec4(39.0f / 255.0f, 39.0f / 255.0f , 39.0f/255.0f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingHighlight]     = orange;
            style.Colors[ImGuiCol_NavWindowingDimBg]         = ImVec4(0.0f, 0.0f, 0.0f, 63.0/255.0f);
            style.Colors[ImGuiCol_ModalWindowDimBg]          = ImVec4(0.0f, 0.0f, 0.0f, 63.0/255.0f);
        }
    } // namespace name
    
} // namespace App