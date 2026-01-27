#include "../include/AppCore.h"
namespace App {
    namespace core {
        //constructeur
        AppCore::AppCore(float width, float height, std::string title, ImGuiIO& io): mwindow(height, width, title), mwindowUi(25.0f, io)
            , mstatistics() , Session(0, 5), mtonality("assets/musique/short-beep-tone-47916.mp3","assets/musique/tiktok_ding_tone3_kofi_by_miraclei-360025.mp3",
            "assets/musique/tap-notification-180637.mp3", "assets/musique/button_09-190435.mp3", "assets/musique/electronic-hit-98242.mp3") {
            std::cout << "🧰 Creation du coeur de l'application reussie avec succes !!" << std::endl;
        }

        AppCore::~AppCore() { 
            std::cout << "🏗️ Destruction du coeur de l'application." <<std::endl;
        }

        void AppCore::AppRun(Uint64 lastTime) {
            while (mrunning) {
                handleEvent();
                //recuperationd e l'instant present
                Uint64 now = SDL_GetTicks();
                //calcul de la variation
                Uint64 deltaTime = now - lastTime;
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
                chrono.WorkPresentation(mwindowUi.GettextureUI().work);
                chrono.restPresentation(mwindowUi.GettextureUI().restTexture);
                chrono.LongRestPresentation(mwindowUi.GettextureUI().chronoTexture);

                ImGui::EndChild();

                //gestion de la reprise a zero
                if (restart) {
                    mstatistics.StatisticInitialisation();
                    Session.InitialiseTimer(0, 3);
                    chrono.ResetMoveNotificationParameters();
                    restart = false;
                }

                //calcul des statistiques
                mstatistics.ShortRestSessionDone(Session.minutes, Session.secondes, mstatistics.GetPeriod());
                mstatistics.WorkSessionComplete(Session.minutes, Session.secondes, chrono.GetSessionNumber(), chrono.GetWorkMinutes(), chrono.GetWorkSecondes(), chrono.GetRestMinutes(),
                                                chrono.GetRestSecondes(), chrono.GetLonRestMinutes(), chrono.GetLongRestSecondes());
                //explication d'entree de jeu
                static int count = 0;
                if (count <= 500) count++;
                if (count < 500) {
                    chrono.Explanations(mstatistics.GetPeriod(), deltaTime, mwindow.mCurrenTheme);
                }
                //test fenetre globale de statistics
                if (mstatistics.GetPeriod() == chrono.GetSessionNumber() && Session.minutes == 0 && Session.secondes <= 0.4f && Session.secondes >= 0.20f) { 
                    show_statistics = true;
                }
                
                //fenetres des stats
                if (show_statistics) {
                    Statistic::GlobalStatsWindow(mwindowUi.GettextureUI().statistics, mstatistics.GetPause().total_restDone, mstatistics.GetPause().short_paused,
                                                mstatistics.GetPause().long_paused, mstatistics.GetPeriod(), mwindowUi.GetFontUi(),
                                                Session.timeCounter, show_statistics);
                }
                
                //fenetre des chronometres
                ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                ImGui::SetNextWindowPos(ImVec2(center.x + 90.0f, center.y), 0, ImVec2(0.5, 0.55));
                ImGui::BeginChild("##chrono01", ImVec2(650.0f, 500.0f), ImGuiChildFlags_None, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);

                if (Get_started) {
                    //calcul du temps restant
                    Session.timeleft();
                }
                
                //insrtion de l'image representative de la session
                SessionRepresentaion(mstatistics.GetPeriod(), deltaTime);

                //ajout du bouton de lancement
                ImGui::SetCursorPos(ImVec2(340.0f, 355.0f));
                if (ImGui::ImageButton("start", (ImTextureID)(intptr_t) mwindowUi.GettextureUI().pause, ImVec2(70.0f, 70.0f))) {
                    Get_started = true;
                }
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

                chrono.SessionNotification(Session.minutes, Session.secondes, mstatistics.GetPeriod(),mwindow.mCurrenTheme, mwindowUi.GettextureUI().darkNotification,
                                            mwindowUi.GettextureUI().blueNotification, mwindowUi.GettextureUI().yellowNotification, mwindowUi.GetFontUi(), lastTime,
                                            mwindowUi.GetAnimPicture(), mwindowUi.GetAnimTextureUI());

                //fenetre des parametres
                if (show_parameters) {
                    ParameterUi();
                    show_statistics = false;
                }
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

            //mwindowUi.igThemeV3(7, 7, 7, 0, 0, 1, 1);
            Uigraphics::UiStyleOrange();
            //statistiques a zero
            mstatistics.StatisticInitialisation();

            mwindow.ChangePrincipalTheme(mwindow.mCurrenTheme);
            std::cout << "initialisation des statistiques a 0" <<std::endl;

            if (!chrono.AnimationInitialised(mwindow.GetRenderer())) {
                std::cout << "❌ Echec de chargement des Gifs de presentation" << std::endl;
                return false;
            }

            //chargement des textures des icones
            mwindowUi.CreateUITexture(mwindow.GetRenderer());
            if (!mwindowUi.Load_animatedTexture(mwindow.GetRenderer())) {
                std::cout << "❌ Echec de chargement des Gifs animés" << std::endl;
                return false;
            }

            return true;
        }

        void AppCore::AppSutdown() {
            chrono.AnimationShutdown();
            mwindowUi.ShutdownUI();
            mwindow.ShutdownWindow();
            std::cout << "🛠️ Arret du moteur de l'application !!" <<std::endl;
        }

        void AppCore::ParameterUi() {
            ImGui::SetNextWindowPos(ImVec2(280.0f, 340.0f), 0, ImVec2(0, 0.55f));
            ImGui::BeginChild("##parameter", ImVec2(500, 600), 0, 0);

            //gestion du son de l'application
            chrono.SoundSettings();
            //parametre de temps
            chrono.TimeSettings();
            //parametre de choix de theme d'arriere plan
            ThemeSettings();
            //image de parametre
            ImGui::SetCursorPos(ImVec2(200.0f, 450.0f));
            ImGui::Image((ImTextureID)(intptr_t)mwindowUi.GettextureUI().settingsTexture, ImVec2(100.0f, 100.0f));
            
            ImGui::EndChild();
        }

        /**
         * @name ThemeSettings
         * @brief Cette fonction cree un combo qui explicite et permet le
         * choix du theme en arriere plan de l'application.
         */
        void AppCore::ThemeSettings() {
            //changement des themes dans le parametrage avec un combo
            const char* mTheme [] = {"Dark light theme-02", "Dark theme", "Dark light theme", "Orange Theme"};
            static int current_item_id = 3;
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

                            case 3:
                                mwindow.mCurrenTheme = backEnd::OfficialTheme::ORANGE_THEME;
                                mwindow.ChangePrincipalTheme(mwindow.mCurrenTheme);
                                SDL_RenderTexture(mwindow.GetRenderer(),mwindow.GetWindowTexture(), nullptr, nullptr);
                            break;
                        }
                    }
                }
                ImGui::EndCombo();            
            }
        }

        void AppCore::SessionRepresentaion(int counterSession, Uint64 deltaTime) {
            if (counterSession == 0) {
                ImGui::SetCursorPos(ImVec2(340.0f, 130.0f));
                chrono.PlayAnimation(deltaTime, ImVec2(70.0f, 70.0f), mwindow.mCurrenTheme);
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