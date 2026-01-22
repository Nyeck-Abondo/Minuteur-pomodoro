#include "../include/windowUI.h"
#include "../libs/SDL3/SDL.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h"

namespace App{
    namespace Uigraphics{
        /**
         * @name constructeur
         * @brief constructeur de la classe windowUi.
         * @param width represente la largeur de la fenetre ImGui
         * @param height represente la hquteur de la fenetre ImGui.
         * @param fontsize represente la taille de la police utilisee
         * par la fenetre ImGui pour l'ecriture du texte.
         * @param io represente l'objet.
         */
        windowUi::windowUi(float fontsize, ImGuiIO& io)
                : mStyle(ImGui::GetStyle()), Uifont(nullptr), mio(io),
                mtools({nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}),
                manimation({nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}), manimPicture({nullptr, nullptr,
                nullptr, nullptr, nullptr, nullptr}), mfontSize(fontsize), isInitialise(false) {
                    std::cout << "🛠️ cration de la fenetre imgui reussi !!"<<std::endl;
        }
         windowUi::~windowUi() {
            std::cout<<"destruction propre de imgui interface"<<std::endl;
        }

        /**
         * InitializeUi
         *  @brief- initialise la fenetre imgui
         * @param renderer correspond au moteur de rendu de la fenetre parent SDL
         * @param window correspond a la fenetre SDL elle meme(la variable qui 
         * prend en charge sa creation).
         * @return nothing. 
         */
        void windowUi::InitializeUi(SDL_Renderer* renderer, SDL_Window* window) {
            mio.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            mtoggleConfig.Flags |= ImGuiToggleFlags_Animated;
            Uifont = mio.Fonts->AddFontFromFileTTF("police/Montserrat/static/Montserrat-Black.ttf");
            //initialisation des paquet imgui
            ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
            ImGui_ImplSDLRenderer3_Init(renderer);
        }

        /**
         * @name ShutdownUI()
         * @brief -Ferme proprement la fentre imgui elle ne prend aucun parametre
         */
        void windowUi::ShutdownUI() {
            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
            //textures crees
            SDL_DestroyTexture(mtools.chronoTexture);
            SDL_DestroyTexture(mtools.profilTexture);
            SDL_DestroyTexture(mtools.restTexture);
            SDL_DestroyTexture(mtools.settingsTexture);
            SDL_DestroyTexture(mtools.soundTexture);
            SDL_DestroyTexture(mtools.statistics);
            SDL_DestroyTexture(mtools.work);
            SDL_DestroyTexture(mtools.coffee);
            SDL_DestroyTexture(mtools.pause);
            SDL_DestroyTexture(mtools.pompe);
        }

        /**
         * @name Load_imageTexture
         * @brief Permet la copie des pixels des images dans des textures a l'aide de la 
         * bibliotheque stb_image. elle est utilisée pour creer des texture pour les icones
         * de l'application.
         * @param renderer c'est le moteur de rendu de l'application, en charge d'appliquer 
         * les textures dans le decor de fond de la fenetre SDL
         * @param fileLocation chemin d'acces vers le fichier image  a charger dans la texture.
         * @return texture de type SDL_Texture* , c'est la textuer a afficher dans la fenetre de
         * rendu. 
         */
        SDL_Texture* windowUi::Load_imageTexture(SDL_Renderer* renderer, const char* fileLocation) {
            int width, height, channels;
            unsigned char* image_data = stbi_load(fileLocation, &width, &height, &channels, 4);
            //verification du chargement de l'image en memoire
            if (!image_data) {
                std::cerr << "Erreur de chargement de l'image: " << stbi_failure_reason() << std::endl;
                return nullptr;
            }
            std::cout << "image : "<< fileLocation << " taille : " << width << " x " << height << std::endl;
            std::cout << "😁 image : " << fileLocation << " chargée avec succes!" << std::endl; 
            //creation de la texutre
            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
            if (!texture) {
                std::cerr << "❌Erreur de creation de la texture: " << SDL_GetError() << std::endl;
                stbi_image_free(image_data);
                return nullptr;
            }
            //copie des pixel
            SDL_UpdateTexture(texture, nullptr, image_data, width * 4);
            //liberation de la memeoire
            stbi_image_free(image_data);
            return texture;
        }

