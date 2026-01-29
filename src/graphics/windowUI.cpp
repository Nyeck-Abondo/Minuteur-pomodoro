#include "../include/windowUI.h"
#include "../libs/SDL3/SDL.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h"

namespace App{
    namespace Uigraphics{
        /**
         * @name constructeur
         * @brief constructeur de la classe windowUi.
         * @param width represente la largeur de la fenetre ImGui
         * @param height represente la hquteur de la fenetre ImGui.
         * @param fontsize represente la taille de la police utilisee
         * par la fenetre ImGui pour l'ecriture du texte.
         * @param io represente l'objet.
         */
        windowUi::windowUi(float fontsize, ImGuiIO& io)
                : mStyle(ImGui::GetStyle()), Uifont(nullptr), mio(io),
                mtools({nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}),
                manimation({nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}), manimPicture({nullptr, nullptr,
                nullptr, nullptr, nullptr, nullptr}), mfontSize(fontsize), isInitialise(false) {
                    std::cout << "🛠️ cration de la fenetre imgui reussi !!"<<std::endl;
        }
         windowUi::~windowUi() {
            std::cout<<"destruction propre de imgui interface"<<std::endl;
        }

        /**
         * InitializeUi
         *  @brief- initialise la fenetre imgui
         * @param renderer correspond au moteur de rendu de la fenetre parent SDL
         * @param window correspond a la fenetre SDL elle meme(la variable qui 
         * prend en charge sa creation).
         * @return nothing. 
         */
        void windowUi::InitializeUi(SDL_Renderer* renderer, SDL_Window* window) {
            mio.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            Uifont = mio.Fonts->AddFontFromFileTTF("police/Montserrat/static/Montserrat-Black.ttf");
            //initialisation des paquet imgui
            ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
            ImGui_ImplSDLRenderer3_Init(renderer);
        }

        /**
         * @name ShutdownUI()
         * @brief -Ferme proprement la fentre imgui elle ne prend aucun parametre
         */
        void windowUi::ShutdownUI() {
            //liberation de la texture d'execution
            for (int i = 0; i <= manimPicture.animationEXE->count; i++) {
                SDL_DestroyTexture(manimation.execution[i]);
            }
            delete [] manimation.execution;

            //liberation de la texture de graphique
            for (int i = 0; i <= manimPicture.animationGraph->count; i++) {
                SDL_DestroyTexture(manimation.graphics[i]);
            }
            delete [] manimation.graphics;

            //liberation de la texture d'animation de succes violette
            for (int i = 0; i <= manimPicture.animationSP->count; i++) {
                SDL_DestroyTexture(manimation.successPurple[i]);
            }
            delete [] manimation.successPurple;

            //liberation de la texture d'animation de succes jaune
            for (int i = 0; i <= manimPicture.animationSY->count; i++) {
                SDL_DestroyTexture(manimation.successYellow[i]);
            }
            delete [] manimation.successYellow;

            //liberation de la texture d'animation de chrono noire
            for (int i = 0; i <= manimPicture.animationTB->count; i++) {
                SDL_DestroyTexture(manimation.timerBlack[i]);
            }
            delete [] manimation.timerBlack;

            //liberation de la texture de l'animation de chrono jaune
            for (int i = 0; i <= manimPicture.animationTY->count; i++) {
                SDL_DestroyTexture(manimation.TimerYellow[i]);
            }
            delete [] manimation.TimerYellow;

            IMG_FreeAnimation(manimPicture.animationEXE);
            IMG_FreeAnimation(manimPicture.animationGraph);
            IMG_FreeAnimation(manimPicture.animationSP);
            IMG_FreeAnimation(manimPicture.animationSY);
            IMG_FreeAnimation(manimPicture.animationTB);
            IMG_FreeAnimation(manimPicture.animationTY);

            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
            //textures crees
            SDL_DestroyTexture(mtools.chronoTexture);
            SDL_DestroyTexture(mtools.profilTexture);
            SDL_DestroyTexture(mtools.restTexture);
            SDL_DestroyTexture(mtools.settingsTexture);
            SDL_DestroyTexture(mtools.soundTexture);
            SDL_DestroyTexture(mtools.statistics);
            SDL_DestroyTexture(mtools.work);
            SDL_DestroyTexture(mtools.coffee);
            SDL_DestroyTexture(mtools.pause);
            SDL_DestroyTexture(mtools.pompe);
            SDL_DestroyTexture(mtools.yellowNotification);
            SDL_DestroyTexture(mtools.blueNotification);
            SDL_DestroyTexture(mtools.darkNotification);

        }

