#include "../../include/renderStats.h"

namespace App {
    namespace Statistic {
        void SessionDoneUi(ImFont* font,const char* counterSession) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();

            //section des sessions teminees
            ImGui::SetNextWindowPos(ImVec2(center.x - 350.0f, center.y + 150.0f), 0, ImVec2(0.5f, 0.5f));
            ImGui::BeginChild("##SessionDone", ImVec2(300, 200));

            //positionnement du compteur de sessions
            float windowWidth = ImGui::GetWindowWidth();
            float windowHeigth = ImGui::GetWindowHeight();
            ImVec2 text_size = ImGui::CalcTextSize(counterSession);

            //vecteurs de centre du compteur de sessions
            ImVec2 count_Center = ImVec2((windowWidth - text_size.x) / 2, (windowHeigth - text_size.y) / 2);

            ImGui::PushFont(font, 30.0f);
            ImGui::Text("   Sessions \nComplétées");
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
            

            //section du temps de comcentration effectue
            ImGui::SetNextWindowPos(ImVec2(center.x, center.y + 150.0f), 0, ImVec2(0.5f, 0.5f));
            ImGui::BeginChild("##ElapsedTime", ImVec2(300.0f, 200.0f));

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
            ImGui::SetNextWindowPos(ImVec2(center.x + 350.0f, center.y + 150.0f), 0, ImVec2(0.5f, 0.5f));
            ImGui::BeginChild("##ShortSessionDone", ImVec2(300.0f, 200.0f));

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

        void GlobalStatsWindow(SDL_Texture* texture, int Totalpause, int restPause, int longPause, int completed, int counter, ImFont* font, int Timecounter, bool& showStats) {
            float stats[] = {(float)Totalpause, (float)restPause, (float)longPause, (float)Timecounter, (float)completed};

            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(ImVec2(center.x - 558.0f, center.y - 384.0f));
            ImGui::SetNextWindowSize(ImVec2(1116.0f, 768.0f), ImGuiCond_Appearing);
            ImGui::OpenPopup("Global stats");
            if (ImGui::BeginPopupModal("Global stats", NULL, ImGuiWindowFlags_NoMove)) {
                //recuperation de la position centtrale de la fenetre de stats
                static ImVec2 midle = ImGui::GetMainViewport()->GetCenter();
                //positionnement de l'histogramme par rapport au centre de la fenetre de stats
                ImGui::SetCursorPosX(midle.x - 200.0f);
                ImGui::Image((ImTextureID)(intptr_t) texture, ImVec2(75.0f, 75.0f));
                ImGui::SameLine();
                ImGui::Text("Statistiques");
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(168 / 255.0f, 58.0f / 255.0f, 235.0f / 255.0f, 1.0f));
                ImGui::SetCursorPosX(midle.x - 500.0f);
                ImGui::PlotHistogram("##", stats, IM_ARRAYSIZE(stats), 0, NULL, 0.0f, 20.0f, ImVec2(0.0f, 300.0f));
                ImGui::PopStyleColor();
                SessionDoneUi(font, std::to_string(completed).c_str());
                ElapsedTimeUi(font, Timecounter);
                TotalPauseUi(font, Totalpause);
                ImGui::SetCursorPosX(midle.x - 250.0f);
                if (ImGui::Button("Fermer", ImVec2(250.0f, 65.0f))) {
                    showStats = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

        }

    } // namespace statistic
} // namespace App
