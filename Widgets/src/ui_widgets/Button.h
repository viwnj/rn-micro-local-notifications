#pragma once
#include <SDL.h>
#include "../Renderer.h"
#include "../geom/Dimension.h"
#include "../geom/Position.h"
#include "./Container.h"


typedef void(*function_ptr)();
class Button : public Container {
private:
	SDL_Rect rect;
	function_ptr on_click;
public:

	Button(Position pos, Dimension dim, function_ptr on_click) {
		rect = {
			pos.x,
			pos.y,
			dim.width,
			dim.height
		};
		this->on_click = on_click;
	}

	Button(Position pos, Dimension dim) {
		rect = {
			pos.x,
			pos.y,
			dim.width,
			dim.height
		};
	}

	void update() override {
	
	}
	


	void render() override {
		SDL_SetRenderDrawColor(Renderer::get_sdl_impl(), 255, 33, 33, 0);
		SDL_RenderFillRect(Renderer::get_sdl_impl(), &rect);
	}
};