#include "interface.hpp"
#include "imgui.h"
#include "Meta.hpp"

void ShowMyOwnDearImGuiWindow(bool* p_open, Meta* meta)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    
    static bool no_titlebar = true;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = true;
    static bool no_resize = true;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;
    static bool unsaved_document = false;

    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
    if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

    // DO NOT REMOVE
    if (!ImGui::Begin("Ollama <3", p_open, window_flags))
    {
        ImGui::End();
        return;
    }

    // MENU BAR
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Models"))
        {
            std::map<string, Model*> models = meta->getModels();
            for (std::map<string, Model*>::iterator it = models.begin(); it != models.end(); it++)
                if (ImGui::Button(it->first.c_str()))
                    std::cout << "Button clicked: " << it->first << std::endl;
            
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Info"))
                std::cout << "Info clicked" << std::endl;
            ImGui::EndMenu();
        }
        
        ImGui::EndMenuBar();
    }

    // MAIN WINDOW 
    static bool info_tab = true;
    if (ImGui::BeginTabBar("TabBar"))
    {
        // INFO POP-UP
        if (info_tab)
        {    
            if (ImGui::TabItemButton("<3", ImGuiTabItemFlags_Leading))
            {
                if (ImGui::BeginPopupContextItem())
                {
                    ImGui::EndPopup();
                }
            }
            ImGui::SetItemTooltip("Add models with love <3");
            ImGui::NewLine();
            
            ImGui::SeparatorText("How it works");
            ImGui::Text("This simple UI allows you to interact with ollama models.");
            ImGui::Text("You can add models by clicking on the 'Models' tab.");
            ImGui::Text("You can then interact with the models by clicking on the model's name.");
            ImGui::NewLine();
        
            ImGui::SeparatorText("About");
        }

        // MODELS TAB
        /* Boucle qui itere sur tous les models dispo en tab */

        ImGui::EndTabBar();
    }

    ImGui::End();
}