#include "Text.h"

Uint8 bytePos(Uint32 value, Uint8 pos) {
	const int factor = pos * 8;
	return static_cast<Uint8>((value >> factor) & 0x000000FF);
}

SDL_Color colorFromInt(Uint32 value) {
	SDL_Color result = {
		.r = bytePos(value, 3),
		.g = bytePos(value, 2),
		.b = bytePos(value, 1),
		.a = bytePos(value, 0)
	};
	return result;
}

Text::Text(std::string str, Position pos) : str(str), Container(pos) {
	this->construct();
}

Text::Text(std::string str, Position pos, Uint32 color) : str(str), Container(pos) {
	this->construct(color);
}

Text::Text(std::string str, Position pos, Uint32 color, std::string font) : str(str), Container(pos) {
	this->construct(color, font);
}

Text::~Text() {
	FC_FreeFont(this->loadedFont);
}

void Text::setPosition(Position p) {
	if (this->parent != NULL && this->loadedFont != NULL) {
		int textWidth = FC_GetWidth(this->loadedFont, "%s", this->str.c_str());
		int textHeight = FC_GetHeight(this->loadedFont, "%s", this->str.c_str());
		Dimension parentDimension = this->parent->getDimension();
		p.x += (parentDimension.width - textWidth) / 2;
		p.y += (parentDimension.height - textHeight) / 2;
	}
	this->position = p;
}

void Text::construct(Uint32 color, std::string font, Uint16 size, Uint8 ttf_style) {
	this->color = color;
	this->font = font;
	std::string fontname = std::string("fonts/").append(font.c_str());
	SDL_Color sdlColor = colorFromInt(color);
	FC_LoadFont(this->loadedFont, Renderer::get_sdl_impl(), fontname.c_str(), size, sdlColor, ttf_style);
}

void Text::render() {
	int x = this->position.x;
	int y = this->position.y;
	this->parent->getPosition();
	FC_Draw(this->loadedFont, Renderer::get_sdl_impl(), x, y, this->str.c_str());
}