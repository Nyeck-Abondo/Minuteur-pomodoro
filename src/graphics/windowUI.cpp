#include "../include/windowUI.h"
#include "../libs/SDL3/SDL.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h"

namespace App{
    namespace Uigraphics{
        windowUi::windowUi(float width, float height, float fontsize, ImGuiIO& io)
                : Uifont(nullptr), mio(io), mStyle(ImGui::GetStyle()), isInitialise(false),
                mtools({nullptr, nullptr, nullptr, nullptr, nullptr}) {
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
            Uifont = mio.Fonts->AddFontFromFileTTF("police/Roboto/static/Roboto_Condensed-Black.ttf");
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
        }

        /**
         * @name parameterUi
         * @brief cette fontion est chargée d'afficher les options de parametrage de
         * l'application. elle comprend les reglages de volumes, les reglages des 
         * sessions de temps de travail et de repos, le nombre d'intervalle de repos
         * long
         * 
         * @param session_number -cette variable gere le  nombre de session pomodoro
         * ou encore connu sous le nom de session de concentration
         * @param workinTime -cette variable est en charge de la regulation du temps
         * de travail de l'utilisateur. elle varien entre 5 et 60 minutes pour assurer
         * une concentration optimale
         * @param short_breakTime Cette variable gère la durée des session de pause courtes.
         * elle varie entre 5 et 30 minutes, selon la convenance de l'utilisateur.
         * @param long_BreakTime Ce paramètre s'occupe de la définition de la durée des longues
         * sessions de pause. Elle s'étend de 20 à 60 minutes selon les préférences de lùutilisateur
         * @param long_BreakInterval defini une constente d'apparition des longues pauses.
         * elle peut varier entre 5 et 10. ces chiffres représentant le nombre de session pomodoro
         * repos court.
         * @param volume permet la gestion du vokume du minuteur
         * @param theme permet de changer le theme en arriere plan de la'application
         * @return nothing
         */
        void windowUi::ParameterUi(int session_mumber, int workingTime, int short_breakTime, int long_BreakTime, int long_BreakInterval, int volume, backEnd::OfficialTheme theme) {
            ImGui::SetNextWindowPos(ImVec2(251.0f, 400.0f), 0, ImVec2(0, 0.75f));
            ImGui::BeginChild("##parameter", ImVec2(500, 600), 0, ImGuiWindowFlags_Modal);

            //gestion du son de l'application
            ImGui::SeparatorText("Son");
            ImGui::Text("Volume");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::SliderInt(" ", &volume, 0, 100);
            ImGui::Text("Son actif");
            ImGui::SameLine(0.0f, 2.0f);
            ImGui::Toggle(" ", &activate_sound, ImGuiToggleFlags_Animated);

            //changement des themes dans le parametrage
            int current_item = -1;
            ImGui::SeparatorText("Theme de lapplication");
            ImGui::BeginCombo("Theme", usefullTheme);
            
            ImGui::SetCursorPos(ImVec2(250.0f - 100, 300.0f - 100.0f));
            ImGui::Image((ImTextureID)(intptr_t)mtools.profilTexture, ImVec2(200, 200));    

            ImGui::EndChild();
        }

        SDL_Texture* windowUi::Load_imageTexture(SDL_Renderer* renderer, const char* fileLocation) {
            int width, height, channels;
            unsigned char* image_data = stbi_load(fileLocation, &width, &height, &channels, 4);
            //verification du chargement de l'image en memoire
            if (!image_data) {
                std::cerr << "Erreur de chargement de l'image: " << stbi_failure_reason() << std::endl;
                return nullptr;
            }
            std::cout << "image : "<< fileLocation << " taille : " << width << " x " << height << std::endl;
            std::cout << "image : " << fileLocation << "chargee avec succes!" << std::endl; 
            //creation de la texutre
            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
            if (!texture) {
                std::cerr << "Erreur de creation de la texture: " << SDL_GetError() << std::endl;
                stbi_image_free(image_data);
                return nullptr;
            }
            //copie des pixel
            SDL_UpdateTexture(texture, nullptr, image_data, width * 4);
            //liberation de la memeoire
            stbi_image_free(image_data);
            return texture;
        }
        