        /**
         * @name Load_imageTexture
         * @brief Permet la copie des pixels des images dans des textures a l'aide de la 
         * bibliotheque stb_image. elle est utilisée pour creer des texture pour les icones
         * de l'application.
         * @param renderer c'est le moteur de rendu de l'application, en charge d'appliquer 
         * les textures dans le decor de fond de la fenetre SDL
         * @param fileLocation chemin d'acces vers le fichier image  a charger dans la texture.
         * @return texture de type SDL_Texture* , c'est la textuer a afficher dans la fenetre de
         * rendu. 
         */
        SDL_Texture* windowUi::Load_imageTexture(SDL_Renderer* renderer, const char* fileLocation) {
            int width, height, channels;
            unsigned char* image_data = stbi_load(fileLocation, &width, &height, &channels, 4);
            //verification du chargement de l'image en memoire
            if (!image_data) {
                std::cerr << "Erreur de chargement de l'image: " << stbi_failure_reason() << std::endl;
                return nullptr;
            }
            std::cout << "image : "<< fileLocation << " taille : " << width << " x " << height << std::endl;
            std::cout << "😁 image : " << fileLocation << " chargée avec succes!" << std::endl; 
            //creation de la texutre
            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
            if (!texture) {
                std::cerr << "❌Erreur de creation de la texture: " << SDL_GetError() << std::endl;
                stbi_image_free(image_data);
                return nullptr;
            }
            //copie des pixel
            SDL_UpdateTexture(texture, nullptr, image_data, width * 4);
            //liberation de la memeoire
            stbi_image_free(image_data);
            return texture;
        }

        bool windowUi::Load_animatedTexture(SDL_Renderer* renderer) {
            //chargement des animations (sont toutes des tableaux de surfaces)
            manimPicture.animationSP = IMG_LoadAnimation("assets/tools/Success (1).gif");
            manimPicture.animationSY = IMG_LoadAnimation("assets/tools/Success (2).gif");
            manimPicture.animationTY = IMG_LoadAnimation("assets/tools/Timer (1).gif");
            manimPicture.animationTB = IMG_LoadAnimation("assets/tools/Timer.gif");
            manimPicture.animationEXE = IMG_LoadAnimation("assets/tools/en-cours-dexecution.gif");
            manimPicture.animationGraph = IMG_LoadAnimation("assets/tools/analytique.gif");
            
            //annimation de success violette
            manimation.successPurple = new SDL_Texture* [manimPicture.animationSP->count];
            if (manimation.successPurple == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de succes violette !!" << std::endl;
                return false;
            }
            
            //convertion en texture
            for (int i = 0; i < manimPicture.animationSP->count; i++) {
                manimation.successPurple[i] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationSP->frames[i]);
            }
            std::cout << "✅ creation de la texture de succes violette !!" << std::endl;

            //animation de succes du theme jaune
            manimation.successYellow = new SDL_Texture* [manimPicture.animationSP->count];
            if (manimation.successYellow == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de succes jaune !!" << std::endl;
                return false;
            }
            
            //concvertion en texture
            for (int i = 0; i < manimPicture.animationSY->count; i++) {
                manimation.successYellow[i] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationSY->frames[i]);
            }
            std::cout << "✅ creation de la texture de succes jaune !!" << std::endl;

