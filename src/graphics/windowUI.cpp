#include "../include/windowUI.h"
#include <iostream>

namespace App{
    namespace Uigraphics{
        windowUi::windowUi(float width, float height, float fontsize, ImGuiIO& io)
                : Uifont(nullptr), mio(io), mStyle(ImGui::GetStyle()), isInitialise(false) {
                    std::cout << "🛠️ cration de la fenetre imgui reussi !!"<<std::endl;
        }
         windowUi::~windowUi() {
            std::cout<<"destruction propre de imgui interface"<<std::endl;
         }

        void windowUi::InitializeUi(SDL_Renderer* renderer, SDL_Window* window) {
            mio.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            mtoggleConfig.Flags |= ImGuiToggleFlags_Animated;
            Uifont = mio.Fonts->AddFontFromFileTTF("police/Roboto/static/Roboto_Condensed-Black.ttf");
            //initialisation des paquet imgui
            ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
            ImGui_ImplSDLRenderer3_Init(renderer);
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