#include "../include/AppCore.h"
namespace App {
    namespace core {
        //constructeur
        AppCore::AppCore(float width, float height, std::string title, ImGuiIO& io): mwindow(height, width, title), mwindowUi(25.0f, io)
        , mSessionNumber(5), mLong_breakInterval(2), mstatistics(), mvolume(50) {
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
                ImGui::SetNextWindowBgAlpha(0.75f);
                ImGui::BeginChild("##Tools barr", ImVec2(300.0f, ImGui::GetWindowHeight()), 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse);
                ImGui::Selectable("Parametre", &show_parameters, 0, ImVec2(300.0f, 100.0f));
                ImGui::Selectable("Statistique", &show_statistics, 0, ImVec2(300.0f, 100.0f));
                ImGui::Selectable("Get Started", &Get_started, 0, ImVec2(300.0f, 100.0f));
                ImGui::Selectable("Restart", &restart, 0, ImVec2(300.0f, 100.0f));
                chrono.WorkPresentation(mwindowUi.GettextureUI().work, Session);
                chrono.restPresentation(mwindowUi.GettextureUI().restTexture, Session);
                chrono.LongRestPresentation(mwindowUi.GettextureUI().chronoTexture, Session);

                ImGui::EndChild();
                //calcul des statistiques
                mstatistics.ShortRestSessionDone(Session.minutes, Session.secondes, mstatistics.GetPeriod());
                mstatistics.WorkSessionComplete(Session.minutes, Session.secondes, chrono.GetWorkMinutes(), chrono.GetWorkSecondes(), chrono.GetRestMinutes(),
                                                chrono.GetRestSecondes(), chrono.GetLonRestMinutes(), chrono.GetLongRestSecondes());
                //explication d'entree de jeu
                static int count = 0;
                if (count <= 100) count++;
                if (count < 100) {
                    chrono.Explanations(mstatistics.GetPeriod(), mwindowUi.GettextureUI());
                }
                
                //fenetre des parametres
                if (show_parameters) {
                    ParameterUi(mSessionNumber, Session, mLong_breakInterval, mvolume);
                    show_statistics = false;
                }
                //fenetres des stats
                if (show_statistics) {
                    statisticsUi();
                }
                
                //fenetre des chronometres
                ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                ImGui::SetNextWindowPos(ImVec2(center.x + 90.0f, center.y), 0, ImVec2(0.5, 0.55));
                ImGui::BeginChild("##chrono01", ImVec2(650.0f, 500.0f), ImGuiChildFlags_None, ImGuiWindowFlags_NoBackground);

                if (Get_started) {
                    //calcul du temps restant
                    Session.timeleft();
                }
                
                //insrtion de l'image representative de la session
                SessionRepresentaion(mstatistics.GetPeriod());
                //affichage du chronometre
                ImGui::PushFont(mwindowUi.GetFontUi(), 80.0f);
                ImGui::SetCursorPos(ImVec2(210.0f, 210.0f));
                ImGui::Text("%s", Session.chrono);
                ImGui::PopFont();
                ImGui::SetCursorPos(ImVec2(150.0f, 20.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(252.0f / 255.0f, 1.0f, 254.0f, 1.0f));
                ImGuiExt::ProgressBarArc(450.0f, 360, ((float)Session.minutes * 60 + Session.secondes) * 100.0f / chrono.totalTimeToDo(mstatistics.GetPeriod()), 25.0f);
                ImGui::PopStyleColor();
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

        void AppCore::ParameterUi(int session_mumber, backEnd::Timer work, int long_BreakInterval, int volume) {
            ImGui::SetNextWindowPos(ImVec2(251.0f, 400.0f), 0, ImVec2(0, 0.55f));
            ImGui::BeginChild("##parameter", ImVec2(500, 600), 0, ImGuiWindowFlags_Modal);

            //gestion du son de l'application
            chrono.SoundSettings();
            //parametre de temps
            chrono.TimeSettings();
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
            
            Statistic::SessionDoneUi(mwindowUi.GetFontUi(), std::to_string(mstatistics.GetPeriod()).c_str());
            Statistic::ElapsedTimeUi(mwindowUi.GetFontUi(), Session.timeCounter);
            Statistic::TotalPauseUi(mwindowUi.GetFontUi(), mstatistics.GetPause().total_restDone);

        }

        void AppCore::SessionRepresentaion(int counterSession) {
            if (counterSession == 0) {
                ImGui::SetCursorPos(ImVec2(340.0f, 130.0f));
                ImGui::Image((ImTextureID)(intptr_t) mwindowUi.GettextureUI().chronoTexture, ImVec2(70.0f, 70.0f));
            }
            else if (counterSession % 2 != 0 || counterSession == 1) {
                ImGui::SetCursorPos(ImVec2(340.0f, 130.0f));
                ImGui::Image((ImTextureID)(intptr_t) mwindowUi.GettextureUI().pompe, ImVec2(70.0f, 70.0f));
            }
            else if (counterSession % 2 == 0 && counterSession % 4 != 0) {
                ImGui::SetCursorPos(ImVec2(340.0f, 130.0f));
                ImGui::Image((ImTextureID)(intptr_t) mwindowUi.GettextureUI().coffee, ImVec2(70.0f, 70.0f));
            }
            else if (counterSession % 4 == 0) {
                ImGui::SetCursorPos(ImVec2(340.0f, 130.0f));
                ImGui::Image((ImTextureID)(intptr_t) mwindowUi.GettextureUI().restTexture, ImVec2(70.0f, 70.0f));
            }
        }

    } // namespace AppCore
} //namespace App