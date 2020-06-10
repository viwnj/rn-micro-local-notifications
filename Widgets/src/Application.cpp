#include "Application.h"
#include "ui_widgets/Button.h"

Application::Application(): should_quit(false), ticks_last_frame(0) {
	this->init();
}

Application::~Application() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}


float Application::get_delta_time() {
	float deltaTime = (SDL_GetTicks() - ticks_last_frame) / 1000.0f;

	// Clamp deltaTime to a maximum value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	// Sets the new ticks for the current frame to be used in the next pass
	ticks_last_frame = SDL_GetTicks();

	return deltaTime;
}

int Application::init() {

	SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL2
	window = SDL_CreateWindow("Widgets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	Renderer::get_instance().init(window);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}

void f() {
	std::cout << "Oi" << std::endl;
}

void Application::render() {
	Position pos(0, 0);
	Dimension dim(200, 40);
	SDL_RenderClear(Renderer::get_sdl_impl());
	Button(pos, dim, f).render();
	SDL_SetRenderDrawColor(Renderer::get_sdl_impl(), 33, 33, 33, 0);

	SDL_RenderPresent(Renderer::get_sdl_impl());
}

void Application::on_mouse_press(SDL_MouseButtonEvent& mouse_event) {
	if (mouse_event.button == SDL_BUTTON_LEFT) {
		int x = mouse_event.x;
		int y = mouse_event.y;
		// if the mouse the is currently inside a widget, we'll proceed to check if that widget implements the onclick function?
		std::cout << "Left button pressed at x:" << x << " and y:" << y << "\n";
	}
}

void Application::process_input() {
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				should_quit = true;
			break;
			case SDL_MOUSEBUTTONDOWN:
				on_mouse_press(event.button);
				break;
			default:
				break;
		}

	}
}

void Application::update(float deltaTime) {

}


void Application::run() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_last_frame + FRAME_TARGET_TIME));
	float deltaTime = this->get_delta_time();


	while (!should_quit)	{
		Application::render();
		Application::update(deltaTime);
		Application::process_input();
	}


}

