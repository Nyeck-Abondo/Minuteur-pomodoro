#include <SDL3/SDL.h>
#include <SDL3/SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

int main() {
    //initialisation de la fenetre
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "erreur d'initialisation des paquets de SDL_INIT_VIDEO: " << SDL_GetError();
        return 1;
    }
    //initialisation des pacauets de SDL_ttf
    TTF_Init();
    //creation de la fentre
    SDL_Window* window = SDL_CreateWindow("TEST DE NOUVELLES POLLICES POUR LE PROJET🪧🗂️", 800, 600,0);
    if (!window) {
        std::cerr << "Echec de creatoin de la fentre: " << SDL_GetError();
        return 1;
    }
    //creation du moteur de rendu
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "echec de la creation du moteur de rendu: " << SDL_GetError();
        SDL_DestroyWindow(window);
        return 1;
    }
    //chargement de l'image de fond
    SDL_Surface* imgSurface = IMG_Load("assets/black_wallpaper.jpg");
    //creation de la texture
    SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    SDL_DestroySurface(imgSurface);
    
    //chargement de la police
    TTF_Font* font = TTF_OpenFont("police/MaterialSymbolsOutlined[FILL,GRAD,opsz,wght].ttf", 40);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, u8"\uE050", SDL_strlen(u8"\uE060"), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    float width;
    float height;
    SDL_GetTextureSize(texture, &width, &height);
    SDL_FRect dst = {740, 50, width, height};

    bool running =true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, imgTexture, nullptr, nullptr);
        SDL_RenderTexture(renderer, texture, nullptr, &dst);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(imgTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}