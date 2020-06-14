#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>

#include "../Renderer.h"
#include "../geom/Position.h"
#include "../geom/Dimension.h"

class Container
{
protected:
	std::vector<Container*> children;
	Position position;
	Container* parent;
	Dimension dimension;
public:
	bool is_interactive;
	Container();
	Container(Position position);
	Container(Position position, Dimension dimension);
	virtual void render();
	virtual void update(){};
	virtual SDL_Rect get_rect() { return SDL_Rect{0, 0, 0, 0}; };
	virtual void onclick(){};
	void append_child(Container* container);
	void remove_child();
	void set_display_mode(std::string &display_mode);
	virtual void setPosition(Position p);
	Position getPosition();
	Dimension getDimension();
	void setParent(Container* parent);
};