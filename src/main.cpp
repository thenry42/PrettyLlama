#include "Meta.hpp"
#include "Model.hpp"
#include "utils.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>


int	main(int ac, char **av)
{
	Meta meta;

	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " <prompt>" << std::endl;
		return (EXIT_FAILURE);
	}

	// Get Screen size
	int *size = getScreenSize();
	std::cout << "Screen size: " << size[0] << "x" << size[1] << std::endl;
	
	// Get models info using ollama list
	meta.getModelInfos();

	// Pass user prompt to every model
	meta.setPrompt(av[1]);

	// Aks models for answers
	//meta.askModels();

	// imgui build that work for my machine
	// - example_glfw_opengl2 (not the greatest)
	// - example_glfw_opengl3 (not the greatest)
	// - example_sdl2_opengl3
	// - example_sdl2_opengl2
	// - example_sdl2_sdlrenderer2
	
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return (EXIT_FAILURE);
	}

	// Create window with SDL_Renderer graphics context
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window* window = SDL_CreateWindow("Ollama_GUI <3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size[0], size[1], window_flags);
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

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	// Test state
	bool show_demo_window = true;

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

		// Rendering
		ImGui::Render();
		SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColor(renderer, 100, 50, 50, 255);
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
