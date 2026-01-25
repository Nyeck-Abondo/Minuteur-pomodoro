#pragma once

#include "structs.h"
#include "statistic.h"
#include "../libs/imgui/imgui.h"
#include "../libs/ImGui_Arc_ProgressBar/arc_progress_bar.hpp"
#include "../libs/SDL3/SDL.h"
#include <cmath>

const double M_Pi =3.14159265358979323846;

namespace App {
    namespace core {
        
        class pomodoro {
            private:
            
            Statistic::stats m_statisitcs;
            IMG_Animation* mPresentation_Animation;
            IMG_Animation* mBlackPresentation_Animation;
            SDL_Texture** mPresentationTexture;
            SDL_Texture** mBlackPresentationTexture;

            //animation de point montant et descendant
            /*Uint64 frequenceWork;
            Uint64 frequenceRest;
            Uint64 frequenceLongRest;*/
            
            //compteur de frames
            int mcounterFrame;

            //facteurs de translation(angle)
            float m_Angle;
            float m_Angle02;
            //variable de deco;pte de temps
            int m_CounterDelay;
            int m_counterDelay02;
            bool m_notificationUp;
            bool m_notificationUp02;

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
            bool GetSoundAcive() { return m_Activate_Sound; }
            int GetWorkMinutes() { return m_Workminuttes; }
            int GetWorkSecondes() { return m_WorkSecondes; }
            int GetRestMinutes() { return m_RestMinutes; }
            int GetRestSecondes() { return m_RestSeconeds; }
            int GetLonRestMinutes() { return m_LongRest_Minutes; }
            int GetLongRestSecondes() { return m_LongRest_Secondes; }
            int GetSessionNumber() { return m_SessionNumber; }

            //METHODES
            //methodes relatives aux animations
            bool AnimationInitialised(SDL_Renderer* renderer);
            void AnimationShutdown();
            void PlayAnimation(Uint64 deltaTime, ImVec2 size, backEnd::OfficialTheme currentTeme);

            //parametre
            void TimeSettings();
            void SoundSettings();
            float totalTimeToDo(int counterSession);

            //presentation de l'evolution du chrono et effets visuels
            void WorkPresentation(SDL_Texture* texture);
            void restPresentation(SDL_Texture* texture);
            void LongRestPresentation(SDL_Texture* texture);
            //deplacement des fenetres de notification
            void MoveNotification(float &angle, bool &notificationUp, int &counterDelay);
            void ResetMoveNotificationParameters();
            void ResetMoveNotificationParametres02();
            void ResetMoveNotificationParameters01();
            //affichage des notifications
            void ManageNotification(SDL_Texture* texture, int counterSession, int minutes, float secondes, ImFont* font, ImVec2 sizeText);
            void ManageEndNotification(SDL_Texture* texture, int counterSession, int minutes, float secondes, ImFont* font, ImVec2 sizeText);

            //transition de session
            void Explanations(int counterSession, Uint64 deltaTime, backEnd::OfficialTheme currentTeme);
            void SessionNotification(int minutes, int secondes, int counterSession, backEnd::OfficialTheme currentTheme, SDL_Texture* texture, ImFont* font);
        };
    } // namespace core
    
} // namespace App
