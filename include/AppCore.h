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
            void ParameterUi(int session_mumber, backEnd::Timer work, int long_BreakInterval, int volume);
            void statisticsUi();
            void SessionRepresentaion(int counterSession);

            //sous instances des fenetres secondaires
            void ThemeSettings();
        };
    }//namespace core
} //namespace App