        void windowUi::Load_animatedTexture(SDL_Renderer* renderer) {
            //chargement des animations (sont toutes des tableaux de surfaces)
            manimPicture.animationSP = IMG_LoadAnimation("assets/tools/Success (1).gif");
            manimPicture.animationSY = IMG_LoadAnimation("assets/tools/Success (2).gif");
            manimPicture.animationTY = IMG_LoadAnimation("assets/tools/Timer (1).gif");
            manimPicture.animationTB = IMG_LoadAnimation("assets/tools/Timer.gif");
            manimPicture.animationEXE = IMG_LoadAnimation("assets/tools/en-cours-dexecution.gif");
            manimPicture.animationGraph = IMG_LoadAnimation("assets/tools/analytique.gif");
            
            //annimation de success violette
            manimation.successPurple = new SDL_Texture* [manimPicture.animationSP->count];
            if (manimation.successPurple == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de succes violette !!" << std::endl;
            }
            std::cout << "✅ creation de la texture de succes violette !!" << std::endl;
            //convertion en texture
            for (int i = 0; i < manimPicture.animationSP->count; i++) {
                manimation.successPurple[i] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationSP->frames[i]);
            }

            //animation de succes du theme jaune
            manimation.successYellow = new SDL_Texture* [manimPicture.animationSP->count];
            if (manimation.successYellow == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de succes jaune !!" << std::endl;
            }
            std::cout << "✅ creation de la texture de succes jaune !!" << std::endl;
            //concvertion en texture
            for (int j = 0; j < manimPicture.animationSP->count; j++) {
                manimation.successYellow[j] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationSY->frames[j]);
            }

