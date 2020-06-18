#include "Button.h"

Button::Button(Position&& pos, Dimension&& dim, function_ptr f) : Button(pos, dim, f) {}

Button::Button(Position&& pos, Dimension&& dim) : Button(pos, dim, NULL) {}

Button::Button(Position& pos, Dimension& dim, function_ptr f) : pos(pos), dim(dim), _onclick(f) {
	this->createBuffer();
	int screenWidth = 800;
	int screenHeight = 600;

	int halfScreenWidth = screenWidth / 2;
	int halfScreenHeight = screenHeight / 2;

	this->rect = new SDL_Rect{
		.x = (int)(halfScreenWidth + halfScreenWidth * pos.x),
		.y = (int)(halfScreenHeight - halfScreenHeight * pos.y),
		.w = (int)(halfScreenWidth * dim.width),
		.h = (int)(halfScreenHeight * dim.height)
	};
}

Button::Button(Position& pos, Dimension& dim) : Button(pos, dim, NULL) {}

void Button::createBuffer() {
	int endX = pos.x + dim.width;
	int endY = pos.y - dim.height;

	Position pos1(pos.x, pos.y);
	Position pos2(endX, pos.y);
	Position pos3(endX, endY);
	Position pos4(pos.x, endY);

	vertex_buffer_data = new GLfloat[24]{
		pos1.x, pos1.y, 0., 1.,1.,0.,
		pos2.x, pos2.y, 0., 1.,1.,1.,
		pos3.x, pos3.y, 0., 1.,0.,1.,
		pos4.x, pos4.y, 0., 1.,0.,0.
	};
}

void Button::render() {
	glBindVertexArray(vertex_buffer);
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(0);
}

void Button::update() {}

void Button::onclick() {
	if (_onclick) {
		_onclick();
	}
}

SDL_Rect Button::get_rect() {
	return *rect;
}
