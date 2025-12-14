#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Texte SDL3", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Echec de la creation de la fenetre : " << SDL_GetError();
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "echec de l'initalisation du moteur de rendu: " << SDL_GetError();
    }

    //inmage de fond 
    SDL_Surface* imgSurface = IMG_Load("assets/img.jpg");
    if (!imgSurface) {
        std::cerr << "Echec de creation de la surface: " << SDL_GetError();
        return 1;
    }
    //creation de la texture de l'image
    SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    SDL_DestroySurface(imgSurface);

    // Charger une police
    TTF_Font* font = TTF_OpenFont("police/Montserrat/static/Montserrat-ExtraBoldItalic.ttf", 50);

    // Créer une surface texte
    SDL_Color color = {255, 255, 255, 255}; // blanc
    std::string chrono;
    int minutes = 00;
    int secondes = 05;
    SDL_Surface* surface = TTF_RenderText_Blended(font, "03:00",SDL_strlen("03:00"), color);

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
        //applocation de l'image de fond de l'application
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, imgTexture, nullptr, nullptr);

        //Variation du compteur: temps defini arbitrairement
        chrono = std::to_string(minutes) + " : ";
        chrono += std::to_string(secondes);
        if (secondes < 10) {
            chrono = std::to_string(minutes) + " : ";
            chrono += "0";
            chrono += std::to_string(secondes);
        }
        else if (minutes < 10) {
            chrono = "0" + std::to_string(minutes);
            chrono += " : ";
            chrono += std::to_string(secondes);
        }
        else if (minutes < 10 && secondes < 10) {
            chrono = "0" + std::to_string(minutes);
            chrono += " : ";
            chrono += std::to_string(secondes);
        }
        SDL_Surface* surface = TTF_RenderText_Blended(font, chrono.c_str(),SDL_strlen(chrono.c_str()), color);
        if (minutes > 0 || secondes > 0) {
            secondes -= 1;
        }
        
        //modification du compteur apres une minute et de secondes
        if (secondes <= 0 && minutes > 0){
            minutes -= 1;
            secondes = 59;
        }
        
        // Convertion de la durface en texture
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        SDL_GetTextureSize(texture, &w, &h);
        SDL_FRect dst = {300, 300, w, h};

        //affichage des textures
        SDL_RenderTexture(renderer, texture, nullptr, &dst);

        

        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(texture);
        SDL_Delay(1000);
    }

    //nettoyage (je suis bien élevé)
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(imgTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
