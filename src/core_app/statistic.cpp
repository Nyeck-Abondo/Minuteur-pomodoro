#include "../../include/statistic.h"

namespace App {
    namespace Statistic {
        stats::stats(): completed(0), rest({0, 0}) {}
        stats::~stats() {}

        void stats::StatisticInitialisation() {
            completed = 0;
            rest.long_paused = 0;
            rest.short_paused = 0;
            rest.total_restDone = 0;
        }

        void stats::WorkSessionComplete(int& minutes, float& seconde, int sessionNumber,int workminute,int workseconde, int restminute, int restseconde, int longRestMinutes, int longRestSecondes) {
            if(minutes == 0 && seconde > 0.0f && seconde < 0.015f) {
                if (completed < sessionNumber) {
                    completed++;
                    if (completed == 1) {
                        minutes = workminute;
                        seconde = workseconde;
                        
                    }
                    else if (completed % 2 != 0) {
                        minutes = workminute;
                        seconde = workseconde;
                    }
                    else if ((completed % 2 == 0) && (completed % 4 != 0)) {
                        minutes = restminute;
                        seconde = restseconde;
                        rest.short_paused++;
                        rest.total_restDone++;
                    }
                    else if (completed % 4 == 0) {
                        minutes = longRestMinutes;
                        seconde = longRestSecondes;
                        rest.long_paused++;
                        rest.total_restDone++;
                    }
                }
            }
        }

        void stats::ShortRestSessionDone(int minutes, float seconde, int countSession) {
            if(minutes == 0 && seconde > 1.0f && seconde <= 1.015f) {
                if (countSession % 2 == 0 && countSession % 4 != 0) {
                    rest.short_paused++;
                }
            }
        }

        void stats::LongRestSessionDonse(int minutes, float seconde) {
            if (minutes == 0 && seconde > 1.0f && seconde <= 1.015f) {
                if (completed % 4 == 0) {
                    rest.long_paused++;
                }
            }
        }

    } // namespace Statistic 
} // namespace App
