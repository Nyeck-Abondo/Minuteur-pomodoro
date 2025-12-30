#include "structs.h"
#include "statistic.h"
#include "../libs/imgui/imgui.h"
#include "../libs/ImGui_Arc_ProgressBar/arc_progress_bar.hpp"
#include "../libs/SDL3/SDL.h"

#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))

namespace App {
    namespace core {
        
        class pomodoro {
            private:
            backEnd::Timer m_WorkChrono;
            backEnd::Timer m_RestChrono;
            backEnd::Timer m_LongRestChrono;
            Statistic::stats m_statisitcs;

            //gestions des sessions
            int m_CounterSession;
            int m_Volume;

            //booleens d'affichage
            bool m_Activate_Sound;
            bool m_NExt_Session;
            bool m_Is_restSession;
            bool m_Is_workSession;
            bool m_Is_LongRestSession;
            
            public:

            //constructeur et destructeur
            pomodoro();
            ~pomodoro();

            //METHODES
            //parametre
            void TimeSettings();
            void SoundSettings();
            void SessionProgression();

            //presentation de l'evolution du chrono et effets visuels
            void Chronometer();
            void WorkSessionPresentation();
            void RestSessionPresentation();
            void LongRestsessionPresentation();

        };
    } // namespace core
    
} // namespace App
