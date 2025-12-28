#pragma once

#include "../libs/SDL3/SDL.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/backends/imgui_impl_sdl3.h"
#include "../libs/imgui/backends/imgui_impl_sdlrenderer3.h"
#include "../libs/imgui_toggle/imgui_toggle.h"
#include "../libs/imgui_toggle/imgui_toggle_presets.h"
#include <string>
#include <iostream>
#include "structs.h"

namespace App {
    namespace Uigraphics {
        class windowUi {
            private:
            //window configuration
            ImGuiStyle& mStyle;
            ImFont* Uifont;
            ImGuiToggleConfig mtoggleConfig;
            ImGuiIO& mio;
            backEnd::textureUi mtools;

            //window size
            float mfontSize;
            
            //window state
            bool isInitialise;
            backEnd::sizeTexture settings, chrono, profile
                , rest, sound, statistic, work;
            const char* usefullTheme[20] = { "Purple Theme", "Dark Theme", "Blue theme", "AOT Wallpaper"};
            
            public:
            //constructeur && destructeur
            windowUi (float fontsize, ImGuiIO& io);
            ~windowUi();

            //GETTERS
            backEnd::textureUi GettextureUI() { return mtools; }
            ImGuiStyle GetUIstyle() const { return mStyle;}
            ImFont* GetFontUi() const { return Uifont;}
            ImGuiToggleConfig GetToggleConfig() const { return mtoggleConfig;}
            float GetFontSize() const { return mfontSize; }
            bool GetInitialisation() const { return isInitialise; }

            //initialisation
            void InitializeUi(SDL_Renderer* renderer, SDL_Window* window);
            void ShutdownUI();
            //rendu
            int igThemeV3(int hue07, int alt07, int nav07, int lit01 = 0, int compact01 = 0, int border01 = 1, int shape0123 = 1);
            SDL_Texture* Load_imageTexture(SDL_Renderer* renderer, const char* fileLocation);
            void CreateUITexture(SDL_Renderer* renderer);
        };
    } //namespace Uigraphics
} //namespace App