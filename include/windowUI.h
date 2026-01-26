#pragma once

#include "../libs/SDL3/SDL.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_sdl3.h"
#include "../libs/imgui/imgui_impl_sdlrenderer3.h"
#include <string>
#include <iostream>
#include "structs.h"
#include "pomodoro.h"

namespace App {
    namespace Uigraphics {
        class windowUi {
            private:
            //window configuration
            ImGuiStyle& mStyle;
            ImFont* Uifont;
            ImGuiIO& mio;
            backEnd::textureUi mtools;

            //animations de Gif
            backEnd::animTexureUi manimation;
            backEnd::animType manimType;
            backEnd::animPicture manimPicture;

            //window size
            float mfontSize;
            
            //window state
            bool isInitialise;
            backEnd::sizeTexture settings, rest
                , sound, statistic, work, pause, coffee
                , pompe;
            
            public:
            //constructeur && destructeur
            windowUi (float fontsize, ImGuiIO& io);
            ~windowUi();

            //GETTERS
            backEnd::textureUi GettextureUI() { return mtools; }
            backEnd::animTexureUi GetAnimTextureUI() { return manimation; }
            backEnd::animType GetAnimType() { return manimType; }
            backEnd::animPicture GetAnimPicture() { return manimPicture; }
            ImGuiStyle GetUIstyle() const { return mStyle;}
            ImFont* GetFontUi() const { return Uifont;}
            float GetFontSize() const { return mfontSize; }
            bool GetInitialisation() const { return isInitialise; }

            //initialisation
            void InitializeUi(SDL_Renderer* renderer, SDL_Window* window);
            void ShutdownUI();
            //rendu
            int igThemeV3(int hue07, int alt07, int nav07, int lit01 = 0, int compact01 = 0, int border01 = 1, int shape0123 = 1);
            SDL_Texture* Load_imageTexture(SDL_Renderer* renderer, const char* fileLocation);
            bool Load_animatedTexture(SDL_Renderer* renderer);
            void PlayAnimation(backEnd::animType animation, Uint64 lastTime, ImVec2 size);
            void CreateUITexture(SDL_Renderer* renderer);

        };
    } //namespace Uigraphics
} //namespace App