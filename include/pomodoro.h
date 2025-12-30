#include "structs.h"
#include "statistic.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui_toggle/imgui_toggle.h"
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
            ImGuiToggleConfig config;

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

            //GETTERS
            backEnd::Timer GetWorkingChrono() const { return m_WorkChrono; }
            backEnd::Timer GetRestChrono() const { return m_RestChrono; }
            backEnd::Timer GetLongChrono() const { return m_LongRestChrono; }
            bool GetIsWorkingSession() { return m_Is_workSession; }
            bool GetIsRestSession() { return m_Is_restSession;}
            bool GetIsLongRestSession() { return m_Is_LongRestSession; }
            int GetCounterSession() { return m_CounterSession;}

            //METHODES
            //parametre
            void TimeSettings();
            void SoundSettings();
            void SessionProgression();

            //presentation de l'evolution du chrono et effets visuels
            void WorkChronometer(bool is_session);
            void RestChronometer(bool is_session);
            void LongRestChronometer(bool is_session);
            void WorkSessionPresentation(SDL_Texture* texture);
            void RestSessionPresentation(SDL_Texture* texture);
            void LongRestsessionPresentation(SDL_Texture* texture);

            //transition de session
            void SessionChange(backEnd::textureUi texture);            

        };
    } // namespace core
    
} // namespace App
