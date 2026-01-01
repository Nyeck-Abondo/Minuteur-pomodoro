#include "../../include/pomodoro.h"

namespace App {
    namespace core {
        
        pomodoro::pomodoro(): m_WorkChrono({0, 5.0f}), m_RestChrono({5, 0.0f}),
                m_LongRestChrono({15, 0.0f}),m_statisitcs(), m_CounterSession(0),
                m_Activate_Sound(true), m_NExt_Session(false), m_Is_restSession(false),
                m_Is_workSession(true), m_Is_LongRestSession(false) {
                    std::cout << "⏱️ Creation du pomodoro effectuée avec succès !" <<std::endl;
                }
        
        pomodoro::~pomodoro() {
            std::cout <<"🛠️ Destruction du pomodoro effectuée avec succès !!" << std::endl;
        }

        void pomodoro::TimeSettings() {
            int values1[] = {m_WorkChrono.minutes, (int)m_WorkChrono.secondes};
            int values2[] = {m_RestChrono.minutes, (int)m_RestChrono.secondes};
            int values3[] = {m_LongRestChrono.minutes, (int)m_LongRestChrono.secondes};
            ImGui::SliderInt2("Travail(m/s)", values1, 0, 60);
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
         * @name WorkSessionPresentation
         * @brief cette fonction gere l'affichafe d;un popupmodal visant
         * a presenter la session en cours avec une icone personnalisee
         */
        void pomodoro::WorkSessionPresentation(SDL_Texture* texture) {
            ImGuiWindowFlags flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            ImGui::OpenPopup("Session de concentration");
            ImGui::SetNextWindowSize(ImVec2(500, 400));
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Session de concentration", &m_Is_workSession, flag)) {
                ImGui::SetCursorPos(ImGui::GetMainViewport()->GetCenter());
                ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(250.0f, 250.0f));
                ImGui::Separator();
                ImGui::Text("Souhaitez vous commencer la Session de concentraion?");
                ImGui::SetCursorPos(ImVec2(ImGui::GetMainViewport()->GetCenter().x , 70.0f));
                if (ImGui::Button("Commencer", ImVec2(250.0f, 50.0f))) {
                    m_Is_restSession = false;
                    m_Is_workSession = true;
                    m_Is_LongRestSession = false;
                    m_NExt_Session = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        
        /**
         * @name RestSessionPresentation
         * @brief affiche une fentre popupmodal visant a 
         * presenter la session de repos court
         */
        void pomodoro::RestSessionPresentation(SDL_Texture* texture) {
            ImGuiWindowFlags flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            ImGui::OpenPopup("Session de Repos");
            ImGui::SetNextWindowSize(ImVec2(500, 400));
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Session de concentration", &m_Is_workSession, flag)) {
                ImGui::SetCursorPos(ImGui::GetMainViewport()->GetCenter());
                ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(250.0f, 250.0f));
                ImGui::Separator();
                ImGui::Text("Souhaitez vous commencer la Session de concentraion?");
                ImGui::SetCursorPos(ImVec2(ImGui::GetMainViewport()->GetCenter().x , 70.0f));
                if (ImGui::Button(u8"Débuter", ImVec2(250.0f, 50.0f))) {
                    m_Is_restSession = true;
                    m_Is_workSession = false;
                    m_Is_LongRestSession = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }

        /**
         * @name LongRestsessionPresentation
         * @brief affiche une fentre popupmodal qui vise a presenter
         * la session de repos long
         */
        void pomodoro::LongRestsessionPresentation(SDL_Texture* texture) {
            ImGuiWindowFlags flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            ImGui::OpenPopup("Session de concentration");
            ImGui::SetNextWindowSize(ImVec2(500, 400));
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Session de concentration", &m_Is_workSession, flag)) {
                ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(250.0f, 250.0f));
                ImGui::Text("Souhaitez vous commencer la Session de concentraion?");
                ImGui::SetCursorPos(ImVec2(ImGui::GetMainViewport()->GetCenter().x , 70.0f));
                if (ImGui::Button(u8"Débuter", ImVec2(250.0f, 50.0f))) {
                    m_Is_restSession = false;
                    m_Is_workSession = false;
                    m_Is_LongRestSession = true;
                    if (m_LongRestChrono.minutes == 0 && m_LongRestChrono.secondes == 0) {
                        m_LongRestChrono.minutes = 15;
                        m_LongRestChrono.secondes = 0.0f;
                    }
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
        void pomodoro::WorkChronometer(bool is_session) {

            if (is_session) {
                //calcul du temps restant
                m_WorkChrono.timeleft();
                if (m_WorkChrono.minutes == 0 && m_WorkChrono.secondes == 0.0f) {
                    m_NExt_Session =true;
                }
            }
        }

        /**
         * @name RestChronometer
         * @brief Gere le temps de repos court. se lance lorsqu'une
         * session de repos court debute
         * @param is_session permet de verifier si la session actuelle
         * correspond a une session de repos court. si cela est le cas
         * la fonction se lance automatiquement
         */
        void pomodoro::RestChronometer(bool is_session) {
            if (is_session) {
                //calcul du temps restant
                m_WorkChrono.timeleft();
                if (m_RestChrono.minutes == 0 && m_RestChrono.secondes > 0.0f && m_RestChrono.secondes < 0.02f) {
                    m_NExt_Session =true;
                }
            }
        }

        /**
         * @name LongRestChronometer
         * @brief gere le temps de repos long. Se lance lorsqu'une 
         * session de repos long debute
         * @param is_session permet de verifier si la session actuelle
         * correspond a la session de repos long. si oui la fonction est lance
         */
        void pomodoro::LongRestChronometer(bool is_session) {
            if (is_session) {
                //calcul du temps restant
                m_WorkChrono.timeleft();
                if (m_LongRestChrono.minutes == 0 && m_LongRestChrono.secondes > 0.0f && m_LongRestChrono.secondes < 0.02f) {
                    m_NExt_Session =true;
                }
            }
        }

        /**
         * $
         */
        void pomodoro::SessionChange(backEnd::textureUi texture) {
            if (m_NExt_Session) {
                if (m_CounterSession <= 2) {
                    m_CounterSession++;
                    switch (m_CounterSession) {
                        case 1:
                            WorkSessionPresentation(texture.work);
                        break;
                        case 2:
                            RestSessionPresentation(texture.restTexture);
                        break;
                        case 3:
                            WorkSessionPresentation(texture.work);
                        break;
                        case 4:
                            LongRestsessionPresentation(texture.restTexture);
                        break;
                    }
                }
            }
        }

    } // namespace core  
} // namespace App

