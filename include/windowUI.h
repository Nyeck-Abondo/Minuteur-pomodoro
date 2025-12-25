#pragma once

#include "../libs/SDL3/SDL.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/backends/imgui_impl_sdl3.h"
#include "../libs/imgui/backends/imgui_impl_sdlrenderer3.h"
#include "../libs/imgui_toggle/imgui_toggle.h"
#include "../libs/imgui_toggle/imgui_toggle_presets.h"
#include <string>
#include "structs.h"

namespace App {
    namespace Uigraphics {
        class windowUi {
            private:
            ImGuiStyle& mStyle;
            ImFont* Uifont;
            ImGuiToggleConfig mtoggleConfig;
            ImGuiIO& mio;
            backEnd::textureUi mtools;
            float UiWidth;
            float UiHeight;
            float mfontSize;
            bool isInitialise;
            public:
            backEnd::sizeTexture settings, chrono, profile
                                , rest, sound;
            //booleen de l'UI
            bool show_interface = true;
            bool activate_sound = false;
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

            //initialisation
            void InitializeUi(SDL_Renderer* renderer, SDL_Window* window);
            void ShutdownUI();
            //rendu
            void Uistyle();
            void ParameterUi();
            void LoginUi();
            void ProfileUi();
            void HelpUi();
            SDL_Texture* Load_imageTexture(SDL_Renderer* renderer, const char* fileLocation);
            void CreateUITexture(SDL_Renderer* renderer);
        };
    } //namespace Uigraphics
} //namespace App