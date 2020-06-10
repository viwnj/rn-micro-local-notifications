#ifndef TRPG_RENDERER
#define TRPG_RENDERER
#include <SDL2/SDL.h>

class Renderer {

private:
	Renderer() {};
	SDL_Renderer* renderer;
public:	
	Renderer(const Renderer&) = delete;

	static Renderer& get_instance() {
		static Renderer instance;
		return instance;
	}

	static SDL_Renderer* get_sdl_impl() {
		return get_instance().renderer;
	}


	void init(SDL_Window* win) {
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			throw "The renderer could not be created";
		}
	}
};

#endif