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

            //booleens  d'affichage
            bool mrunning = true;
            bool Get_started = false;
            bool show_statistics = false;
            bool show_parameters = false;
            bool show_interface = true;

            //booleens de gestion de l'app
            bool restart = false;
        public:
            

            //cpnstructeur et destructeur
            AppCore(float width, float height, std::string title, ImGuiIO& io);
            ~AppCore();

            //Lancement, initialisation , recuperation des events, presentation

            bool AppInitialised();
            void AppRun(Uint64 lastTime);
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
            * de travail de l'utilisateur. elle varie entre 5 et 60 minutes
            * @param short_breakTime durée des session de pause courtes.
            * elle varie entre 5 et 30 minutes.
            * @param long_BreakTime définition de la durée des longues
            * sessions de pause. Elle s'étend de 20 à 60 minutes.
            * @param long_BreakInterval defini une constente d'apparition des longues pauses.
            * elle peut varier entre 5 et 10.
            * @param volume permet la gestion du vokume du minuteur
            * @param theme permet de changer le theme en arriere plan de la'application
            * @return nothing
            */
            void ParameterUi();

            /**
             * @name statisticsUi
             * @brief Affichage de la fenetre des statistiques. ne prens aucun parametre
             * mais est cinstues de nombreuses methodes segmentant l'affichage de la stat 
             */
            void statisticsUi();

            /**
             * @name SessionRepresentaion
             * @brief affiche des minis icones representatives des sessions en cours
             * pour une meilleure comprehension de l'utilisateur
             * @param counterSession ce parametre represente le numero de la session
             * courante. ideal pour identifier la sesion dans laquelle se trouve l'utilisateur
             * et donc choisir l'icone appropriee.
             */
            void SessionRepresentaion(int counterSession);

            //sous instances des fenetres secondaires
            /**
             * @name ThemeSettings
             * @brief fenetre secondaire premettant le changement de theme dans l'application
             * ne nessessitant pas de sortir et s'occupant proprement de la destruction des 
             * textures precedantes.
             */
            void ThemeSettings();
        };
    }//namespace core
} //namespace App