        void windowUi::CreateUITexture(SDL_Renderer* Renderer) {
            mtools.settingsTexture = Load_imageTexture(Renderer, "assets/tools/icons8-slider-100.png");
            mtools.chronoTexture = Load_imageTexture(Renderer, "assets/tools/timer_15553848.png");
            mtools.profilTexture = Load_imageTexture(Renderer, "assets/tools/user_8104772.png");
            mtools.restTexture = Load_imageTexture(Renderer, "assets/tools/person_17580600.png");
            mtools.soundTexture = Load_imageTexture(Renderer, "assets/tools/icons8-musical-note-100.png");
            mtools.statistics =Load_imageTexture(Renderer, "assets/tools/icons8-analytique-100 (1).png");
            mtools.work = Load_imageTexture(Renderer, "assets/tools/icons8-travaux-de-jardinage-100 (1).png");
            //recuperation des dimensions
            SDL_GetTextureSize(mtools.settingsTexture, &settings.w, &settings.w);
            SDL_GetTextureSize(mtools.chronoTexture, &chrono.w, &chrono.h);
            SDL_GetTextureSize(mtools.profilTexture, &profile.w, &profile.h);
            SDL_GetTextureSize(mtools.restTexture, &rest.w, &rest.h);
            SDL_GetTextureSize(mtools.soundTexture, &sound.w, &sound.h);
            SDL_GetTextureSize(mtools.statistics, &statistic.w, &statistic.h);
            SDL_GetTextureSize(mtools.work, &work.w, &work.h);
        }

