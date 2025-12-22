#include "../include/window.h"

namespace App {
    namespace Graphics {        
        window::window (float height, float width, const std::string& title) 
            : mwinHeight(height), mwinWidth(width), mwinTitle(title), mappWindow(nullptr)
            , mAppRenderer(nullptr), mfont(nullptr), winIsinitialise(false) {
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
            std::srand(std::time(0));
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
                        
                        DrawCircle(particles[i], particlesColor.blue(), mAppRenderer);
                        //deplacement aleatoire
                        mrandom.x = (std::rand() & 30) + 20;
                        mrandom.y = (std::rand() & 30) + 20;
                        particles[i].centerX += mrandom.Addition(particles[i]).x;
                        particles[i].centerY += mrandom.Addition(particles[i]).y;

                        particles[i].centerX *= 0.002;
                        particles[i].centerY *= 0.002;
                    }
                break;

                case backEnd::backGround::GREEN_THEME :

                break;

                case backEnd::backGround::BEAUTIFULL_CITY :

                break;

                case backEnd::backGround::DARK_THEME :

                break;
                
                case backEnd::backGround::ORIGINAL_LOCAL :

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

        void window::SpawnRandomParticles() {
            //assignation des posittions aleatoires de depart
            for (auto& particule : particles) {
                particule.centerX = (std::rand() % 1600) + 1;
                particule.centerY = (std::rand() % 900) + 1;
                particule.radius = (std::rand() % 16) + 5;
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
    } 
}