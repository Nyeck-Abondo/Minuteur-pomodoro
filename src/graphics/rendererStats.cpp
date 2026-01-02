#include "../../include/renderStats.h"

namespace App {
    namespace Statistic {
        void SessionDoneUi(ImFont* font,const char* counterSession) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();

            //section des sessions teminees
            ImGui::SetNextWindowPos(ImVec2(center.x - 250.0f, center.y + 250.0f), 0, ImVec2(0.5f, 0.5f));
            ImGui::BeginChild("##SessionDone", ImVec2(300, 300));

            //positionnement du compteur de sessions
            float windowWidth = ImGui::GetWindowWidth();
            float windowHeigth = ImGui::GetWindowHeight();
            ImVec2 text_size = ImGui::CalcTextSize(counterSession);

            //vecteurs de centre du compteur de sessions
            ImVec2 count_Center = ImVec2((windowWidth - text_size.x) / 2, (windowHeigth - text_size.y) / 2);

            ImGui::PushFont(font, 30.0f);
            ImGui::Text("Sessions \nComplétées");
            ImGui::PopFont();
            ImGui::PushFont(font, 40.0f);
            //positionnement au centre
            ImGui::SetCursorPos(count_Center);
            ImGui::Text("%s", counterSession);
            ImGui::PopFont();
            ImGui::EndChild();
        }

        void ElapsedTimeUi(ImFont* font, int timeCounter) {
            //calcul du centre de la fenetre principale
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();

            //section des session de decompte du temps
            ImGui::SetNextWindowPos(ImVec2(center.x - 250.0f, center.y + 250.0f), 0, ImVec2(0.5f, 0.5f));

            //section du temps de comcentration effectue
            ImGui::SetNextWindowPos(ImVec2(center.x + 100.0f, center.y + 250.0f), 0, ImVec2(0.5f, 0.5f));
            ImGui::BeginChild("##ElapsedTime", ImVec2(300.0f, 300.0f));

            //positionnement du compteur de sessions
            float windowWidth = ImGui::GetWindowWidth();
            float windowHeigth = ImGui::GetWindowHeight();

            //calcul de la position centrale
            ImVec2 time_size = ImGui::CalcTextSize(std::to_string(timeCounter).c_str());
            
            //vecteur de centre du compteur de temps
            ImVec2 time_center = ImVec2((windowWidth - time_size.x) / 2 , (windowHeigth - time_size.y) / 2);
            //positionnement du compteur
            
            ImGui::PushFont(font, 30.0f);
            ImGui::Text("Temps total de \nconcentration");
            ImGui::PopFont();
            
            ImGui::PushFont(font, 40.0f);
            ImGui::SetCursorPos(time_center);
            ImGui::Text("%d", timeCounter);
            ImGui::PopFont();
            ImGui::EndChild();
        }

        void TotalPauseUi(ImFont* font, int pauseCounter) {
            //calcul du centre de la fenetre principale
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();

            //section des session de decompte du temps
            ImGui::SetNextWindowPos(ImVec2(center.x - 250.0f, center.y + 250.0f), 0, ImVec2(0.5f, 0.5f));

            ImGui::SetNextWindowPos(ImVec2(center.x + 450.0f, center.y + 250.0f), 0, ImVec2(0.5f, 0.5f));
            ImGui::BeginChild("##ShortSessionDone", ImVec2(300.0f, 300.0f));

            //positionnement du compteur de sessions
            float windowWidth = ImGui::GetWindowWidth();
            float windowHeigth = ImGui::GetWindowHeight();

            //calcul de la position centrale de la fenetre
            ImVec2 pause_size = ImGui::CalcTextSize(std::to_string(pauseCounter).c_str());
            ImVec2 pauseText_size = ImGui::CalcTextSize(u8"Nombre de \npauses effectuées");
            //calcul du vecteur de positionnement central de la fenetre
            ImVec2 pause_center = ImVec2((windowWidth - pause_size.x) / 2, (windowHeigth - pause_size.y) / 2);
            ImVec2 pauseText_center = ImVec2 ((windowWidth - pauseText_size.x) / 2, (windowHeigth - pauseText_size.y));
            ImGui::PushFont(font, 30.0f);
            ImGui::Text(u8"Nombre de \npauses effectuées");
            ImGui::PopFont();
            ImGui::PushFont(font, 40.0f);
            ImGui::SetCursorPos(pause_center);
            ImGui::Text("%d", pauseCounter);
            ImGui::PopFont();
            ImGui::EndChild();
        }

    } // namespace statistic
} // namespace App
