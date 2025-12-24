#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL3_image/SDL_image.h>
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
            TTF_Font* mfont;
            mutable std::mt19937 mrandongenerator; //generateur de nombre aleatoire
            float mwinHeight;
            float mwinWidth;
            float mfontSize;
            backEnd::circle particles[40];
            bool winIsinitialise;
            std::string mwinTitle;
            backEnd::vector2D mrandom; //deplacement aleatoire

        public:
            backEnd::backGround mCurrenTheme; //theme de fond
            backEnd::color mBgColor;
            backEnd::color particlesColor;
           

            //constructeur et destructeur de la classe
            window (float height, float width, const std::string& title);
            ~window();
            
            //GETTERS
            SDL_Window* GetWindowSDL() { return mappWindow;}
            SDL_Renderer* GetRenderer()  { return mAppRenderer;}
            float GetWindowHeight() const { return mwinHeight;}
            float GetWindowWidth() const { return mwinWidth;}
            bool Initialised() const { return winIsinitialise;}

            //Initialisation et fermeture de la fenetre
            bool InitialiseWindow();
            void PresentWindow();
            void ShutdownWindow();

            //chargement des images et du text
            SDL_Texture* TextureImg(std::string file, SDL_Renderer* renderer) const;
            SDL_Texture* TextureText(SDL_Renderer* renderer);

            //rendu des particules de la fenetre
            void SpawnRandomParticles();
            backEnd::vector2D RandomDirection() const;
            void StayInBounds(); 
            void CreateDeign(backEnd::backGround theme);
            void DrawCircle(backEnd::circle round, backEnd::color effect, SDL_Renderer* renderer) const;
        };
    } // namespace Graphics
} //namespace App