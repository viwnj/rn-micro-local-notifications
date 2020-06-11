#include "Button.h"

Button::Button(Position&& pos, Dimension&& dim, function_ptr f) {
	rect = {
		pos.x,
		pos.y,
		dim.width,
		dim.height
	};
	this->_onclick= f;
}

Button::Button(Position&& pos, Dimension&& dim) {
	rect = {
		pos.x,
		pos.y,
		dim.width,
		dim.height
	};
}


Button::Button(Position& pos, Dimension& dim, function_ptr f) {
	rect = {
		pos.x,
		pos.y,
		dim.width,
		dim.height
	};
	this->_onclick = f;
}

Button::Button(Position& pos, Dimension& dim) {
	rect = {
		pos.x,
		pos.y,
		dim.width,
		dim.height
	};
}


void Button::render() {
	SDL_SetRenderDrawColor(Renderer::get_sdl_impl(), 255, 33, 33, 0);
	SDL_RenderFillRect(Renderer::get_sdl_impl(), &rect);
}

void Button::update() {}

void Button::onclick() {
	if (_onclick) {
		_onclick();
	}
}

SDL_Rect Button::get_rect() {
	return rect;
}
