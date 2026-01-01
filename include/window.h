#pragma once

#include <SDL3/SDL.h>
#include "../libs/SDL3/SDL3_image/SDL_image.h"
#include <string>
#include <random>
#include <ctime>
#include <iostream>
#include "structs.h"


namespace App {
    namespace Graphics
    {
        class window {
            private:
            //RESSOURCES DE LA FENETRE
            SDL_Window* mappWindow;
            SDL_Renderer* mAppRenderer;
            SDL_Texture* textTexture;
            SDL_Texture* ImgTexture;
            float mwinHeight;
            float mwinWidth;
            float mfontSize;
            bool winIsinitialise;
            std::string mwinTitle;

        public:
            backEnd::OfficialTheme mCurrenTheme; //theme de fond
            //constructeur et destructeur de la classe
            window (float height, float width, const std::string& title);
            ~window();
            
            //GETTERS
            SDL_Window* GetWindowSDL() { return mappWindow;}
            SDL_Renderer* GetRenderer()  { return mAppRenderer;}
            SDL_Texture* GetWindowTexture() { return ImgTexture; }
            float GetWindowHeight() const { return mwinHeight;}
            float GetWindowWidth() const { return mwinWidth;}
            bool Initialised() const { return winIsinitialise;}

            //Initialisation et fermeture de la fenetre

            bool InitialiseWindow();
            void PresentWindow();
            void ShutdownWindow();

            //chargement des images et du text

            void TextureImg(const char* file);

            //rendu des particules de la fenetre
            
            void ChangePrincipalTheme(backEnd::OfficialTheme theme);
        };
    } // namespace Graphics
} //namespace App