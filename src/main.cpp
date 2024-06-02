#include "Meta.hpp"
#include "Model.hpp"
#include "utils.hpp"
#include "interface.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>

int	main(void)
{
	Meta meta;

	// Get Screen size
	int *size = getScreenSize();
	//std::cout << "Screen size: " << size[0] << "x" << size[1] << std::endl;
	
	// Get models info using ollama list
	meta.getOllamalist();

	// Pass user prompt to every model
	meta.setPrompt("What is love?");

	// Aks models for answers
	//meta.askModels();

	// MODELS TO USE
	meta.getModelByName("llama3")->setTabStatus(true);
	meta.getModelByName("phi3")->setTabStatus(true);
	meta.getModelByName("mistral")->setTabStatus(true);
	meta.getModelByName("llama3")->setNeedAnswer(true);
	meta.getModelByName("phi3")->setNeedAnswer(true);
	meta.getModelByName("mistral")->setNeedAnswer(true);

    // MODELS TO IGNORE
    meta.getModelByName("dolphin-mixtral")->setNeedAnswer(false);
    meta.getModelByName("starcoder2")->setNeedAnswer(false);
    meta.getModelByName("mixtral")->setNeedAnswer(false);

	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return (EXIT_FAILURE);
	}

	// Create window with SDL_Renderer graphics context
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window* window = SDL_CreateWindow("Ollama_UI <3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size[0], size[1], window_flags);
	if (window == nullptr)
	{
		std::cerr << SDL_GetError() << std::endl;
		return (EXIT_FAILURE);
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cerr << "Error creating SDL_Renderer!" << std::endl;
		return (EXIT_FAILURE);
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.IniFilename = NULL;

	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	// Test state
	bool show_demo_window = false;
	bool my_own_dear_imgui_window = true;

	// Main loop
	bool done = false;
	while (!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		// Start the Dear ImGui frame
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow()
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// Show our own dear ImGui window
		if (my_own_dear_imgui_window)
			ShowMyOwnDearImGuiWindow(&my_own_dear_imgui_window, &meta);

		// Rendering
		ImGui::Render();
		SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return (EXIT_SUCCESS);
}
