#include "Button.h"

Button::Button(Position&& pos, Dimension&& dim, function_ptr f) : Container(pos, dim) {
	rect = {
		pos.x,
		pos.y,
		dim.width,
		dim.height
	};
	this->_onclick= f;
}

Button::Button(Position&& pos, Dimension&& dim) : Button(pos, dim, NULL) {}

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
	// SDL_SetRenderDrawColor(Renderer::get_sdl_impl(), 255, 33, 33, 0);
	// SDL_RenderFillRect(Renderer::get_sdl_impl(), &rect);
	Sint16 x1 = rect.x;
	Sint16 y1 = rect.y;
	Sint16 x2 = rect.x + rect.w;
	Sint16 y2 = rect.y + rect.h;
	Sint16 radius = 10;
	Uint32 color = 0xFF2121FF;
	roundedBoxColor(Renderer::get_sdl_impl(), x1, y1, x2, y2, radius, color);
	Container::render();
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
