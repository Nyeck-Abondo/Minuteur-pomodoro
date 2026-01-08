#pragma once

#include "structs.h"

namespace App {
    namespace Statistic {

        /**
         * @struct Session
         * @brief denombre le nombre de sessions achecvees et inachevee
         */
        struct session {
            int completed;
            int skiped;
        };

        /**
         * @struct paused
         * @brief denombre le nombre de pauses prises par l'utilisateur
         */
        struct paused {
            int long_paused;
            int short_paused;
        };

        /**
         * @struct Stats
         * @brief cette structure gere la sttistique l'application
         */
        class stats {
            private:
                session period;
                paused rest;

            public:
            stats();
            ~stats();

            //GETTERS
            session GetPeriod() { return period; }
            paused GetPause() { return rest; }

            //initialisation
            void StatisticInitialisation();

            void WorkSessionComplete(int& minutes, float& seconde, int workminute, int restminute, int longRestMinutes);
            void ShortRestSessionDone(int minutes, float seconde, int countSession);
            void LongRestSessionDonse(int minutes, float seconde);
        };
        
    } // namespace Statistic
} // namespace App
