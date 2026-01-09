#include "../../include/pomodoro.h"

namespace App {
    namespace core {
        
        pomodoro::pomodoro(): m_statisitcs(), m_Activate_Sound(true), m_Is_restSession(false),
                m_Is_workSession(false), m_Is_LongRestSession(false), m_Workminuttes(25), m_WorkSecondes(0), m_RestMinutes(5),
                m_RestSeconeds(0), m_LongRest_Minutes(15), m_LongRest_Secondes(0) {
                    std::cout << "⏱️ Creation du pomodoro effectuée avec succès !" <<std::endl;
                }
        
        pomodoro::~pomodoro() {
            std::cout <<"🛠️ Destruction du pomodoro effectuée avec succès !!" << std::endl;
        }

        void pomodoro::TimeSettings() {
            ImGui::SliderInt("Travail(m/s)", &m_Workminuttes, 0, 60);
            ImGui::SliderInt("travail(s)", &m_WorkSecondes, 0, 60);
            ImGui::SliderInt("repos (m/s)", &m_RestMinutes, 0, 30);
            ImGui::SliderInt("repos(s)", &m_RestSeconeds, 0, 60);
            ImGui::SliderInt("Pause Longue", &m_LongRest_Minutes, 0, 60);
            ImGui::SliderInt("Pause Longue (s)", &m_LongRest_Secondes, 0, 60);
            ImGui::SliderInt("tours", &m_SessionNumber, 1, 20);
        }

        /**
         * @name SoundSettings
         * @brief gere les interfaces de modification du son dans les parametre
         */
        void pomodoro::SoundSettings() {
            ImGui::Text("Volume");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::SliderInt(" ", &m_Volume, 0, 100);
            ImGui::Text("Son actif");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::Toggle("##sound", &m_Activate_Sound, ImGuiToggleFlags_Animated);
        }

        void pomodoro::WorkPresentation(SDL_Texture* texture, backEnd::Timer chrono) {
            if (ImGui::Selectable("concentration", &m_Is_workSession, 0, ImVec2(450.0f, 75.0f)))
            ImGui::OpenPopup("session de concentration");

            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("session de concentration", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
                //calcul de la position centrale de la fenetre
                float windowWidth = ImGui::GetWindowWidth();
                float windowHeight = ImGui::GetWindowHeight();
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

        void pomodoro::restPresentation(SDL_Texture* texture, backEnd::Timer chrono) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::Selectable("repos court", &m_Is_restSession, 0, ImVec2(450.0f, 75.0f)))
                ImGui::OpenPopup("session de repos court");
            if (ImGui::BeginPopupModal("session de repos court", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
                //calcul de la position centrale de la fenetre
                float windowWidth = ImGui::GetWindowWidth();
                float windowHeight = ImGui::GetWindowHeight();
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

        void pomodoro::LongRestPresentation(SDL_Texture* texture, backEnd::Timer chrono) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::Selectable("repos long", &m_Is_LongRestSession, 0, ImVec2(450.0f, 75.0f)))
                ImGui::OpenPopup("session de repos long");
            if (ImGui::BeginPopupModal("session de repos long", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
                //calcul de la position centrale de la fenetre
                float windowWidth = ImGui::GetWindowWidth();
                float windowHeight = ImGui::GetWindowHeight();
                ImVec2 img_size = ImVec2(300.0f, 300.0f);
                ImGui::SetCursorPosX((windowWidth - img_size.x) /2);
                ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(300.0f, 300.0f));
                ImGui::Text("Ceci est la session de repos long apparaissant \noccasionnelement après celles concentration. appuyez \nsur commencer pour lancer la session de repos court.");
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
        void pomodoro::Explanations(int counterSession, backEnd::textureUi texture) {
            
            //centralisation de la fenetre de popup
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if (counterSession == 0) {
                ImGui::OpenPopup("presentation", ImGuiPopupFlags_NoReopen);
            }
            if (ImGui::BeginPopupModal("presentation", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                //calcul de la position centrale de la fenetre
                float windowWidth = ImGui::GetWindowWidth();
                float windowHeight = ImGui::GetWindowHeight();
                ImVec2 img_size = ImVec2(300.0f, 300.0f);
                ImGui::SetCursorPosX((windowWidth - img_size.x) /2);
                ImGui::Image((ImTextureID)(intptr_t)texture.chronoTexture, ImVec2(300.0f, 300.0f));
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

    } // namespace core
} // namespace App