            //animation du timer theme blanc
            manimation.timerBlack = new SDL_Texture* [manimPicture.animationTB->count];
            if (manimation.timerBlack == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de chrnometre noir !!" << std::endl;
            }
            std::cout << "✅ creation de la texture de chrnometre noir !!" << std::endl;
            for (int k = 0; k < manimPicture.animationTB->count; k++) {
                manimation.timerBlack[k] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationTB->frames[k]);
            }

            //animation du timer pour le theme jaune
            manimation.TimerYellow = new SDL_Texture* [manimPicture.animationTY->count];
            if (manimation.TimerYellow == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de chronometre jaune !!" << std::endl;
            }
            std::cout << "✅ creation de la texture de chronometre jaune !!" << std::endl;
            for (int l = 0; l < manimPicture.animationTY->count; l++) {
                manimation.TimerYellow[l] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationTY->frames[l]);
            }

            //animation de l'execution de la session de travail
            manimation.execution = new SDL_Texture* [manimPicture.animationEXE->count];
            if (manimation.execution == nullptr) {
                std::cout << "❌ Echec de la creation de la texture d'execution !!" << std::endl;
            }
            std::cout << "✅ creation de la texture d'execution !!" << std::endl;
            for (int p = 0; p < manimPicture.animationEXE->count; p++) {
                manimation.execution[p] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationEXE->frames[p]);
            }

            //animation des l'augmentation des statistiques par notifications
            manimation.graphics = new SDL_Texture* [manimPicture.animationGraph->count];
            if (manimation.graphics == nullptr) {
                std::cout << "❌ Echec de la creation de la texture de graphe !!" << std::endl;
            }
            std::cout << "✅ creation de la texture de graphe !!" << std::endl;
            for (int g = 0; g < manimPicture.animationGraph->count; g++) {
                manimation.graphics[g] = SDL_CreateTextureFromSurface(renderer, manimPicture.animationGraph->frames[g]);
            }
        }

        void windowUi::PlayAnimation(backEnd::animType animation, Uint64 lastTime) {
            //temps actuel lors de l'appel de la fenetre de notification
            Uint64 currentTime = SDL_GetTicks();
            //frame actuelle
            static int currentFrame = 0;
            //choix de l'animation a jouer en fonction de la notification passé vers
            //l'utilisateur
            switch (animation) {
                case backEnd::animType::SUCCESSPURPLE :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationSP->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationSP->count) {
                            currentFrame = 0;
                        }
                    }
                break;

                case backEnd::animType::SUCCESSYELLOW :

                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationSY->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationSY->count) {
                            currentFrame = 0;
                        }
                    }
                break;

                case backEnd::animType::TIMERBLACK :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationTB->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationTB->count) {
                            currentFrame = 0;
                        }
                    }
                break;

                case backEnd::animType::TIMERYELLOW :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationTY->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationTY->count) {
                            currentFrame = 0;
                        }
                    }
                break;

                case backEnd::animType::EXECUTION :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationEXE->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationEXE->count) {
                            currentFrame = 0;
                        }
                    }
                break;

                case backEnd::animType::GRAPH :
                    if (static_cast<int>(currentTime - lastTime) >= manimPicture.animationGraph->delays[currentFrame]) {
                        currentFrame++;
                        if (currentFrame >= manimPicture.animationGraph->count) {
                            currentFrame = 0;
                        }
                    }
                break;
            }
        }
        
        /**
         * @name CreateUITexture
         * @brief elle charge les differentes textures des icones dans le moteur de rendu pour 
         * l'affichage final.
         * @param renderer correspond au moteur de rendu a qui on passera les textures prealablement
         * crees.
         */
        void windowUi::CreateUITexture(SDL_Renderer* Renderer) {
            mtools.settingsTexture = Load_imageTexture(Renderer, "assets/tools/icons8-settings-100.png");
            mtools.chronoTexture = Load_imageTexture(Renderer, "assets/tools/timer_15553848.png");
            mtools.restTexture = Load_imageTexture(Renderer, "assets/tools/person_17580600.png");
            mtools.soundTexture = Load_imageTexture(Renderer, "assets/tools/icons8-musical-note-100.png");
            mtools.statistics =Load_imageTexture(Renderer, "assets/tools/icons8-analytique-100 (1).png");
            mtools.work = Load_imageTexture(Renderer, "assets/tools/work_6190606.png");
            mtools.coffee = Load_imageTexture(Renderer, "assets/tools/icons8-coffee-cup-100.png");
            mtools.pause = Load_imageTexture(Renderer, "assets/tools/icons8-pause-100.png");
            mtools.pompe = Load_imageTexture(Renderer, "assets/tools/icons8-pompes-100.png");
            //recuperation des dimensions
            SDL_GetTextureSize(mtools.settingsTexture, &settings.w, &settings.w);
            SDL_GetTextureSize(mtools.chronoTexture, &chrono.w, &chrono.h);
            SDL_GetTextureSize(mtools.restTexture, &rest.w, &rest.h);
            SDL_GetTextureSize(mtools.soundTexture, &sound.w, &sound.h);
            SDL_GetTextureSize(mtools.statistics, &statistic.w, &statistic.h);
            SDL_GetTextureSize(mtools.work, &work.w, &work.h);
            SDL_GetTextureSize(mtools.coffee, &coffee.w, &coffee.h);
            SDL_GetTextureSize(mtools.pause, &pause.w, &pause.h);
            SDL_GetTextureSize(mtools.pompe, &pompe.w, &pompe.h);
        }

        //style de UI
        // V3 theme v1.1
