#include "../../include/pomodoro.h"

namespace App {
    namespace core {
        
        pomodoro::pomodoro(): m_WorkChrono({20, 0.0f}), m_RestChrono({5, 0.0f}),
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

        void pomodoro::SoundSettings() {
            ImGui::Text("Volume");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::SliderInt(" ", &m_Volume, 0, 100);
            ImGui::Text("Son actif");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::Toggle("##sound", &m_Activate_Sound, ImGuiToggleFlags_Animated);
        }

        void pomodoro::WorkSessionPresentation(backEnd::textureUi texture) {
            ImGuiWindowFlags flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            ImGui::OpenPopup("Session de concentration");
            ImGui::SetNextWindowSize(ImVec2(500, 400));
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Session de concentration", &m_Is_workSession, flag)) {
                ImGui::SetCursorPos(ImGui::GetMainViewport()->GetCenter());
                ImGui::Image((ImTextureID)(intptr_t)texture.work, ImVec2(250.0f, 250.0f));
                ImGui::Separator();
                ImGui::Text("Souhaitez vous commencer la Session de concentraion?");
                ImGui::SetCursorPos(ImVec2(ImGui::GetMainViewport()->GetCenter().x , 70.0f));
                if (ImGui::Button("Commencer", ImVec2(250.0f, 50.0f))) {
                    m_Is_restSession = false;
                    m_Is_workSession = true;
                    m_Is_LongRestSession = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        
        void pomodoro::RestSessionPresentation(backEnd::textureUi texture) {
            ImGuiWindowFlags flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            ImGui::OpenPopup("Session de Repos");
            ImGui::SetNextWindowSize(ImVec2(500, 400));
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Session de concentration", &m_Is_workSession, flag)) {
                ImGui::SetCursorPos(ImGui::GetMainViewport()->GetCenter());
                ImGui::Image((ImTextureID)(intptr_t)texture.work, ImVec2(250.0f, 250.0f));
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

        void pomodoro::LongRestsessionPresentation(backEnd::textureUi texture) {
            ImGuiWindowFlags flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            ImGui::OpenPopup("Session de concentration");
            ImGui::SetNextWindowSize(ImVec2(500, 400));
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Session de concentration", &m_Is_workSession, flag)) {
                ImGui::SetCursorPos(ImGui::GetMainViewport()->GetCenter());
                ImGui::Image((ImTextureID)(intptr_t)texture.work, ImVec2(250.0f, 250.0f));
                ImGui::Separator();
                ImGui::Text("Souhaitez vous commencer la Session de concentraion?");
                ImGui::SetCursorPos(ImVec2(ImGui::GetMainViewport()->GetCenter().x , 70.0f));
                if (ImGui::Button(u8"Débuter", ImVec2(250.0f, 50.0f))) {
                    m_Is_restSession = false;
                    m_Is_workSession = false;
                    m_Is_LongRestSession = true;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }

        void pomodoro::Chronometer(backEnd::Timer chrono, bool is_session) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                ImGui::SetNextWindowPos(ImVec2(center.x + 90.0f, center.y), 0, ImVec2(0.5, 0.55));
                ImGui::BeginChild("##chrono01", ImVec2(650.0f, 500.0f), ImGuiChildFlags_None, ImGuiWindowFlags_NoBackground);

                if (is_session) {
                    //calcul du temps restant
                    chrono.timeleft();
                    if (chrono.minutes == 0 && chrono.secondes > 0.0f && chrono.secondes < 0.02f) {
                        m_NExt_Session =true;
                    }
                }
        }

    } // namespace core  
} // namespace App

