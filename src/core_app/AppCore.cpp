#include "../include/AppCore.h"
namespace App {
    namespace core {
        //constructeur
        AppCore::AppCore(float width, float height, std::string title, ImGuiIO& io): mwindow(height, width, title), mwindowUi(28.0f, io)
        , mworkSession(20, 0.0f), mshortBreak(5, 0), mLongbreak(15, 0.0f), mSessionNumber(5), mLong_breakInterval(2), mstatistics(), mvolume(50) {
            std::cout << "🧰 Creation du coeur de l'application reussie avec succes !!" << std::endl;
        }

        AppCore::~AppCore() { 
            std::cout << "🏗️ Destruction du coeur de l'application." <<std::endl;
        }

        void AppCore::AppRun() {
            while (mrunning) {
                handleEvent();
                ImGui_ImplSDLRenderer3_NewFrame();
                ImGui_ImplSDL3_NewFrame();
                ImGui::NewFrame();

                ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), 0, ImVec2(0.5f, 0.5f));
                ImGui::SetNextWindowSize(ImVec2(mwindow.GetWindowWidth(), mwindow.GetWindowHeight()));
                ImGui::Begin("Minuteur Pomodoro", &show_interface, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

                ImGui::BeginChild("##Tools barr", ImVec2(250.0f, 900.0f));

                ImGui::Selectable("Parametre", &show_parameters, 0, ImVec2(250.0f, 100.0f));
                ImGui::Selectable("Statistique", show_statistics, 0, ImVec2(250.0f, 100.0f));

                ImGui::EndChild();

                ImGui::End();
                //presentation du rendu de l'application
                AppPresent();
            }
        }

        void AppCore::handleEvent() {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL3_ProcessEvent(&event);
                if(event.type == SDL_EVENT_QUIT) {
                    mrunning = false;
                }
            }
        }

        void AppCore::AppPresent() {
            ImGui::Render();
            SDL_RenderTexture(mwindow.GetRenderer(), mwindow.GetWindowTexture(), nullptr, nullptr);
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), mwindow.GetRenderer());
            mwindow.PresentWindow();
            SDL_Delay(15);
        }

        bool AppCore::AppInitialised() {
            if (!mwindow.InitialiseWindow()) {
                std::cout << "❌ Erreur de creation de la fentre de l'application." <<std::endl;
                return false;
            }
            std::cout <<"✅ creation de la fentre de l'application reussie !!" <<std::endl;

            mwindowUi.InitializeUi(mwindow.GetRenderer(), mwindow.GetWindowSDL());
            std::cout <<"✅ creation de la fenetre ImGui de l' application !" <<std::endl;

            mwindowUi.igThemeV3(7, 7, 7, 0, 0, 1, 1);

            //statistiques a zero
            mstatistics.work_time = 0;
            mstatistics.period.completed = 0;
            mstatistics.period.skiped = 0;
            mstatistics.rest.long_paused = 0;
            mstatistics.rest.short_paused = 0;

            mwindow.ChangePrincipalTheme(mwindow.mCurrenTheme);
            std::cout << "initialisation des statistiques a 0" <<std::endl;

            return true;
        }

        void AppCore::AppSutdown() {
            mwindowUi.ShutdownUI();
            if(mwindow.Initialised()) mwindow.ShutdownWindow();
            std::cout << "🛠️ Arret du moteur de l'application !!" <<std::endl;
        }

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
            SoundSettings();
            //parametre de choix de theme d'arriere plan
            ThemeSettings();
            //parametrage du temps des sessions
            
            ImGui::SetCursorPos(ImVec2(250.0f - 100, 300.0f - 100.0f));
            ImGui::Image((ImTextureID)(intptr_t)mwindowUi.GettextureUI().settingsTexture, ImVec2(200, 200));    

            ImGui::EndChild();
        }

        void  AppCore::SoundSettings() {
            ImGui::SeparatorText("Son");
            ImGui::Text("Volume");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::SliderInt(" ", &mvolume, 0, 100);
            ImGui::Text("Son actif");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::Toggle(" ", &activate_sound, ImGuiToggleFlags_Animated);
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

        void AppCore::statisticsUi(bool& show) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();

            //section des sessions teminees
            ImGui::SetNextWindowPos(ImVec2(center.x - 250.0f, center.y), 0, ImVec2(0.5f, 0.5f));
            ImGui::BeginChild("##SessionDone", ImVec2(200, 300), ImGuiChildFlags_AlwaysAutoResize);
            ImGui::Text("Sessions Complétées");
            ImGui::Text("%s",std::to_string(mstatistics.work_time).c_str());
            ImGui::EndChild();

            //section des sessions sautees
            ImGui::SetNextWindowPos(center, 0, ImVec2(0.5f, 0.5f));
            ImGui::BeginChild("##periodSKiped", ImVec2(200.0f, 300.0f), ImGuiChildFlags_AlwaysAutoResize);
            ImGui::Text("sessions Sautées");
            ImGui::Text("%s",std::to_string(mstatistics.period.skiped).c_str());
            ImGui::EndChild();
        }
    } // namespace AppCore
} //namespace App

