#include "../include/AppCore.h"
#include <windows.h>

int main (int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    SetConsoleOutputCP(CP_UTF8);
    
    //creation du coeur
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    App::core::AppCore Engine(1366.0f, 768.0f, "Minuteur Pomodoro", ImGui::GetIO());

    //initialisation du coeur
    if (!Engine.AppInitialised()) {
        std::cerr << "❌Echec de la creation du coeur de l'application" << std::endl;
        return 1;
    }
    Uint64 lastTime = SDL_GetTicks();
    //lancement du coeur de l'application
    Engine.AppRun(lastTime);

    //Arret propre de l'application
    Engine.AppSutdown();

    return 0;
}