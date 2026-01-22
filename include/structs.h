#pragma once

#include <string>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include "../libs/SDL3/SDL.h"
#include "../libs/SDL3/SDL3_image/SDL_image.h"

namespace App{
    namespace backEnd{
        struct Timer {
            int minutes;
            float secondes;
            int timeCounter = 0;
            char chrono[256] = {'0', '0', ' ', ':', ' ', '0', '0', '.', '0', '0'};

            Timer(int min, float sec): minutes(min), secondes(sec) {
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
                    timeCounter++;
                }
                if (secondes < 10.0f) {
                    sprintf(chrono,"%d : 0%0.2f", minutes, secondes);
                }
                if (minutes < 10) {
                   sprintf(chrono,"0%d : %0.2f", minutes, secondes);
                }
                if (minutes < 10 && secondes < 10) {
                    sprintf(chrono, "0%d : 0%0.2f", minutes, secondes);
                }
                if(secondes <= 0 && minutes <= 0) {
                    secondes = 0;
                    sprintf(chrono, "0%d : 0%0.2f", minutes, secondes);
                }
            }

            void InitialiseTimer(int min, float sec) {
                minutes = min;
                secondes =sec;
            }
        };

        //Cette enumeration permet le choix du theme de fond en local de la fenetre
        enum class OfficialTheme {
            DARK_LIGHT_THEME02,
            DARK_LIGHT_THEME,
            DARK_THEME,
            ORANGE_THEME
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
            SDL_Texture* pause;
            SDL_Texture* pompe;
            SDL_Texture* coffee;
        };

        struct animTexureUi {
            SDL_Texture** successPurple;
            SDL_Texture** successYellow;
            SDL_Texture** TimerYellow;
            SDL_Texture** timerBlack;
            SDL_Texture** execution;
            SDL_Texture** graphics;
        };

        struct animPicture {
            IMG_Animation* animationSP;
            IMG_Animation* animationSY;
            IMG_Animation* animationTY;
            IMG_Animation* animationTB;
            IMG_Animation* animationEXE;
            IMG_Animation* animationGraph;
        };
        
        
        enum class animType {
            SUCCESSPURPLE,
            SUCCESSYELLOW,
            TIMERBLACK,
            TIMERYELLOW,
            EXECUTION,
            GRAPH
        };

        //taille des textures
        struct sizeTexture {
            float w;
            float h;
        };
    } // namespace backEnd 
}// namespace App