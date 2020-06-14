#pragma once

#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include "../SDL_FontCache/SDL_FontCache.h"

#include "Container.h"

SDL_Color colorFromInt(Uint32 value);

class Text : public Container {
private:

	/**
	 * @private attribute
	 *
	 * String which Text will represent.
	 */
	std::string str;

	/**
	 * @private attribute
	 *
	 * Number representing text's color.
	 */
	Uint32 color;

	/**
	 * @private attribute
	 *
	 * Font of the text.
	 */
	std::string font;

	/**
	 * @private attribute
	 *
	 * Loaded font based on Text::font.
	 */
	FC_Font *loadedFont = FC_CreateFont();

	/**
	 * @private method
	 *
	 * Alternative constructor with default values
	 */
	void construct(Uint32 color = 0xFFFFFFFF, std::string font = "Fira_Sans/FiraSans-Regular.ttf", Uint16 size = 19,
				   Uint8 ttf_style = TTF_STYLE_NORMAL);

public:
	/**
	 * @public constructor
	 *
	 * Construct a text class representing one string.
	 * Will use default color(white) and position(0, 0)
	 *
	 * @param str string to be represented.
	 * @param pos position of the string.
	 */
	Text(std::string str, Position pos);

	/**
	 * @public constructor
	 *
	 * Construct a text class representing one string.
	 *
	 * @param str string to be represented.
	 * @param pos position to draw string.
	 * @param color color to paint string.
	 */
	Text(std::string str, Position pos, Uint32 color);

	/**
	 * @public constructor
	 *
	 * Construct a text class representing one string.
	 *
	 * @param str string to be represented.
	 * @param pos position to draw string.
	 * @param color color to paint string.
	 * @param font .
	 */
	Text(std::string str, Position pos, Uint32 color, std::string font);

	void setPosition(Position pos);

	~Text();

	void render();
};