// - rlyeh, public domain
int windowUi::igThemeV3(int hue07, int alt07, int nav07, int lit01, int compact01, int border01, int shape0123) {
    bool rounded = shape0123 == 2;

    // V3 style from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();
    
    const float _8 = compact01 ? 4 : 8;
    const float _4 = compact01 ? 2 : 4;
    const float _2 = compact01 ? 0.5 : 1;

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.3f;

    style.WindowPadding = ImVec2(4, _8);
    style.FramePadding = ImVec2(4, _4);
    style.ItemSpacing = ImVec2(_8, _2 + _2);
    style.ItemInnerSpacing = ImVec2(4, 4);
    style.IndentSpacing = 16;
    style.ScrollbarSize = compact01 ? 12 : 18;
    style.GrabMinSize = compact01 ? 16 : 20;

    style.WindowBorderSize = border01;
    style.ChildBorderSize = border01;
    style.PopupBorderSize = border01;
    style.FrameBorderSize = 0;

    style.WindowRounding = 4;
    style.ChildRounding = 6;
    style.FrameRounding = shape0123 == 0 ? 0 : shape0123 == 1 ? 4 : 12;
    style.PopupRounding = 4;
    style.ScrollbarRounding = rounded * 8 + 4;
    style.GrabRounding = style.FrameRounding;

    style.TabBorderSize = 0;
    style.TabBarBorderSize = 2;
    style.TabBarOverlineSize = 2;
    style.TabCloseButtonMinWidthSelected = -1; // -1:always visible, 0:visible when hovered, >0:visible when hovered if minimum width
    style.TabCloseButtonMinWidthUnselected = -1;
    style.TabRounding = rounded;

    style.CellPadding = ImVec2(8.0f, 4.0f);

    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;

    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.5f, 0.5f);
    style.SeparatorTextAlign.x = 1.00f;
    style.SeparatorTextBorderSize = 1;
    style.SeparatorTextPadding = ImVec2(0,0);

    style.WindowMinSize = ImVec2(32.0f, 16.0f);
    style.ColumnsMinSpacing = 6.0f;

    // diamond sliders
    style.CircleTessellationMaxError = shape0123 == 3 ? 4.00f : 0.30f; 

    
    auto dim = [&](ImVec4 hi) {
        float h,s,v; ImGui::ColorConvertRGBtoHSV(hi.x,hi.y,hi.z, h,s,v);
        ImVec4 dim = ImColor::HSV(h,s,lit01 ? v*0.65:v*0.65, hi.w).Value;
        if( hi.z > hi.x && hi.z > hi.y ) return ImVec4(dim.x,dim.y,hi.z,dim.w);
        return dim;
    };

    const ImVec4 cyan    = ImVec4(000/255.f, 192/255.f, 255/255.f, 1.00f);
    const ImVec4 red     = ImVec4(230/255.f, 000/255.f, 000/255.f, 1.00f);
    const ImVec4 yellow  = ImVec4(240/255.f, 210/255.f, 000/255.f, 1.00f);
    const ImVec4 orange  = ImVec4(255/255.f, 144/255.f, 000/255.f, 1.00f);
    const ImVec4 lime    = ImVec4(192/255.f, 255/255.f, 000/255.f, 1.00f);
    const ImVec4 aqua    = ImVec4(000/255.f, 255/255.f, 192/255.f, 1.00f);
    const ImVec4 magenta = ImVec4(255/255.f, 000/255.f,  88/255.f, 1.00f);
    const ImVec4 purple  = ImVec4(192/255.f, 000/255.f, 255/255.f, 1.00f);

    ImVec4 alt = cyan;
    /**/ if( alt07 == 0 || alt07 == 'C' ) alt = cyan;
    else if( alt07 == 1 || alt07 == 'R' ) alt = red;
    else if( alt07 == 2 || alt07 == 'Y' ) alt = yellow;
    else if( alt07 == 3 || alt07 == 'O' ) alt = orange;
    else if( alt07 == 4 || alt07 == 'L' ) alt = lime;
    else if( alt07 == 5 || alt07 == 'A' ) alt = aqua;
    else if( alt07 == 6 || alt07 == 'M' ) alt = magenta;
    else if( alt07 == 7 || alt07 == 'P' ) alt = purple;
    if( lit01 ) alt = dim(alt);

    ImVec4 hi = cyan, lo = dim(cyan);
    /**/ if( hue07 == 0 || hue07 == 'C' ) lo = dim( hi = cyan );
    else if( hue07 == 1 || hue07 == 'R' ) lo = dim( hi = red );
    else if( hue07 == 2 || hue07 == 'Y' ) lo = dim( hi = yellow );
    else if( hue07 == 3 || hue07 == 'O' ) lo = dim( hi = orange );
    else if( hue07 == 4 || hue07 == 'L' ) lo = dim( hi = lime );
    else if( hue07 == 5 || hue07 == 'A' ) lo = dim( hi = aqua );
    else if( hue07 == 6 || hue07 == 'M' ) lo = dim( hi = magenta );
    else if( hue07 == 7 || hue07 == 'P' ) lo = dim( hi = purple );
