#pragma once

#include <string>
#include <iomanip>
#include <cstdint>

namespace App{
    namespace backEnd{
        struct Timer {
            unsigned int minutes : 6;
            float secondes;
            std::string timeremain;

            void timeleft() {
                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << secondes;
                timeremain = std::to_string(minutes) + " : ";
                timeremain += stream.str();
                if (minutes >= 0) {
                    secondes -= 0.015;
                }
                if (secondes < 0.01 && minutes > 0) {
                    minutes -= 1;
                    secondes = 60;
                }
                if (secondes < 10.0f) {
                    timeremain = std::to_string(minutes) + " : ";
                    timeremain += "0";
                    stream << std::fixed << std::setprecision(2) << secondes;
                    timeremain += stream.str();
                }
                if (minutes < 10) {
                    timeremain = "0" + std::to_string(minutes);
                    timeremain += " : ";
                    stream << std::fixed << std::setprecision(2) << secondes;
                    timeremain += stream.str(); 
                }
            }
        };

        //cercles dessines pour l'effet de background dans la fenetre SDL
        struct circle {
            float radius;
            int centerX;
            int centerY;
        };
        
        //couleurs des cercles systeme RGBA
        struct color {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;

            //constructeur de couleurs
            color() : r(255), g(255), b(255), a(255) {}
            color(uint8_t red, uint8_t green, uint8_t blue, uint8_t aupacity) 
                : r(red), g(green), b(blue), a(aupacity) {}
            
            //couleurs predefinies
            static color red() { return color(245, 65, 41, 255); }
            static color blue() { return color(65, 119, 196, 255); }
            static color green() { return color(28, 196, 94, 255); }
            static color purple() { return color(182, 45, 196, 255); }
            static color pink() { return color(234, 63, 247, 255); }
            static color yellow() { return color(250, 238, 61, 255); }
            static color brokenWhite() { return color(242, 242, 242, 255); }
        };

        //vecteurs de deplacement
        struct vector2D {
            float x;
            float y;
            //constructeur
            vector2D () : x(0), y(0) {}
            vector2D(float vectx, float vecty) : x(vectx), y(vecty) {}
            //methodes utilitaires
            vector2D Addition(circle cercle) {
                return vector2D(x + cercle.centerX, y + cercle.centerY);
            }
        };
        
        
        //Cette enumeration permet le choix du theme de fond en local de la fenetre
        enum class backGround {
            DARK_THEME,
            COLOR_THEME,
            RED_THEME,
            PURPLE_THEME,
            PINK_THEME,
            YELLOW_THEME,
            BLUE_THEME,
            GREEN_THEME,
            ORIGINAL_LOCAL,
            BEAUTIFULL_CITY,
        };

        //choix des onglets de l'application
        enum class UiNavigation {
            PARAMETERS,
            STATISTICS,
            PROFILE,
            HELP
        };
    } // namespace backEnd 
}// namespace App