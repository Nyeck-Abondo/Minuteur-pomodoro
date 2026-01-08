#pragma once

#include "window.h"
#include "windowUI.h"
#include "statistic.h"
#include "pomodoro.h"
#include "renderStats.h"

namespace App {
    namespace core {
        class AppCore {
        private:
            Graphics::window mwindow;
            Uigraphics::windowUi mwindowUi;
            Statistic::stats mstatistics;
            pomodoro chrono;
            backEnd::Timer Session;

            int mSessionNumber;
            int mLong_breakInterval;
            int mvolume;

            //booleens  d'affichage
            bool mrunning = true;
            bool Get_started = false;
            bool show_statistics = false;
            bool show_parameters = false;
            bool show_interface = true;

            //booleens de compteur pour les stats
            bool is_work_complete = true;
            bool is_short_pause_done = false;
            bool is_long_pause_done = false;

            //booleens de gestion de l'app
            bool restart = false;
        public:
            

            //cpnstructeur et destructeur
            AppCore(float width, float height, std::string title, ImGuiIO& io);
            ~AppCore();

            //Lancement, initialisation , recuperation des events, presentation

            bool AppInitialised();
            void AppRun();
            void handleEvent();
            void AppSutdown();
            void AppPresent();

            //utilitaire

            void ParameterUi(int session_mumber, backEnd::Timer work, int long_BreakInterval, int volume);
            void statisticsUi();
            void SessionRepresentaion(int counterSession);

            //sous instances des fenetres secondaires
            void ThemeSettings();
        };
    }//namespace core
} //namespace App