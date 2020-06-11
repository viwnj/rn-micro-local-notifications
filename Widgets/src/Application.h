#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <memory>
#include "Renderer.h"
#include "geom/Dimension.h"
#include "geom/Position.h"
#include "ui_widgets/Container.h"
#include "Collision.h"

class Application
{
	private:
		const unsigned int FPS = 60;
		const unsigned int FRAME_TARGET_TIME = 1000 / FPS;
		SDL_Window* window;
		SDL_Event event;
		SDL_Renderer* renderer;
		std::vector<std::shared_ptr<Container>> clickable_elements;
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
		template <typename T, typename ...TArgs>
		void add_widget(TArgs ...args) {
			std::shared_ptr<Container> widget = std::make_shared<T>(std::forward<TArgs>(args)...);

			if (widget->is_interactive) {
				clickable_elements.emplace_back(widget);
			}
		}
};