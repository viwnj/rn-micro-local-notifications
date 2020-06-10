#pragma once
#include <SDL2/SDL.h>
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

	Button(Position&& pos, Dimension&& dim, function_ptr on_click);

	Button(Position&& pos, Dimension&& dim);

	Button(Position& pos, Dimension& dim, function_ptr on_click);

	Button(Position& pos, Dimension& dim);

	void update() override;

	void render() override;
};