#include "../include/window.h"
#include <windows.h>

int main() {
    SetConsoleCP(CP_UTF8);

    App::Graphics::window window(900.0f, 1600.0f, "chrono pomodoro");
    if(window.InitialiseWindow() == false) {
        std::cerr <<"Erreur de creation de la fenetre toute entiere!"<<std::endl;
        return 1;
    }
    window.mCurrenTheme = App::backEnd::backGround::PINK_THEME;
    window.SpawnRandomParticles();
    SDL_Event event;
    bool running = true;
    int time = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
       if ( time == 300){
        window.SpawnRandomParticles();
        time = 0;
       }
        window.CreateDeign(window.mCurrenTheme);
        window.PresentWindow();
        SDL_Delay(15);
        time++;
    }
    window.ShutdownWindow();
    return 0;
}