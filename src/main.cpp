#include <SDL3/SDL.h>
#include <SDL3/SDL3_ttf/SDL_ttf.h>
#include <string>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Texte SDL3", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    // Charger une police
    TTF_Font* font = TTF_OpenFont("Montserrat/Montserrat-VariableFont_wght.ttf", 50);

    // Créer une surface texte
    SDL_Color color = {255, 255, 255, 255}; // blanc
    std::string chrono;
    int minutes = 20, secondes = 60;
    SDL_Surface* surface = TTF_RenderText_Blended(font, "20:00",SDL_strlen("20:00"), color);

    // Convertir en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Récupérer dimensions
    float w, h;
    SDL_GetTextureSize(texture, &w, &h);
    SDL_FRect dst = {400, 300, (float)w, (float)h};

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        chrono = std::to_string(minutes) + " : ";
        chrono += std::to_string(secondes);
        SDL_Surface* surface = TTF_RenderText_Blended(font, chrono.c_str(),SDL_strlen(chrono.c_str()), color);
        secondes -= 0.0002;
        if (secondes <= 0){
            minutes -=0.0002;
            secondes = 60;
        }
        
        // Convertir en texture
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        // Récupérer dimensions
        SDL_GetTextureSize(texture, &w, &h);
        SDL_FRect dst = {400, 300, (float)w, (float)h};

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderTexture(renderer, texture, nullptr, &dst);

        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(texture);
        SDL_Delay(1000);
    }

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
