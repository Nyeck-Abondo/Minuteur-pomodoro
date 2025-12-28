#pragma once

#include <string>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include "../libs/SDL3/SDL.h"

namespace App{
    namespace backEnd{
        struct Timer {
            unsigned int minutes : 6;
            float secondes;
            char chrono[256];

            Timer(int min, float second): minutes(min), secondes(second) {
                std::cout << "✅ creation du chronometre reussie !" << std::endl;
            }
            void timeleft() {
                sprintf(chrono,"%d : %0.2f", minutes, secondes);
                if (minutes >= 0) {
                    secondes -= 0.015;
                }
                if (secondes < 0.01 && minutes > 0) {
                    minutes -= 1;
                    secondes = 60;
                }
                if (secondes < 10.0f) {
                    sprintf(chrono,"%d : 0%0.2f", minutes, secondes);
                }
                if (minutes < 10) {
                   sprintf(chrono,"0%d : %0.2f", minutes, secondes);
                }
            }
        };

        //Cette enumeration permet le choix du theme de fond en local de la fenetre
        enum class OfficialTheme {
            BLUE_THEME,
            PURPLE_THEME,
            DARK_LIGHT_THEME,
            AOT_THEME,
            DARK_THEME
        };

        //ensembles des textures d'images a generer
        struct textureUi {
            SDL_Texture* soundTexture;
            SDL_Texture* restTexture;
            SDL_Texture* chronoTexture;
            SDL_Texture* profilTexture;
            SDL_Texture* settingsTexture;
            SDL_Texture* work;
            SDL_Texture* statistics;
        };

        //taille des textures
        struct sizeTexture {
            float w;
            float h;
        };
    } // namespace backEnd 
}// namespace App