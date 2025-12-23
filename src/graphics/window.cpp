#include "../include/window.h"

namespace App {
    namespace Graphics {        
        window::window (float height, float width, const std::string& title) 
            : mwinHeight(height), mwinWidth(width), mwinTitle(title), mappWindow(nullptr)
            , mAppRenderer(nullptr), mfont(nullptr), ImgTexture(nullptr), winIsinitialise(false)
            , textTexture(nullptr), mrandongenerator(std::random_device{} ()) {
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
            SDL_DestroyRenderer(mAppRenderer);
            SDL_DestroyWindow(mappWindow);
            SDL_Quit();
        }

        void window::CreateDeign(backEnd::backGround theme) {
            switch (theme) {
                case backEnd::backGround::BLUE_THEME :
                    SDL_SetRenderDrawColor(mAppRenderer, 255, 255, 255, 255);
                    SDL_RenderClear(mAppRenderer);
                    for (int i = 0; i < 40; i++) {
                        //dimentionnement aleatoire des paticules dessinees
                        StayInBounds();
                        DrawCircle(particles[i], particlesColor.blue(), mAppRenderer);
                        //deplacement aleatoire
                        mrandom = RandomDirection();
                        particles[i].centerX = particles[i].centerX + mrandom.Addition(particles[i]).x * 0.005f;
                        particles[i].centerY = particles[i].centerY + mrandom.Addition(particles[i]).y * 0.005f;
                    }
                break;

                case backEnd::backGround::GREEN_THEME :
                    SDL_SetRenderDrawColor(mAppRenderer, 0, 0, 0, 150);
                    SDL_RenderClear(mAppRenderer);
                    for (auto& part : particles) {
                        StayInBounds();
                        DrawCircle(part, particlesColor.green(), mAppRenderer);
                        mrandom = RandomDirection();
                        part.centerX += mrandom.x * 0.005f;
                        part.centerY += mrandom.y * 0.005f;
                    }
                break;

                case backEnd::backGround::BEAUTIFULL_GRADIENT :
                    
                break;

                case backEnd::backGround::DARK_THEME :

                break;
                
                case backEnd::backGround::ORIGINAL_DARK :

                break;

                case backEnd::backGround::PINK_THEME :

                break;

                case backEnd::backGround::PURPLE_THEME :

                break;

                case backEnd::backGround::RED_THEME :

                break;

                case backEnd::backGround::YELLOW_THEME :

                break;

                case backEnd::backGround::COLOR_THEME :

                break;
            }
        }

        backEnd::vector2D window::RandomDirection() {
            std::uniform_real_distribution<> dis(-1.0f, 1.0f);
            return backEnd::vector2D(dis(mrandongenerator), dis(mrandongenerator));
        }

        void window::StayInBounds() {
            for (int i = 0; i < 40; i++) {
                if (particles[i].centerX >= mwinWidth + particles[i].radius * 2) {
                    std::uniform_real_distribution<> dix(1.0f, 1600.0f);
                    particles[i].centerX = dix(mrandongenerator);
                }
                if (particles[i].centerY >= mwinHeight + particles[i].radius * 2) {
                    std::uniform_real_distribution<> diy(1.0f, 900.0f);
                    particles[i].centerY = diy(mrandongenerator);
                }
                if (particles[i].centerX <= 0 - particles[i].radius * 2) {
                    std::uniform_real_distribution<> diy(1.0f, 1600.0f);
                    particles[i].centerX = diy(mrandongenerator);
                }
                if (particles[i].centerY <= 0 - particles[i].radius * 2) {
                    std::uniform_real_distribution<> diy(1.0f, 900.0f);
                    particles[i].centerY = diy(mrandongenerator);
                } 
            }
        }

        void window::SpawnRandomParticles() {
            //assignation des posittions aleatoires de depart
            for (int i = 0; i < 40; i++) {
                std::uniform_real_distribution<> dix(1.0f, 1600.0f);
                particles[i].centerX = dix(mrandongenerator);
                std::uniform_real_distribution<> diy(1.0f, 900.0f);
                particles[i].centerY = diy(mrandongenerator);
                std::uniform_real_distribution<> dir(5.0f, 30.0f);
                particles[i].radius = dir(mrandongenerator);
            }
        }
        void window::DrawCircle(backEnd::circle round, backEnd::color effect, SDL_Renderer* renderer) {
            //creation d'un rendu personnalise
            SDL_SetRenderDrawColor(renderer, effect.r, effect.g, effect.b, effect.a);

            for (int width = 0; width <= round.radius * 2; width++) {
                for (int height = 0; height <= round.radius * 2; height++) {
                    //calcul de la position des point situes a une distance convenable du centre
                    float dx = round.radius - width;
                    float dy = round.radius - height;

                    //condition suivant le trace d'un disque plein
                    if(dx * dx + dy * dy <= round.radius * round.radius) {
                        SDL_RenderPoint(renderer, round.centerX + dx, round.centerY + dy);
                    }
                }
            }
        }

        SDL_Texture* window::TextureImg(backEnd::backGround image) {
            //creation d'une surface
            SDL_Surface* imgsurface = nullptr;
            if (image == backEnd::backGround::ORIGINAL_DARK) {
                SDL_Surface* imgsurface = IMG_Load("assets/black_wallpaper.jpg");
            }
            if (image == backEnd::backGround::BEAUTIFULL_GRADIENT) {
                SDL_Surface* imgsurface = IMG_Load("assets/img.jpg");
            }
        }
    } 
}