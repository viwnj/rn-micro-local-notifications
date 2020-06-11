#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
class Container
{
protected:
	std::vector<Container> children;

public:
	bool is_interactive;
	Container();
	virtual void render(){};
	virtual void update(){};
	virtual SDL_Rect get_rect() { return SDL_Rect{0, 0, 0, 0}; };
	virtual void onclick(){};
	void append_child(Container container);
	void remove_child();
	void set_display_mode(std::string &display_mode);
};