            //animation du timer theme blanc
            manimation.timerBlack = new SDL_Texture* [manimPicture.animationTB->count];
            if (manimation.timerBlack == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de chrnometre noir !!" << std::endl;
                return false;
            }
            std::cout << "✅ creation de la texture de chrnometre noir !!" << std::endl;
            for (int k = 0; k < manimPicture.animationTB->count; k++) {
                manimation.timerBlack[k] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationTB->frames[k]);
            }

            //animation du timer pour le theme jaune
            manimation.TimerYellow = new SDL_Texture* [manimPicture.animationTY->count];
            if (manimation.TimerYellow == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de chronometre jaune !!" << std::endl;
                return false;
            }
            std::cout << "✅ creation de la texture de chronometre jaune !!" << std::endl;
            for (int l = 0; l < manimPicture.animationTY->count; l++) {
                manimation.TimerYellow[l] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationTY->frames[l]);
            }

            //animation de l'execution de la session de travail
            manimation.execution = new SDL_Texture* [manimPicture.animationEXE->count];
            if (manimation.execution == nullptr) {
                std::cout << "❌ Echec de la creation de la texture d'execution !!" << std::endl;
                return false;
            }
            std::cout << "✅ creation de la texture d'execution !!" << std::endl;
            for (int p = 0; p < manimPicture.animationEXE->count; p++) {
                manimation.execution[p] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationEXE->frames[p]);
            }

            //animation des l'augmentation des statistiques par notifications
            manimation.graphics = new SDL_Texture* [manimPicture.animationGraph->count];
            if (manimation.graphics == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de graphe !!" << std::endl;
                return false;
            }
            std::cout << "✅ creation de la texture de graphe !!" << std::endl;
            for (int g = 0; g < manimPicture.animationGraph->count; g++) {
                manimation.graphics[g] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationGraph->frames[g]);
            }

            return true;
        }

        void windowUi::PlayAnimation(backEnd::animType animation, Uint64 lastTime, ImVec2 size) {
            //temps actuel lors de l'appel de la fenetre de notification
            Uint64 currentTime = SDL_GetTicks();
            //frame actuelle
            static int currentFrame = 0;
            //choix de l'animation a jouer en fonction de la notification passé vers
            //l'utilisateur
            switch (animation) {
                case backEnd::animType::SUCCESSPURPLE :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationSP->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationSP->count) {
                            currentFrame = 0;
                        }
                    }
                    ImGui::Image((ImTextureID)(intptr_t) manimation.successPurple[currentFrame], size);
                break;

                case backEnd::animType::SUCCESSYELLOW :

                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationSY->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationSY->count) {
                            currentFrame = 0;
                        }
                    }
                    ImGui::Image((ImTextureID)(intptr_t) manimation.successYellow[currentFrame], size);
                break;

                case backEnd::animType::TIMERBLACK :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationTB->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationTB->count) {
                            currentFrame = 0;
                        }
                    }
                    ImGui::Image((ImTextureID)(intptr_t) manimation.timerBlack[currentFrame], size);
                break;

                case backEnd::animType::TIMERYELLOW :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationTY->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationTY->count) {
                            currentFrame = 0;
                        }
                    }
                    ImGui::Image((ImTextureID)(intptr_t) manimation.TimerYellow[currentFrame], size);
                break;

                case backEnd::animType::EXECUTION :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationEXE->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationEXE->count) {
                            currentFrame = 0;
                        }
                    }
                    ImGui::Image((ImTextureID)(intptr_t) manimation.execution[currentFrame], size);
                break;

                case backEnd::animType::GRAPH :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationGraph->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationGraph->count) {
                            currentFrame = 0;
                        }
                    }
                    ImGui::Image((ImTextureID)(intptr_t) manimation.graphics[currentFrame], size);
                break;
            }
        }
        
        /**
         * @name CreateUITexture
         * @brief elle charge les differentes textures des icones dans le moteur de rendu pour 
         * l'affichage final.
         * @param renderer correspond au moteur de rendu a qui on passera les textures prealablement
         * crees.
         */
        void windowUi::CreateUITexture(SDL_Renderer* Renderer) {
            mtools.settingsTexture = Load_imageTexture(Renderer, "assets/tools/icons8-settings-100.png");
            mtools.restTexture = Load_imageTexture(Renderer, "assets/tools/person_17580600.png");
            mtools.soundTexture = Load_imageTexture(Renderer, "assets/tools/icons8-musical-note-100.png");
            mtools.statistics =Load_imageTexture(Renderer, "assets/tools/icons8-analytique-100 (1).png");
            mtools.work = Load_imageTexture(Renderer, "assets/tools/work_6190606.png");
            mtools.coffee = Load_imageTexture(Renderer, "assets/tools/icons8-coffee-cup-100.png");
            mtools.pause = Load_imageTexture(Renderer, "assets/tools/icons8-pause-100.png");
            mtools.pompe = Load_imageTexture(Renderer, "assets/tools/icons8-pompes-100.png");
            mtools.yellowNotification = Load_imageTexture(Renderer, "assets/notification/png/002-actif-1.png");
            mtools.blueNotification = Load_imageTexture(Renderer, "assets/notification/png/001-actif.png");
            mtools.darkNotification = Load_imageTexture(Renderer, "assets/notification/png/003-actif-2.png");
            //recuperation des dimensions
            SDL_GetTextureSize(mtools.settingsTexture, &settings.w, &settings.w);
            SDL_GetTextureSize(mtools.restTexture, &rest.w, &rest.h);
            SDL_GetTextureSize(mtools.soundTexture, &sound.w, &sound.h);
            SDL_GetTextureSize(mtools.statistics, &statistic.w, &statistic.h);
            SDL_GetTextureSize(mtools.work, &work.w, &work.h);
            SDL_GetTextureSize(mtools.coffee, &coffee.w, &coffee.h);
            SDL_GetTextureSize(mtools.pause, &pause.w, &pause.h);
            SDL_GetTextureSize(mtools.pompe, &pompe.w, &pompe.h);
        }
        
    }
}