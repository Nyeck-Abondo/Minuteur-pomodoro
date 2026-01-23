#include "../../include/pomodoro.h"

namespace App {
    namespace core {
        
        pomodoro::pomodoro(): m_statisitcs(),mPresentation_Animation(nullptr), mBlackPresentation_Animation(nullptr),
                mPresentationTexture(nullptr), mBlackPresentationTexture(nullptr),mcounterFrame(0), angle(0.0f), m_Workminuttes(25),
                m_WorkSecondes(0), m_RestMinutes(5), m_RestSeconeds(0), m_LongRest_Minutes(15), m_LongRest_Secondes(0),
                m_SessionNumber(7),m_Activate_Sound(true), m_Is_restSession(false), m_Is_workSession(false),
                m_Is_LongRestSession(false), m_IsNotificationUp(false) {
                    std::cout << "⏱️ Creation du pomodoro effectuée avec succès !" <<std::endl;
                }
        
        pomodoro::~pomodoro() {
            std::cout <<"🛠️ Destruction du pomodoro effectuée avec succès !!" << std::endl;
        }

        bool pomodoro::AnimationInitialised(SDL_Renderer* renderer) {
            mPresentation_Animation = IMG_LoadAnimation("assets/tools/Timer (1).gif");
            mBlackPresentation_Animation = IMG_LoadAnimation("assets/tools/Timer.gif");
            //allocation de la texture
            mPresentationTexture = new SDL_Texture* [mPresentation_Animation->count];
            mBlackPresentationTexture = new SDL_Texture* [mBlackPresentation_Animation->count];
            //verification de l'allocation dynamique
            if (mPresentationTexture == nullptr || mBlackPresentationTexture == nullptr) {
                std::cout << "❌ Echec de l'allocation dynamique de la texture" << std::endl;
                return false;
            }
            //transformation des frames en textures
            for (int i = 0; i < mPresentation_Animation->count; i++) {
                mPresentationTexture[i] = SDL_CreateTextureFromSurface(renderer, mPresentation_Animation->frames[i]);
            }
            std::cout << "✅ texture animée de presentation chargée avec succes !" << std::endl;

            for (int i = 0; i < mBlackPresentation_Animation->count; i++) {
                mBlackPresentationTexture[i] = SDL_CreateTextureFromSurface(renderer, mBlackPresentation_Animation->frames[i]);
            }
            return true;
        }

        void pomodoro::AnimationShutdown() {
            for (int i = 0; i < mPresentation_Animation->count; i++) {
                SDL_DestroyTexture(mPresentationTexture[i]);
            }
            delete [] mPresentationTexture;
            std::cout << "🔓 liberation de la memoire allouée pour l'animation jaune" << std::endl;

            for (int i = 0; i < mBlackPresentation_Animation->count; i++) {
                SDL_DestroyTexture(mBlackPresentationTexture[i]);
            }
            delete [] mBlackPresentationTexture;
            std::cout << "🔓 liberation de la memoire allouée pour l'animation jaune" << std::endl;

            IMG_FreeAnimation(mPresentation_Animation);
            IMG_FreeAnimation(mBlackPresentation_Animation);
        }

        void pomodoro::PlayAnimation(Uint64 deltaTime, ImVec2 size, backEnd::OfficialTheme currentTeme) {
            //choix de l'animation de presentation selon le theme actuel
            if (currentTeme == backEnd::OfficialTheme::DARK_LIGHT_THEME02) {
                if (static_cast<int> (deltaTime) >= mBlackPresentation_Animation->delays[mcounterFrame]) {
                    mcounterFrame++;
                    if (mcounterFrame >= mBlackPresentation_Animation->count) {
                        mcounterFrame = 0;
                    }
                }
                ImGui::Image((ImTextureID)(intptr_t) (mBlackPresentationTexture[mcounterFrame]), size);
            }
            else {
                if (static_cast<int> (deltaTime) >= mPresentation_Animation->delays[mcounterFrame]) {
                    mcounterFrame++;
                    if (mcounterFrame >= mPresentation_Animation->count) {
                        mcounterFrame = 0;
                    }
                }
                ImGui::Image((ImTextureID)(intptr_t) mPresentationTexture[mcounterFrame], size);
            }
        }

