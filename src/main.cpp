#include "../include/AppCore.h"
#include <windows.h>

int main (int arc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    
    //creation du coeur
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    App::core::AppCore Engine(1600.0f, 900.0f, "Minuteur Pomodoro", ImGui::GetIO());

    //initialia=sation du coeur
    if (!Engine.AppInitialised()) {
        std::cerr << "❌Echec de la creation du coeur de l'application" << std::endl;
        return 1;
    }

    //lancement du coeur de l'application
    Engine.AppRun();

    //Arret propre de l'application
    Engine.AppSutdown();

    return 0;
}