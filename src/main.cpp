#include <SDL3/SDL.h>
#include <SDL3/SDL3_ttf/SDL_ttf.h>
#include <string>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Texte SDL3", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    // Charger une police
    TTF_Font* font = TTF_OpenFont("police/Montserrat/static/Montserrat-ExtraBoldItalic.ttf", 50);

    // Créer une surface texte
    SDL_Color color = {255, 255, 25, 255}; // blanc
    std::string chrono;
    int minutes = 20;
    int secondes = 60;
    SDL_Surface* surface = TTF_RenderText_Blended(font, "20:00",SDL_strlen("20:00"), color);

    // Convertir en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Récupérer dimensions
    float w, h;
    SDL_GetTextureSize(texture, &w, &h);
    SDL_FRect dst = {300, 300, w, h};

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        //Variation du compteur: temps defini arbitrairement
        chrono = std::to_string(minutes) + " : ";
        chrono += std::to_string(secondes);
        SDL_Surface* surface = TTF_RenderText_Blended(font, chrono.c_str(),SDL_strlen(chrono.c_str()), color);
        secondes -= 0.0002;
        //modification du compteur apres une minute
        if (secondes <= 0){
            minutes -=0.0002;
            secondes = 60;
        }
        
        // Convertion de la durface en texture
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        SDL_GetTextureSize(texture, &w, &h);
        SDL_FRect dst = {300, 300, w, h};

        //dessin remplissage de la fenetre avec la couleur verte
        SDL_SetRenderDrawColor(renderer, 20, 130, 0, 255);
        SDL_RenderClear(renderer);

        //affichage des textures
        SDL_RenderTexture(renderer, texture, nullptr, &dst);

        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(texture);
        SDL_Delay(1000);
    }

    //nettoyage (je suis bien élevé)
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