//    if( lit01 ) { ImVec4 tmp = hi; hi = lo; lo = lit(tmp); }

    ImVec4 nav = orange;
    /**/ if( nav07 == 0 || nav07 == 'C' ) nav = cyan;
    else if( nav07 == 1 || nav07 == 'R' ) nav = red;
    else if( nav07 == 2 || nav07 == 'Y' ) nav = yellow;
    else if( nav07 == 3 || nav07 == 'O' ) nav = orange;
    else if( nav07 == 4 || nav07 == 'L' ) nav = lime;
    else if( nav07 == 5 || nav07 == 'A' ) nav = aqua;
    else if( nav07 == 6 || nav07 == 'M' ) nav = magenta;
    else if( nav07 == 7 || nav07 == 'P' ) nav = purple;
    if( lit01 ) nav = dim(nav);

    const ImVec4
    link  = ImVec4(0.26f, 0.59f, 0.98f, 1.00f),
    grey0 = ImVec4(0.04f, 0.05f, 0.07f, 1.00f),
    grey1 = ImVec4(0.08f, 0.09f, 0.11f, 1.00f),
    grey2 = ImVec4(0.10f, 0.11f, 0.13f, 1.00f),
    grey3 = ImVec4(0.12f, 0.13f, 0.15f, 1.00f),
    grey4 = ImVec4(0.16f, 0.17f, 0.19f, 1.00f),
    grey5 = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);

    #define Luma(v,a) ImVec4((v)/100.f,(v)/100.f,(v)/100.f,(a)/100.f)

    style.Colors[ImGuiCol_Text]                      = Luma(100,100);
    style.Colors[ImGuiCol_TextDisabled]              = Luma(39,100);
    style.Colors[ImGuiCol_WindowBg]                  = grey1;
    style.Colors[ImGuiCol_ChildBg]                   = ImVec4(0.09f, 0.10f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_PopupBg]                   = grey1;
    style.Colors[ImGuiCol_Border]                    = grey4;
    style.Colors[ImGuiCol_BorderShadow]              = grey1;
    style.Colors[ImGuiCol_FrameBg]                   = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]            = grey4;
    style.Colors[ImGuiCol_FrameBgActive]             = grey4;
    style.Colors[ImGuiCol_TitleBg]                   = grey0;
    style.Colors[ImGuiCol_TitleBgActive]             = grey0;
    style.Colors[ImGuiCol_TitleBgCollapsed]          = grey1;
    style.Colors[ImGuiCol_MenuBarBg]                 = grey2;
    style.Colors[ImGuiCol_ScrollbarBg]               = grey0;
    style.Colors[ImGuiCol_ScrollbarGrab]             = grey3;
    style.Colors[ImGuiCol_ScrollbarGrabHovered]      = lo;
    style.Colors[ImGuiCol_ScrollbarGrabActive]       = hi;
    style.Colors[ImGuiCol_CheckMark]                 = alt;
    style.Colors[ImGuiCol_SliderGrab]                = lo;
    style.Colors[ImGuiCol_SliderGrabActive]          = hi;
    style.Colors[ImGuiCol_Button]                    = ImVec4(0.10f, 0.11f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered]             = lo;
    style.Colors[ImGuiCol_ButtonActive]              = grey5;
    style.Colors[ImGuiCol_Header]                    = grey3;
    style.Colors[ImGuiCol_HeaderHovered]             = lo;
    style.Colors[ImGuiCol_HeaderActive]              = hi;
    style.Colors[ImGuiCol_Separator]                 = ImVec4(0.13f, 0.15f, 0.19f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered]          = lo;
    style.Colors[ImGuiCol_SeparatorActive]           = hi;
    style.Colors[ImGuiCol_ResizeGrip]                = Luma(15,100);
    style.Colors[ImGuiCol_ResizeGripHovered]         = lo;
    style.Colors[ImGuiCol_ResizeGripActive]          = hi;
    style.Colors[ImGuiCol_InputTextCursor]           = Luma(100,100);
    style.Colors[ImGuiCol_TabHovered]                = grey3;
    style.Colors[ImGuiCol_Tab]                       = grey1;
    style.Colors[ImGuiCol_TabSelected]               = grey3;
    style.Colors[ImGuiCol_TabSelectedOverline]       = hi;
    style.Colors[ImGuiCol_TabDimmed]                 = grey1;
    style.Colors[ImGuiCol_TabDimmedSelected]         = grey1;
    style.Colors[ImGuiCol_TabDimmedSelectedOverline] = lo;
    style.Colors[ImGuiCol_PlotLines]                 = grey5;
    style.Colors[ImGuiCol_PlotLinesHovered]          = lo;
    style.Colors[ImGuiCol_PlotHistogram]             = grey5;
    style.Colors[ImGuiCol_PlotHistogramHovered]      = lo;
    style.Colors[ImGuiCol_TableHeaderBg]             = grey0;
    style.Colors[ImGuiCol_TableBorderStrong]         = grey0;
    style.Colors[ImGuiCol_TableBorderLight]          = grey0;
    style.Colors[ImGuiCol_TableRowBg]                = grey3;
    style.Colors[ImGuiCol_TableRowBgAlt]             = grey2;
    style.Colors[ImGuiCol_TextLink]                  = link;
    style.Colors[ImGuiCol_TextSelectedBg]            = Luma(39,100);
    style.Colors[ImGuiCol_TreeLines]                 = Luma(39,100);
    style.Colors[ImGuiCol_DragDropTarget]            = nav;
    style.Colors[ImGuiCol_NavCursor]                 = nav;
    style.Colors[ImGuiCol_NavWindowingHighlight]     = lo;
    style.Colors[ImGuiCol_NavWindowingDimBg]         = Luma(0,63);
    style.Colors[ImGuiCol_ModalWindowDimBg]          = Luma(0,63);

    if( lit01 ) {
        for(int i = 0; i < ImGuiCol_COUNT; i++) {
            float H, S, V;
            ImVec4& col = style.Colors[i];
            ImGui::ColorConvertRGBtoHSV( col.x, col.y, col.z, H, S, V );
            if( S < 0.5 ) V = 1.0 - V, S *= 0.15;
            ImGui::ColorConvertHSVtoRGB( H, S, V, col.x, col.y, col.z );
        }
    }

    #undef Luma
    return 0;
}

#if 0
// demo
int theme = 0;
static int hue = 0, alt = 0, nav = 0, shape = 1;
static bool light = 0, compact = 0, borders = 0;
theme |= ImGui::SliderInt("Hue", &hue, 0, 7);
theme |= ImGui::SliderInt("Alt", &alt, 0, 7);
theme |= ImGui::SliderInt("Nav", &nav, 0, 7);
theme |= ImGui::SliderInt("Shape", &shape, 0, 3);
theme |= ImGui::Checkbox("Light", &light);
theme |= ImGui::Checkbox("Compact", &compact);
theme |= ImGui::Checkbox("Borders", &borders);
if(theme) igThemeV3(hue["CRYOLAMP"], alt["CRYOLAMP"], nav["CRYOLAMP"], light, compact, borders, shape);
#endif
    }
}