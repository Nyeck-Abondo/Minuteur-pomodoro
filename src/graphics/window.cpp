#include "../include/window.h"

namespace App {
    namespace Graphics {        
        window::window (float height, float width, const std::string& title) 
            : mwinHeight(height), mwinWidth(width), mwinTitle(title), mappWindow(nullptr)
            , mAppRenderer(nullptr), mfont(TTF_OpenFont("police/Montserrat/static/Montserrat-BoldItalic.ttf", 25.0f))
            , ImgTexture(nullptr), winIsinitialise(false), textTexture(nullptr) {
                std::cout << "✅ initialisation de la fenetre avec succes !!"<< std::endl;
            }
            window::~window(){
                std::cout << "destruction de la fentre." <<std::endl;
            }
        /**
         * @name InitialiseWindow
         * @brief Cette fonction permet d'initialiser la fenetre SDL3 sans fournir trop
         * d'effort
         * @return nothing
         */
        bool window::InitialiseWindow() {
            mappWindow = SDL_CreateWindow(mwinTitle.c_str(), mwinWidth, mwinHeight, 0);
            if (!mappWindow) {
                std::cerr<<"Erreur d'initialisation de la fenetre : "<<SDL_GetError()<< std::endl;
                return false;
            }
            mAppRenderer = SDL_CreateRenderer(mappWindow, nullptr);
            if (!mAppRenderer) {
                std::cerr<<"Erreur d'initialisation du moteur de rendu : "<<SDL_GetError()<<std::endl;
                return false;
            }
            //fond par defaut
            mCurrenTheme = App::backEnd::OfficialTheme::PURPLE_THEME;

            winIsinitialise = true;
            return winIsinitialise;
        }

        /**
         * @name PresentWindow
         * @brief Cette fontion presente le rendu final de la fenetre SDL
         */
        void window::PresentWindow() {
            SDL_RenderPresent(mAppRenderer);
        }

        /**
         * @name ShutdownWindow
         * @brief Elle permet de fermer proprement la fenetre SDL 
         */
        void window::ShutdownWindow() {
            if (ImgTexture != nullptr) SDL_DestroyTexture(ImgTexture);
            SDL_DestroyRenderer(mAppRenderer);
            SDL_DestroyWindow(mappWindow);
            SDL_Quit();
        }

        /**
         * @name ChangePrincipalTheme
         * @brief Cette fonction permet de changer le fond de l'application en chargeant
         * à chaque fois une nouvelle image en background dans la fenetre SDL.
         * @param theme ce parametre represente le theme choisi par l'utilisateur. Il sera
         * appliqué durant l'utilisation
         * @return nothing
         */
        void window::ChangePrincipalTheme(backEnd::OfficialTheme theme) {
            SDL_Surface* surface = nullptr;
            switch (theme) {
                case backEnd::OfficialTheme::BLUE_THEME :
                    surface = IMG_Load("assets/backgrounds/klaus-andersen-2aWVqmjluIQ-unsplash (2).jpg");
                    ImgTexture = SDL_CreateTextureFromSurface(mAppRenderer, surface);
                    SDL_DestroySurface(surface);
                break;

                case backEnd::OfficialTheme::PURPLE_THEME :
                    surface = IMG_Load("assets/backgrounds/liquid_purple.jpg");
                    ImgTexture = SDL_CreateTextureFromSurface(mAppRenderer, surface);
                    SDL_DestroySurface(surface);
                break;

                case backEnd::OfficialTheme::AOT_THEME :
                    surface = IMG_Load("assets/backgrounds/AOT_theme.jpg");
                    ImgTexture = SDL_CreateTextureFromSurface(mAppRenderer, surface);
                    SDL_DestroySurface(surface);
                break;

                case backEnd::OfficialTheme::DARK_LIGHT_THEME :
                surface = IMG_Load("assets/backgrounds/dark_theme.jpg");
                ImgTexture = SDL_CreateTextureFromSurface(mAppRenderer, surface);
                SDL_DestroySurface(surface);
                break;

                case backEnd::OfficialTheme::DARK_THEME :
                surface = IMG_Load("assets/backgrounds/broken-dark.png");
                if (!surface) {
                    std::cerr << "Erreur de chargement de la surface: "<< SDL_GetError() << std::endl;
                }
                ImgTexture = SDL_CreateTextureFromSurface(mAppRenderer, surface);
                SDL_DestroySurface(surface);
                break;
            }
        }

        /**
         * @name TextureImg
         * @brief charge la texture de fond de l'application. Cree une surface avent
         * de la convertir en texture utilisable pour le background
         * @param file ce parametre correspond au chemin d'acces vers l'image qui
         * servira de background à l'application
         */
        void window::TextureImg(const char* file) {
            //creation d'une surface
            SDL_Surface* imgsurface = IMG_Load(file);
            //creation de la texture
            ImgTexture = SDL_CreateTextureFromSurface(mAppRenderer, imgsurface);
            SDL_DestroySurface(imgsurface);
        }

        
        SDL_Texture* window::TextureText(SDL_Renderer* renderer) {
            //creation de la surface
            std::string message = "Welcome To Pomodoro App";
            SDL_Color colorbg = {0, 0, 0, 200};
            SDL_Color colorfg = {255, 255, 255, 255};

            SDL_Surface* fontSurface = TTF_RenderText_Shaded(mfont, message.c_str(), SDL_strlen(message.c_str()), colorfg, colorbg);
            SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);

            return fontTexture;
        }
    } //namespace backend
}//namespace app