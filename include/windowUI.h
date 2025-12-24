#pragma once

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include "../libs/imgui_toggle/imgui_toggle.h"
#include <../libs/imgui_toggle/imgui_toggle_presets.h>
#include <string>

namespace App {
    namespace Uigraphics {
        class windowUi {
            private:
            ImGuiStyle& mStyle;
            ImFont* Uifont;
            ImGuiToggleConfig mtoggleConfig;
            ImGuiIO& mio;
            float UiWidth;
            float UiHeight;
            float mfontSize;
            bool isInitialise;
            public:
            //booleen de l'UI
            bool show_interface = true;
            bool sound = false;
            bool show_stats = false;
            bool show_profile = true;
            bool show_parameters = false;
            bool next_session = false;
            bool getStarted = false;
            bool helper = false;
            bool show_demo = true;
            //constructeur && destructeur
            windowUi (float width, float height, float fontsize, ImGuiIO& io);
            ~windowUi();

            //GETTERS
            
            ImGuiStyle GetUIstyle() const { return mStyle;}
            ImFont* GetFontUi() const { return Uifont;}
            ImGuiToggleConfig GetToggleConfig() const { return mtoggleConfig;}
            float GetUIwidth() const { return UiWidth; }
            float GetUIheight() const { return UiHeight; }
            float GetFontSize() const { return mfontSize; }
            bool GetInitialisation() const { return isInitialise; }

            //rendu
            void InitializeUi(SDL_Renderer* renderer, SDL_Window* window);
            void Uistyle();
            void ParameterUi();
            void LoginUi();
            void ProfileUi();
            void HelpUi();

        };
    } //namespace Uigraphics
} //namespace App