        void pomodoro::TimeSettings() {
            ImGui::Spacing();
            ImGui::SliderInt("Travail(m/s)", &m_Workminuttes, 0, 60);
            ImGui::Spacing();
            ImGui::SliderInt("travail(s)", &m_WorkSecondes, 0, 60);
            ImGui::Spacing();
            ImGui::SliderInt("repos (m/s)", &m_RestMinutes, 0, 30);
            ImGui::Spacing();
            ImGui::SliderInt("repos(s)", &m_RestSeconeds, 0, 60);
            ImGui::Spacing();
            ImGui::SliderInt("Pause Longue", &m_LongRest_Minutes, 0, 60);
            ImGui::Spacing();
            ImGui::SliderInt("Pause Longue (s)", &m_LongRest_Secondes, 0, 60);
            ImGui::Spacing();
            ImGui::SliderInt("tours", &m_SessionNumber, 1, 20);
            ImGui::Spacing();
        }

        /**
         * @name SoundSettings
         * @brief gere les interfaces de modification du son dans les parametre
         */
        void pomodoro::SoundSettings() {
            ImGui::Spacing();
            ImGui::Text("Volume");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::SliderInt(" ", &m_Volume, 0, 100);
            ImGui::Spacing();
            ImGui::Text("Son actif");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::Toggle("##sound", &m_Activate_Sound, ImGuiToggleFlags_Animated);
            ImGui::Spacing();
        }

