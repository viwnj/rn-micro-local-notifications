#pragma once
#include <SDL2/SDL.h>
#include "../Renderer.h"
#include "../geom/Dimension.h"
#include "../geom/Position.h"
#include "./Container.h"

typedef void(*function_ptr)();
class Button : public Container {
private:
	SDL_Rect rect = {0, 0, 0, 0};
	function_ptr _onclick;
public:
	bool is_interactive = true;
	Button(Position&& pos, Dimension&& dim, function_ptr onclick);

	Button(Position&& pos, Dimension&& dim);

	Button(Position& pos, Dimension& dim, function_ptr onclick);

	Button(Position& pos, Dimension& dim);

	void update() override;

	void render() override;

	void onclick() override;

	SDL_Rect get_rect() override;
};