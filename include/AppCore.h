#pragma once

#include "window.h"
#include "windowUI.h"
#include "statistic.h"

#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))

namespace App {
    namespace core {
        class AppCore {
        private:
            Graphics::window mwindow;
            Uigraphics::windowUi mwindowUi;
            Statistic::stats mstatistics;
            backEnd::Timer mworkSession;
            backEnd::Timer mshortBreak;
            backEnd::Timer mLongbreak;

            int mSessionNumber;
            int mLong_breakInterval;
            int mvolume;
            int counter_session;

            //booleens  d'affichage
            bool mrunning = true;
            bool Get_started = false;
            bool show_statistics = false;
            bool show_parameters = false;
            bool show_interface = true;
            bool activate_sound = false;
            bool next_session = false;
            bool helper = false;

            //booleens de compteur pour les stats
            bool is_work_complete = false;
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

            void ParameterUi(int session_mumber, backEnd::Timer work, backEnd::Timer short_breakTime, backEnd::Timer long_BreakTime, int long_BreakInterval, int volume);
            void statisticsUi();
            void SessionChange(bool& change);

            //sous instances des fenetres secondaires
            void ThemeSettings();
            void TimeSettings();
            void SoundSettings();
            void SessionProgression();
        };
    }//namespace core
} //namespace App