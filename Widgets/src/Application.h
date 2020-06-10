#pragma once
#include <SDL.h>
#include <stdio.h>
#include "Renderer.h"
#include "geom/Dimension.h"
#include "geom/Position.h"

class Application
{
	private:
		const unsigned int FPS = 60;
		const unsigned int FRAME_TARGET_TIME = 1000 / FPS;
		SDL_Window* window;
		SDL_Event event;
		SDL_Renderer* renderer;
		bool should_quit;
		int ticks_last_frame;
		float get_delta_time();
public:
		Application();
		~Application();
		
		int init();
		void run();
		void update(float deltaTime);
		void process_input();
		void render();
		void on_mouse_press(SDL_MouseButtonEvent& button);
};
