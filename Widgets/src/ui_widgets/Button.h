#pragma once
#include <SDL2/SDL.h>
#include "GL/glew.h"
#include "../geom/Dimension.h"
#include "../geom/Position.h"
#include "./Container.h"

typedef void(*function_ptr)();
class Button : public Container {
private:
	SDL_Rect* rect;
	Position pos;
	Dimension dim;
	function_ptr _onclick;
	GLfloat* vertex_buffer_data;
	GLuint vertex_buffer;

	void createBuffer();
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