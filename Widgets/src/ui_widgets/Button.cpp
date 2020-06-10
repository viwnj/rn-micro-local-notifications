#include "Button.h"

Button::Button(Position & pos, Dimension & dim, function_ptr f) {
	rect = {
		pos.x,
		pos.y,
		dim.width,
		dim.height
	};
	this->on_click = on_click;
}

Button::Button(Position & pos, Dimension & dim) {
	rect = {
		pos.x,
		pos.y,
		dim.width,
		dim.height
	};
}

void Button::update() {}

void Button::render() {
	SDL_SetRenderDrawColor(Renderer::get_sdl_impl(), 255, 33, 33, 0);
	SDL_RenderFillRect(Renderer::get_sdl_impl(), &rect);
}