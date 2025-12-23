#include "include/windowUI.h"
#include <iostream>

namespace App{
    namespace Uigraphics{
        windowUi::windowUi(float width, float height, float fontsize)
                : mio(nullptr), Uifont(nullptr), mtoggleConfig(nullptr) {
                    std::cout << "🛠️ cration de la fenetre imgui reussi !!"<<std::endl;
        }

        void windowUi::InitializeUi() {
            
        }
        
        //style de UI
        void windowUi::Uistyle() {
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
    }
}