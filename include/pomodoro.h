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
            
            Statistic::stats m_statisitcs;
            ImGuiToggleConfig config;

            //gestions des sessions
            int m_Workminuttes;
            int m_WorkSecondes;
            int m_RestMinutes;
            int m_RestSeconeds;
            int m_LongRest_Minutes;
            int m_LongRest_Secondes;
            int m_Volume;
            int m_SessionNumber;

            //booleens d'affichage
            bool m_Activate_Sound;
            bool m_Is_restSession;
            bool m_Is_workSession;
            bool m_Is_LongRestSession;
            
            public:
            //constructeur et destructeur
            pomodoro();
            ~pomodoro();

            //GETTERS
            bool GetIsWorkingSession() { return m_Is_workSession; }
            bool GetIsRestSession() { return m_Is_restSession;}
            bool GetIsLongRestSession() { return m_Is_LongRestSession; }
            int GetWorkMinutes() { return m_Workminuttes; }
            int GetWorkSecondes() { return m_WorkSecondes; }
            int GetRestMinutes() { return m_RestMinutes; }
            int GetRestSecondes() { return m_RestSeconeds; }
            int GetLonRestMinutes() { return m_LongRest_Minutes; }
            int GetLongRestSecondes() { return m_LongRest_Secondes; }
            int GetSessionNumber() { return m_SessionNumber; }

            //METHODES
            //parametre
            void TimeSettings();
            void SoundSettings();
            float totalTimeToDo(int counterSession);

            //presentation de l'evolution du chrono et effets visuels
            void WorkPresentation(SDL_Texture* texture);
            void restPresentation(SDL_Texture* texture);
            void LongRestPresentation(SDL_Texture* texture);

            //transition de session
            void Explanations(int counterSession, backEnd::textureUi texture);
            void SessionChange(int counterSession, backEnd::textureUi texture);          
            ImVec2 CenterContent();
        };
    } // namespace core
    
} // namespace App
