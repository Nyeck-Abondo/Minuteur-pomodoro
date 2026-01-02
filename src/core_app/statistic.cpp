#include "../../include/statistic.h"

namespace App {
    namespace Statistic {
        stats::stats(): period({1 , 0}), rest({0, 0}) {}
        stats::~stats() {}

        void stats::StatisticInitialisation() {
            period.completed = 0;
            period.skiped = 0;
            rest.long_paused = 0;
            rest.short_paused = 0;
        }

        void stats::WorkSessionComplete(int& minutes, float& seconde) {
            if(minutes == 0 && seconde > 0.0f && seconde < 0.015f) {
                if (period.completed < 7) {
                    if (period.completed % 3 == 0 || period.completed == 0 || period.completed == 1) {
                        minutes = 0;
                        seconde = 3;
                        period.completed++;
                    }
                    else if (period.completed % 2 == 0 && period.completed % 4 != 0) {
                        minutes = 1;
                        seconde = 3;
                        period.completed++;
                    }
                    else if (period.completed % 4 == 0) {
                        minutes = 2;
                        seconde = 0;
                        period.completed++;
                        rest.long_paused++;
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
                if (period.completed % 4 == 0) {
                    rest.long_paused++;
                }
            }
        }

    } // namespace Statistic 
} // namespace App
