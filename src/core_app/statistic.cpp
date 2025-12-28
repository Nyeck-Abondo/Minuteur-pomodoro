#include "../../include/statistic.h"

namespace App {
    namespace Statistic {
        int workingTime(int minutes, bool work) {
            int past_time = 0;
            int current_minute = minutes;

            if (minutes <= current_minute && work) {
                current_minute = minutes;
                past_time++;
            }
            return past_time;
        }

        
    } // namespace statistic 
} // namespace App
