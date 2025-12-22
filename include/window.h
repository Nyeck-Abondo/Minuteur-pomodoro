#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <cstdlib>
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
            TTF_Font* mfont;
            float mwinHeight;
            float mwinWidth;
            float mfontSize;
            backEnd::circle particles[40];
            bool winIsinitialise;
            std::string mwinTitle;

        public:
            backEnd::backGround mCurrenTheme; //theme de fond
            backEnd::color mBgColor;
            backEnd::color particlesColor;
            backEnd::vector2D mrandom; //position aleatoire

            //constructeur et destructeur de la classe
            window (float height, float width, const std::string& title);
            ~window();
            
            //GETTERS
            SDL_Window* GetWindowSDL() { return mappWindow;}
            SDL_Renderer* GetRenderer() { return mAppRenderer;}
            float GetWindowHeight() { return mwinHeight;}
            float GetWindowWidth() { return mwinWidth;}
            bool Initialised() { return winIsinitialise;}

            //Initialisation et fermeture de la fenetre
            bool InitialiseWindow();
            void PresentWindow();
            void ShutdownWindow();

            //rendu des particules de la fenetre
            void SpawnRandomParticles();
            void CreateDeign(backEnd::backGround theme);
            void DrawCircle(backEnd::circle round, backEnd::color effect, SDL_Renderer* renderer);
        };
    } // namespace Graphics
} //namespace App