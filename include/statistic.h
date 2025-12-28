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
        struct stats {
            int work_time;
            session period;
            paused rest;

            stats(): work_time(0), period({5 , 5}), rest({0, 0}) {}

            void workingTime(int minutes, bool work) {
                static int current_time = minutes;

                if (minutes < current_time && work) {
                    current_time = minutes;
                    work_time++;
                }
            }

            void WorkSessionComplete(int minutes, float seconde) {
                if(minutes == 0 && seconde > 0.0f && seconde < 0.02f) {
                    period.completed++;
                }
                
            }

            void ShortRestSessionDone(int minutes, float seconde) {
                if (minutes == 0 && seconde > 0.0f && seconde < 0.02f) {
                    rest.short_paused++;
                }
            }

            void LongRestSessionDonse(int minutes, float seconde) {
                if (minutes == 0 && seconde > 0.0f && seconde < 0.02f) {
                    rest.long_paused++;
                }
            }
        };
        
    } // namespace Statistic
} // namespace App
