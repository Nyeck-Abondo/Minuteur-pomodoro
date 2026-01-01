#include "../../include/pomodoro.h"

namespace App {
    namespace core {
        
        pomodoro::pomodoro(): m_WorkChrono({0, 5.0f}),m_statisitcs(), m_Activate_Sound(true), m_Is_restSession(false),
                m_Is_workSession(false), m_Is_LongRestSession(false), m_Workminuttes(20), m_WorkSecondes(0), m_RestMinutes(5),
                m_RestSeconeds(0), m_LongRest_Minutes(15), m_LongRest_Secondes(0) {
                    std::cout << "⏱️ Creation du pomodoro effectuée avec succès !" <<std::endl;
                }
        
        pomodoro::~pomodoro() {
            std::cout <<"🛠️ Destruction du pomodoro effectuée avec succès !!" << std::endl;
        }

        void pomodoro::TimeSettings(backEnd::Timer chrono) {
            int values1[] = {m_Workminuttes, (int)m_WorkSecondes};
            int values2[] = {m_RestMinutes, (int)m_RestSeconeds};
            int values3[] = {m_LongRest_Minutes, (int)m_LongRest_Secondes};
            ImGui::SliderInt("Travail(m/s)", &chrono.minutes, 0, 60);
            ImGui::SliderInt2("repos (m/s)", values2, 0, 30);
            ImGui::SliderInt2("Pause Longue", values3, 0, 60);
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

        /**
         * @name SessionProgression
         * @brief cette fonction dessine une barre horizontale de menu.
         * ce menu non clicables est un indicateur de session, faisant 
         * aparaitre en surbrillance la sesssion dans laquelle on se trouve
         */
        void pomodoro::SessionProgression(backEnd::textureUi texture, backEnd::Timer chrono) {
            //Dessin de la barre de menu horizontale
            ImGui::BeginChild("##progress Session",ImVec2(1600.0f, 75.0f), ImGuiChildFlags_Borders, 0);
            WorkPresentation(texture.work, chrono);
            ImGui::SameLine();
            restPresentation(texture.restTexture, chrono);
            ImGui::SameLine();
            LongRestPresentation(texture.chronoTexture, chrono);

            ImGui::EndChild();
        }

        void pomodoro::WorkPresentation(SDL_Texture* texture, backEnd::Timer chrono) {
            if (ImGui::Selectable("session de concentration", &m_Is_workSession, 0, ImVec2(450.0f, 75.0f)))
            ImGui::OpenPopup("session de concentration");

            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("session de concentration", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

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

            if (ImGui::Selectable("session de repos court", &m_Is_restSession, 0, ImVec2(450.0f, 75.0f)))
                ImGui::OpenPopup("session de repos court");
            if (ImGui::BeginPopup("session de repos court")) {
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

            if (ImGui::Selectable("session de repos long", &m_Is_LongRestSession, 0, ImVec2(450.0f, 75.0f)))
                ImGui::OpenPopup("session de repos long");
            if (ImGui::BeginPopup("session de repos long")) {
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
         * @name WorkChronometer
         * @brief En charge de la gestion du temps de travail
         * se lance lors qu'une session de concentration debute
         */
        void pomodoro::Chronometer(bool is_session) {

        }

    } // namespace core  
} // namespace App

