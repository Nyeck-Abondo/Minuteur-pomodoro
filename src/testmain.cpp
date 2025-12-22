#include "../include/window.h"

int main() {
    App::Graphics::window window(900.0f, 1600.0f, "chrono pomodoro");
    if(window.InitialiseWindow() == false) {
        std::cerr <<"Erreur de creation de la fenetre toute entiere!"<<std::endl;
        return 1;
    }
    window.mCurrenTheme = App::backEnd::backGround::BLUE_THEME;
    window.SpawnRandomParticles();
    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        window.CreateDeign(window.mCurrenTheme);
        window.PresentWindow();
        SDL_Delay(15);
    }
    window.ShutdownWindow();
    return 0;
}