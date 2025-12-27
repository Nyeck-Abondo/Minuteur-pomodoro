#pragma once

#include "window.h"
#include "windowUI.h"

namespace App {
    namespace core {
        class AppCore {
        private:
            Graphics::window mwindow;
            Uigraphics::windowUi mwindowUi;
            backEnd::Timer mworkSession;
            backEnd::Timer mshortBreak;
            backEnd::Timer mLongbreak;
            //buffers
            const char mUserName[250];
            const char mObjectives[250];
            int mSessionNumber;
            int mLong_breakInterval;

        public:
            bool Get_started;
            bool show_statistics;
            bool show_parameters;

            //cpnstructeur et destructeur
            AppCore(float width, float height, std::string title);
            ~AppCore();

            //Lancement
            bool AppInitialised();
            void AppRun();

            //utilitaire
            void ParameterUi(int session_mumber, backEnd::Timer work, backEnd::Timer short_breakTime, backEnd::Timer long_BreakTime, int long_BreakInterval, int volume);
            void ProfileUi();
            void statisticsUi();
            void HelpUi();
            void SessionChange();

            //sous instances des fenetres secondaires
            void ThemeSettings();
            void TimeSettings();
        };
    }//namespace core
} //namespace App