        //style de UI
        void windowUi::Uistyle() {
            mStyle = ImGui::GetStyle();
            mStyle.GrabRounding = 4.0f;
            mStyle.WindowRounding = 4.0f;
            mStyle.FrameRounding = 4.0f;
            mStyle.ChildRounding = 4.0f;
            mStyle.PopupRounding = 4.0f;
            //padding
            mStyle.WindowPadding = ImVec2(20, 20);
            mStyle.WindowBorderHoverPadding = 10.0f;
            mStyle.WindowPadding = ImVec2(8, 5);
            mStyle.FramePadding = ImVec2(6, 5);
            //spacing
            mStyle.ItemSpacing = ImVec2(10, 1);
            mStyle.ItemInnerSpacing = ImVec2(20, 5);
            mStyle.IndentSpacing = 20.0f;
            mStyle.GrabMinSize = 16.0f;
            //size
            mStyle.WindowBorderSize = 1.0f;
            //scrollbar
            mStyle.ScrollbarSize = 13.0f;
            mStyle.ScrollbarRounding = 4.0f;
            mStyle.ScrollbarPadding = 2.0f;
            //tab
            mStyle.TabRounding = 4.0f;
            mStyle.TabBorderSize = 4.0f;
            //window
            mStyle.WindowTitleAlign = ImVec2(0.5f, 0.5f);
            mStyle.WindowBorderHoverPadding = 6.0f;
            mStyle.WindowMenuButtonPosition = ImGuiDir_None;
            //button
            mStyle.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            mStyle.SelectableTextAlign = ImVec2(0.5, 0.5);
            mStyle.SeparatorTextAlign = ImVec2(1.0f, 0.5f);
            mStyle.SeparatorTextBorderSize = 2.0f;
            mStyle.DisplayWindowPadding = ImVec2(30, 20);

            ImVec4* color = mStyle.Colors;
            color[ImGuiCol_Text] = ImVec4(230.0f/255, 230.0f/255, 1.0f, 1.0f);
            color[ImGuiCol_TextDisabled] = ImVec4(135.0f/255.0f, 135.0f/255.0f, 135.0f/255.0f, 1.0f);
            color[ImGuiCol_WindowBg] = ImVec4(24.0f/255.0f, 25.0f/255.0f, 26.0f/255.0f, 1.0f);
            color[ImGuiCol_ChildBg] = ImVec4(85.0f/255.0f, 88.0f/255.0f, 89.0f/255.0f, 0.75f);
            color[ImGuiCol_PopupBg] = ImVec4(207.0f/ 255.0f, 204.0f/255.0f, 58.0f/255.0f, 0.5f);
            color[ImGuiCol_Border] = ImVec4(237.0f/255.0f, 230.0f/255.0f, 60.0f/255.0f, 0.5f);
            color[ImGuiCol_BorderShadow] = ImVec4(112.0f/255.0f, 109.0f/255.0f, 29.0f/255.0f, 0.5f);
            color[ImGuiCol_FrameBg] = ImVec4(224.0f/255.0f, 202.0f/255.0f, 17.0f/255.0f, 0.75f);
            color[ImGuiCol_FrameBgHovered] = ImVec4(250.0f/255.0f, 225.0f/255.0f, 19.0f/255.0f, 0.5);
            color[ImGuiCol_FrameBgActive] = ImVec4(250.0f/255.0f, 225.0f/255.0f, 19.0f/255.0f, 0.5);
            color[ImGuiCol_TitleBg] = ImVec4(224.0f/255.0f, 202.0f/255.0f, 17.0f/255.0f, 0.75f);
            color[ImGuiCol_TitleBgActive] = ImVec4(224.0f/255.0f, 202.0f/255.0f, 17.0f/255.0f, 0.75f);
            color[ImGuiCol_TitleBgCollapsed] = ImVec4(41.0f/255.0f, 40.0f/255.0f, 39.0f/255.0f, 0.75f);
            color[ImGuiCol_MenuBarBg] = ImVec4(59.0f/255.0f, 57.0f/255.0f , 55.0f/255.0f, 0.75f);
            color[ImGuiCol_ScrollbarBg] = ImVec4(245.0f/255.0f, 233.0f/255.0f, 60.0f/255.0f, 0.75f);
            color[ImGuiCol_ScrollbarGrab] = ImVec4(250.0f/255.0f, 225.0f/255.0f, 19.0f/255.0f, 0.5);
            color[ImGuiCol_ScrollbarGrabHovered] = ImVec4(245.0f/255.0f, 213.0f/255.0f, 40.0f/255.0f, 0.75f);
            color[ImGuiCol_ScrollbarGrabActive] = ImVec4(250.0f/255.0f, 225.0f/255.0f, 19.0f/255.0f, 0.5);
            color[ImGuiCol_CheckMark] = ImVec4(250.0f/255.0f, 225.0f/255.0f, 19.0f/255.0f, 0.5);
            color[ImGuiCol_SliderGrab] = ImVec4(250.0f/255.0f, 225.0f/255.0f, 19.0f/255.0f, 0.5);
            color[ImGuiCol_SliderGrabActive] =ImVec4(250.0f/255.0f, 225.0f/255.0f, 19.0f/255.0f, 0.5);
            color[ImGuiCol_Button] = ImVec4(131.0/255.0f, 133.0f/255.0f, 126.0f, 0.70f); 
            color[ImGuiCol_ButtonHovered] = ImVec4(250.0f/255.0f, 225.0f/255.0f, 19.0f/255.0f, 0.5);
            color[ImGuiCol_ButtonActive] = ImVec4(222.0f/255.0f, 195.0f/255.0f, 50.0f/255.0f, 0.70f);
            color[ImGuiCol_TextSelectedBg] = ImVec4(218.0f/255.0f, 218.0f/255.0f, 71.0f/255.0f, 0.70f);

        }
    }
}