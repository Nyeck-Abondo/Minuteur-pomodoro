#include "../libs/imgui/imgui.h"
#include "../libs/imgui/backends/imgui_impl_sdl3.h"
#include "../libs/imgui/backends/imgui_impl_sdlrenderer3.h"
#include "../SDL3/SDL.h"
#include <iostream>
#include <iomanip>
#include <string>

void UIstyle();

struct Timer {
            unsigned int minutes : 6;
            float secondes;
            std::string timeremain;

            void timeleft() {
                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << secondes;
                timeremain = std::to_string(minutes) + " : ";
                timeremain += stream.str();
                if (minutes >= 0) {
                    secondes -= 0.015;
                }
                if (secondes < 0.01 && minutes > 0) {
                    minutes -= 1;
                    secondes = 60;
                }
                if (secondes < 10.0f) {
                    timeremain = std::to_string(minutes) + " : ";
                    timeremain += "0";
                    stream << std::fixed << std::setprecision(2) << secondes;
                    timeremain += stream.str();
                }
                if (minutes < 10) {
                    timeremain = "0" + std::to_string(minutes);
                    timeremain += " : ";
                    stream << std::fixed << std::setprecision(2) << secondes;
                    timeremain += stream.str(); 
                }
            }
        };

int main(int argc, char* argv[]) {
    //initialisation des paquets SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }

    //creation de la fenetre
    SDL_Window* window = SDL_CreateWindow("parameters ex02", 1200, 600, 0);
    //verification
    if (!window) {
        std::cerr << "Erreur de creation de la fenetre SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    //creation du moteur de rendu
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Echec de l'initialisation du moteur de rendu: " << SDL_GetError() << std::endl;
        return 1;
    }

    //outils et objet imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    UIstyle();
    ImFont* font = io.Fonts->AddFontFromFileTTF("police/Montserrat/static/Montserrat-Medium.ttf", 18.0f);
    //initialisation des pacquets imgui
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    //variables de la boucle de fenetre
    bool custom_window = true;
    bool running = true;
    bool parameters = true;
    bool profile = true;
    bool statistic = true;
    SDL_Event event;
    Timer chronometer = {20, 15};

    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        //calcul du temps
        chronometer.timeleft();

        //nouvelle frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        //affichage de la fenetre imgui
        if(custom_window) {
            ImGui::Begin("chrono pomodoro", &custom_window);

            ImGui::SetNextWindowSize(ImVec2(300, 300));
            ImGui::BeginChild("##onglet");
            ImGui::Button("Paramettre");
            ImGui::Button("profile");
            ImGui::SetCursorPos(ImVec2(100, 80));
            ImGui::Text("%s",chronometer.timeremain.c_str());
            ImGui::EndChild();

            ImGui::End();
            SDL_Delay(15);
        }
        //rendu
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer,32, 21, 36, 100);
        SDL_RenderClear(renderer);

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }
    //nettoyage
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void UIstyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.GrabRounding = 3.0f;
    style.WindowRounding = 3.0f;
    style.FrameRounding = 3.0f;
    style.WindowPadding = ImVec2(20, 20);

    ImVec4* color = style.Colors;
    color[ImGuiCol_ButtonHovered] = ImVec4(152.0f/255, 57.0f/255, 1.0f, 0.75f);
    color[ImGuiCol_Button] = ImVec4(221.0f, 219.0f, 1.0f, 0.75f);
    color[ImGuiCol_ChildBg] = ImVec4(64.0f/255, 36.0f/255, 69.0f/255, 0.95f);
}