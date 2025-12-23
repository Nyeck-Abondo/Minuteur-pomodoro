#pragma once

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <imgui_toggle.h>
#include <imgui_toggle_presets.h>
#include <arc_progress_bar.hpp>
#include <string>

namespace App {
    namespace Uigraphics {
        class windowUi {
            private:
            ImGuiIO* mio;
            ImGuiStyle* mStyle;
            ImFont* Uifont;
            const ImGuiToggleConfig* mtoggleConfig;
            float UiWidth;
            float UiHeight;
            float mfontSize;
            public:
            //constructeur && destructeur
            windowUi (float width, float height, float fontsize);

            //rendu
            void InitializeUi();
            void Uistyle();
            void ParameterUi();
            void LoginUi();
            void ProfileUi();
            void HelpUi();

        };
    } //namespace Uigraphics
} //namespace App