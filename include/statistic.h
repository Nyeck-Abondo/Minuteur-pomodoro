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

            stats(): work_time(0), period({0 , 0}), rest({0, 0}) {}

            void workingTime(int minutes, bool work) {
                int current_time = minutes;

                if (minutes < current_time && work) {
                    current_time = minutes;
                    work_time++;
                }
            }

            void WorkSessionComplete(int minutes, bool finished) {
                if (minutes < 0 && finished) {
                    period.completed++;
                }
                else {
                    period.skiped++;
                }
            }

            void ShortRestSessionDone(int minutes, bool done) {
                if (minutes < 0 && done) {
                    rest.short_paused++;
                }
            }

            void LongRestSessionDonse(int minutes, bool done) {
                if (minutes < 0 && done) {
                    rest.long_paused++;
                }
            }
        };
        
    } // namespace Statistic
} // namespace App
