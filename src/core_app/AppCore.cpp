#include "../include/AppCore.h"
#include "libs/fmod/fmod.h"
namespace App {
    namespace core {
        //constructeur
        AppCore::AppCore(float width, float height, std::string title): mwindow(height, width, title), mwindowUi(width, height, 28.0f, ImGui::GetIO())
                        , mworkSession(20, 0.0f), mshortBreak(5, 0), mLongbreak(15, 0.0f), mSessionNumber(5), mLong_breakInterval(2), mUserName("Nom")
                        , mObjectives("Objectifs") {}

        /**
         * @name parameterUi
         * @brief cette fontion est chargée d'afficher les options de parametrage de
         * l'application. elle comprend les reglages de volumes, les reglages des 
         * sessions de temps de travail et de repos, le nombre d'intervalle de repos
         * long
         * 
         * @param session_number nombre de session pomodoro
         * ou encore connu sous le nom de session de concentration
         * @param workinTime regulation du temps
         * de travail de l'utilisateur. elle varien entre 5 et 60 minutes pour assurer
         * une concentration optimale
         * @param short_breakTime durée des session de pause courtes.
         * elle varie entre 5 et 30 minutes, selon la convenance de l'utilisateur.
         * @param long_BreakTime définition de la durée des longues
         * sessions de pause. Elle s'étend de 20 à 60 minutes selon les préférences de lùutilisateur
         * @param long_BreakInterval defini une constente d'apparition des longues pauses.
         * elle peut varier entre 5 et 10. ces chiffres représentant le nombre de session pomodoro
         * repos court.
         * @param volume permet la gestion du vokume du minuteur
         * @param theme permet de changer le theme en arriere plan de la'application
         * @return nothing
         */
        void AppCore::ParameterUi(int session_mumber, backEnd::Timer work, backEnd::Timer short_breakTime, backEnd::Timer long_BreakTime, int long_BreakInterval, int volume) {
            ImGui::SetNextWindowPos(ImVec2(251.0f, 400.0f), 0, ImVec2(0, 0.75f));
            ImGui::BeginChild("##parameter", ImVec2(500, 600), 0, ImGuiWindowFlags_Modal);

            //gestion du son de l'application
            ImGui::SeparatorText("Son");
            ImGui::Text("Volume");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::SliderInt(" ", &volume, 0, 100);
            ImGui::Text("Son actif");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::Toggle(" ", &mwindowUi.activate_sound, ImGuiToggleFlags_Animated);
            //parametre de choix de theme d'arriere plan
            ThemeSettings();
            
            
            ImGui::SetCursorPos(ImVec2(250.0f - 100, 300.0f - 100.0f));
            ImGui::Image((ImTextureID)(intptr_t)mwindowUi.GettextureUI().settingsTexture, ImVec2(200, 200));    

            ImGui::EndChild();
        }

        /**
         * @name ThemeSettings
         * @brief Cette fonction cree un combo qui explicite et permet le
         * choix du theme en arriere plan de l'application.
         */
        void AppCore::ThemeSettings() {
            //changement des themes dans le parametrage avec un combo
            const char* mTheme [] = {"Blue Theme", "Purple Theme", "Dark Light", "AOT Theme"};
            int current_item_id = 0;
            //ici on verra Blue Theme en ouvrant le combo
            const char* preview_value = mTheme[current_item_id];

            ImGui::SeparatorText("Theme de lapplication");
                if(ImGui::BeginCombo("Theme", preview_value, ImGuiComboFlags_HeightLarge)) {

                    for (int i; i < IM_ARRAYSIZE(mTheme); i++) {
                    const bool selected = (current_item_id == i);
                    if (ImGui::Selectable(mTheme[i], selected)){
                        current_item_id = i;
                        
                    }
                    //on met un focus sur l'objet actuel
                    if (selected) {
                        ImGui::SetItemDefaultFocus();
                        if (mwindow.GetWindowTexture()) {
                            SDL_DestroyTexture(mwindow.GetWindowTexture());
                        }
                        switch (i) {
                            case 0:
                                mwindow.mCurrenTheme = backEnd::OfficialTheme::BLUE_THEME;
                            break;
                            case 1:
                                mwindow.mCurrenTheme = backEnd::OfficialTheme::PURPLE_THEME;
                            break;
                            case 2:
                                mwindow.mCurrenTheme = backEnd::OfficialTheme::DARK_THEME;
                            break;
                            case 3:
                                mwindow.mCurrenTheme = backEnd::OfficialTheme::AOT_THEME;
                            break;
                        }
                        mwindow.ChangePrincipalTheme(mwindow.mCurrenTheme);
                    }
                }
                
                ImGui::EndCombo();
            }
        }
    } // namespace AppCore
} //namespace App