        void pomodoro::WorkPresentation(SDL_Texture* texture) {
            if (ImGui::Selectable("concentration", &m_Is_workSession, 0, ImVec2(450.0f, 75.0f)))
            ImGui::OpenPopup("session de concentration");

            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("session de concentration", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
                //calcul de la position centrale de la fenetre
                float windowWidth = ImGui::GetWindowWidth();
                ImVec2 img_size = ImVec2(300.0f, 300.0f);
                ImGui::SetCursorPosX((windowWidth - img_size.x) /2);
                ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(300.0f, 300.0f));
                ImGui::Text("Ceci est la session de travail ou encore de concentration. \nAppuyez sur le bouton commencer pour lancer la session.");
                ImGui::Separator();
                if (ImGui::Button("Commencer", ImVec2(150.0f, 60.0f))) { 
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(150.0f, 60.0f))) { ImGui::CloseCurrentPopup(); }
                ImGui::EndPopup();
            }
        }

        void pomodoro::restPresentation(SDL_Texture* texture) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::Selectable("repos court", &m_Is_restSession, 0, ImVec2(450.0f, 75.0f)))
                ImGui::OpenPopup("session de repos court");
            if (ImGui::BeginPopupModal("session de repos court", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
                //calcul de la position centrale de la fenetre
                float windowWidth = ImGui::GetWindowWidth();
                ImVec2 img_size = ImVec2(300.0f, 300.0f);
                ImGui::SetCursorPosX((windowWidth - img_size.x) /2);
                ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(300.0f, 300.0f));
                ImGui::Text("Ceci est la session de repos court suivant \ndirectement celles concentration. appuyez sur commencer \npour lancer la session de repos court.");
                if (ImGui::Button("commencer", ImVec2(150.0f, 60.0f))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(150.0f, 60.0f))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }

        void pomodoro::LongRestPresentation(SDL_Texture* texture) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::Selectable("repos long", &m_Is_LongRestSession, 0, ImVec2(450.0f, 75.0f)))
                ImGui::OpenPopup("session de repos long");
            if (ImGui::BeginPopupModal("session de repos long", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
                //calcul de la position centrale de la fenetre
                float windowWidth = ImGui::GetWindowWidth();
                ImVec2 img_size = ImVec2(300.0f, 300.0f);
                ImGui::SetCursorPosX((windowWidth - img_size.x) /2);
                ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(300.0f, 300.0f));
                ImGui::TextWrapped("Ceci est la session de repos long apparaissant occasionnelement après celles concentration. appuyez sur commencer pour lancer la session de repos court.");
                if (ImGui::Button("commencer", ImVec2(150.0f, 60.0f))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(150.0f, 60.0f))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }

        /**
         * @name Sessionchange
         * @brief Cette methode charge un messsage sous la
         * foeme d'un popupmodal à chaques variations du 
         * compteur afin de presenter a l'utilisateur ce que
         * chaque sessions qu'il aborde
         */
        void pomodoro::Explanations(int counterSession, Uint64 deltaTime, backEnd::OfficialTheme currentTeme) {
            
            //centralisation de la fenetre de popup
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if (counterSession == 0) {
                ImGui::OpenPopup("presentation", ImGuiPopupFlags_NoReopen);
            }
            if (ImGui::BeginPopupModal("presentation", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                //calcul de la position centrale de la fenetre
                float windowWidth = ImGui::GetWindowWidth();
                ImVec2 img_size = ImVec2(300.0f, 300.0f);
                ImGui::SetCursorPosX((windowWidth - img_size.x) /2);
                PlayAnimation(deltaTime, ImVec2(300.0f, 300.0f), currentTeme);
                //ecriture des explications concernant le pomodoro
                ImGui::Text(" ");
                ImGui::Text("Ce chronomètre est un outil spécial du nom de \nchronomètre pomodoro mettant a la dispositio\nn de lutilisateur "
                "un ensemble de sept grandes \nsessions se répartisant entre : session de conc\nentration session de repos court et enfin "
                "une \nsession de repos long pour optimiser le travail \net la concetrarion de l'utilisateur pour fournir le \nmeilleur rendement"
                "possible.");
                ImGui::EndPopup();
            }
        }

        float pomodoro::totalTimeToDo (int counterSession) {
            if (counterSession % 2 != 0 || counterSession == 1) {
                return (float)(m_Workminuttes * 60.0f + m_WorkSecondes);
            }
            else if (counterSession % 2 == 0 && counterSession % 4 != 0) {
                return (float)(m_RestMinutes * 60.0f + m_RestSeconeds);
            }
            else if (counterSession % 4 == 0) {
                return (float)(m_LongRest_Minutes * 60.0f + m_LongRest_Secondes);
            }
            return 60.0f;
        }

        void pomodoro::SessionNotification(int minutes, int secondes, int counterSession, backEnd::OfficialTheme currentTheme, SDL_Texture* texture, ImFont* font) {
            //definition de l'angle
            ImVec2 sizeText = ImGui::CalcTextSize("Session de concentration en cours . . .");
            
            switch (currentTheme) {
                case backEnd::OfficialTheme::DARK_LIGHT_THEME02 :
                
                    if (counterSession == 1) {
                        //mouvement de la notification
                        if (angle <= M_Pi) {
                            m_IsNotificationUp = false;
                        }
                        if (!m_IsNotificationUp) {
                            angle += 0.01f;
                        }
                        }else if (angle >=0 || m_IsNotificationUp){
                           angle -= 0.01f;
                        }
                        if (angle == M_Pi) {
                            m_IsNotificationUp = true;
                        }
                        //definition du moment de la duree de vie de la notification
                        if ( minutes <= m_Workminuttes - 1 && minutes > 0 && secondes >= 2.0f ) {
                             
                            ImGui::SetNextWindowPos(ImVec2(360.0f, 1000.0f - (370.0f * sinf(angle))));
                            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
                            ImGui::BeginChild("##notification", ImVec2(800.0f, 100.0f), ImGuiChildFlags_FrameStyle, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);
                            ImGui::Image((ImTextureID)(intptr_t) (texture), ImVec2(75.0f, 75.0f));
                            ImGui::SameLine();
                            ImGui::PushFont(font, 30.0f);
                            ImGui::SetCursorPos(ImVec2(350.0f - sizeText.x / 2.0f, 50.0f - sizeText.y / 2.0f));
                            ImGui::Text("Session de concentration en cours . . .");
                            ImGui::SameLine();
                            ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
                            ImGui::Text(" . ");
                            ImGui::PopFont();
                        
                            ImGui::EndChild();
                            ImGui::PopStyleVar();
                        }
                        if (m_Workminuttes == 0 && m_WorkSecondes <= 0.5f) {
                            angle = 0.0f;
                        }

                    if (counterSession % 2 != 0 || counterSession == 1) {

                    }

                    else if (counterSession % 2 == 0 && counterSession % 4 != 0) {

                    }

                    else if (counterSession % 4 == 0) {

                    }

                break;

                case backEnd::OfficialTheme::DARK_LIGHT_THEME :
                    ImGui::SetNextWindowPos(ImVec2(350.0f, 640.0f));
                    ImGui::BeginChild("##notification", ImVec2(700.0f, 100.0f), ImGuiChildFlags_FrameStyle, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);

                    ImGui::Image((ImTextureID)(intptr_t) (texture), ImVec2(75.0f, 75.0f));

                    ImGui::EndChild();
                break;

                case backEnd::OfficialTheme::DARK_THEME :
                    ImGui::SetNextWindowPos(ImVec2(350.0f, 640.0f));
                    ImGui::BeginChild("##notification", ImVec2(700.0f, 100.0f), ImGuiChildFlags_FrameStyle, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);

                    ImGui::Image((ImTextureID)(intptr_t) (texture), ImVec2(75.0f, 75.0f));

                    ImGui::EndChild();
                break;

                case backEnd::OfficialTheme::ORANGE_THEME :
                    ImGui::SetNextWindowPos(ImVec2(350.0f, 640.0f));
                    ImGui::BeginChild("##notification", ImVec2(700.0f, 100.0f), ImGuiChildFlags_FrameStyle, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);

                    ImGui::Image((ImTextureID)(intptr_t) (texture), ImVec2(75.0f, 75.0f));

                    ImGui::EndChild();
                break;
            }
        }

    } // namespace core
} // namespace App