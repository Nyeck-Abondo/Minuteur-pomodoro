#include "../include/AppCore.h"
namespace App {
    namespace core {
        //constructeur
        AppCore::AppCore(float width, float height, std::string title, ImGuiIO& io): mwindow(height, width, title), mwindowUi(25.0f, io), counter_session(1)
        ,Session(0, 3) , mSessionNumber(5), mLong_breakInterval(2), mstatistics(), mvolume(50) {
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
                
                //fenetre imgui principale
                ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), 0, ImVec2(0.5f, 0.5f));
                ImGui::SetNextWindowSize(ImVec2(mwindow.GetWindowWidth() + 50, mwindow.GetWindowHeight() + 50));
                ImGui::Begin("Minuteur Pomodoro", &show_interface, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

                ImGui::PushFont(mwindowUi.GetFontUi(), mwindowUi.GetFontSize());
                ImGui::BeginChild("##Tools barr", ImVec2(350.0f, ImGui::GetWindowHeight()), 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse);
                ImGui::SameLine();
                ImGui::Selectable("Parametre", &show_parameters, 0, ImVec2(350.0f, 100.0f));
                ImGui::Selectable("Statistique", &show_statistics, 0, ImVec2(350.0f, 100.0f));
                ImGui::Selectable("Get Started", &Get_started, 0, ImVec2(350.0f, 100.0f));
                ImGui::Selectable("Restart", &restart, 0, ImVec2(350.0f, 100.0f));
                chrono.WorkPresentation(mwindowUi.GettextureUI().work, Session);
                chrono.restPresentation(mwindowUi.GettextureUI().restTexture, Session);
                chrono.LongRestPresentation(mwindowUi.GettextureUI().chronoTexture, Session);

                ImGui::EndChild();
                //calcul des statistiques
            mstatistics.ShortRestSessionDone(Session.minutes, Session.secondes, mstatistics.GetPeriod().completed);
                //explication d'entree de jeu
                static int count = 0;
                if (count <= 500) count++;
                if (count < 500) {
                    chrono.Explanations(mstatistics.GetPeriod().completed, mwindowUi.GettextureUI());
                }
                
                //fenetre des parametres
                if (show_parameters) {
                    ParameterUi(mSessionNumber, Session, mLong_breakInterval, mvolume);
                    show_statistics = false;
                }
                //fenetres des stats
                statisticsUi();

                //fenetre des chronometres
                ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                ImGui::SetNextWindowPos(ImVec2(center.x + 90.0f, center.y), 0, ImVec2(0.5, 0.55));
                ImGui::BeginChild("##chrono01", ImVec2(650.0f, 500.0f), ImGuiChildFlags_None, ImGuiWindowFlags_NoBackground);

                //met a jour l'état du chronometre pour quùil s'adapte en fonction de la session actuelle
                Session.updateTimer(mstatistics.GetPeriod().completed);
                if (Get_started) {
                    //calcul du temps restant
                    Session.timeleft();
                }
                
                //affichage du chronometre
                ImGui::PushFont(mwindowUi.GetFontUi(), 150.0f);
                ImGui::Text("%s", Session.chrono);
                ImGui::PopFont();
                //progression des sessions
                ImGui::EndChild();
                ImGui::PopFont();
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
            mstatistics.StatisticInitialisation();

            mwindow.ChangePrincipalTheme(mwindow.mCurrenTheme);
            std::cout << "initialisation des statistiques a 0" <<std::endl;

            //chargement des textures des icones
            mwindowUi.CreateUITexture(mwindow.GetRenderer());

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
        void AppCore::ParameterUi(int session_mumber, backEnd::Timer work, int long_BreakInterval, int volume) {
            ImGui::SetNextWindowPos(ImVec2(251.0f, 400.0f), 0, ImVec2(0, 0.55f));
            ImGui::BeginChild("##parameter", ImVec2(500, 600), 0, ImGuiWindowFlags_Modal);

            //gestion du son de l'application
            chrono.SoundSettings();
            //parametre de temps
            chrono.TimeSettings(Session);
            //parametre de choix de theme d'arriere plan
            ThemeSettings();
            //parametrage du temps des sessions
            
            ImGui::EndChild();
        }

        /**
         * @name ThemeSettings
         * @brief Cette fonction cree un combo qui explicite et permet le
         * choix du theme en arriere plan de l'application.
         */
        void AppCore::ThemeSettings() {
            //changement des themes dans le parametrage avec un combo
            const char* mTheme [] = {"Dark light theme-02", "Dark theme", "Dark light theme"};
            static int current_item_id = 0;
            //ici on verra Blue Theme en ouvrant le combo
            const char* preview_value = mTheme[current_item_id];

            ImGui::SeparatorText("Theme de lapplication");
            if(ImGui::BeginCombo("Theme", preview_value)) {

                for (int i = 0; i < IM_ARRAYSIZE(mTheme); i++) {
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
                                mwindow.mCurrenTheme = backEnd::OfficialTheme::DARK_LIGHT_THEME02;
                                mwindow.ChangePrincipalTheme(mwindow.mCurrenTheme);
                                SDL_RenderTexture(mwindow.GetRenderer(),mwindow.GetWindowTexture(), nullptr, nullptr);
                            break;

                            case 1:
                                mwindow.mCurrenTheme = backEnd::OfficialTheme::DARK_THEME;
                                mwindow.ChangePrincipalTheme(mwindow.mCurrenTheme);
                                SDL_RenderTexture(mwindow.GetRenderer(),mwindow.GetWindowTexture(), nullptr, nullptr);
                            break;
                            case 2:
                                mwindow.mCurrenTheme = backEnd::OfficialTheme::DARK_LIGHT_THEME;
                                mwindow.ChangePrincipalTheme(mwindow.mCurrenTheme);
                                SDL_RenderTexture(mwindow.GetRenderer(),mwindow.GetWindowTexture(), nullptr, nullptr);
                            break;
                        }
                    }
                }
                ImGui::EndCombo();            
            }
        }

        void AppCore::statisticsUi() {
            //calcul des sessions completes
            mstatistics.WorkSessionComplete(Session.minutes, Session.secondes);
            Statistic::SessionDoneUi(mwindowUi.GetFontUi(), std::to_string(mstatistics.GetPeriod().completed).c_str());
            Statistic::ElapsedTimeUi(mwindowUi.GetFontUi(), Session.timeCounter);
            Statistic::TotalPauseUi(mwindowUi.GetFontUi(), mstatistics.GetPause().short_paused);

        }

    } // namespace AppCore
} //namespace App