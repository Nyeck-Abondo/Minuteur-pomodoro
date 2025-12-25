#include "../include/window.h"

namespace App {
    namespace Graphics {        
        window::window (float height, float width, const std::string& title) 
            : mwinHeight(height), mwinWidth(width), mwinTitle(title), mappWindow(nullptr)
            , mAppRenderer(nullptr), mfont(TTF_OpenFont("police/Montserrat/static/Montserrat-BoldItalic.ttf", 25.0f))
            , ImgTexture(nullptr), winIsinitialise(false), textTexture(nullptr)
            , mrandongenerator(std::random_device{} ()) {
                std::cout << "✅ initialisation de la fenetre avec succes !!"<< std::endl;
            }
            window::~window(){
                std::cout << "destruction de la fentre." <<std::endl;
            }
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
            winIsinitialise = true;
            return winIsinitialise;
        }

        void window::PresentWindow() {
            SDL_RenderPresent(mAppRenderer);
        }

        void window::ShutdownWindow() {
            if (ImgTexture != nullptr) SDL_DestroyTexture(ImgTexture);
            SDL_DestroyRenderer(mAppRenderer);
            SDL_DestroyWindow(mappWindow);
            SDL_Quit();
        }

        void window::ChangePrincipalTheme(backEnd::OfficialTheme theme) {
            SDL_Surface* surface = nullptr;
            switch (theme) {
                case backEnd::OfficialTheme::BLUE_THEME :
                    surface = IMG_Load("assets/backgrounds/dark_02.jpg");
                    ImgTexture = SDL_CreateTextureFromSurface(mAppRenderer, surface);
                    SDL_DestroySurface(surface);
                break;

                case backEnd::OfficialTheme::PURPLE_THEME :
                    surface = IMG_Load("assets/backgrounds/Windows Wallpaper Black Purple R.jpg");
                    ImgTexture = SDL_CreateTextureFromSurface(mAppRenderer, surface);
                    SDL_DestroySurface(surface);
                break;
            }
        }

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