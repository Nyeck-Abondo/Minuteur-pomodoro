#include "statistic.h"
#include "../libs/imgui/imgui.h"
#include "../libs/SDL3/SDL.h"
#include "../libs/imgui/imgui.h"

namespace App {
    namespace Statistic {
        
        void SessionDoneUi(ImFont* font,const char* counterSession);
        void ElapsedTimeUi(ImFont* font, int counterSession);
        void TotalPauseUi(ImFont* font, int pauseCounter);
        
    } // namespace Statistic
} // namespace App
