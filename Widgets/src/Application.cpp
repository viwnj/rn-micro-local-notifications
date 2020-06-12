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



void f() {
	std::cout << "Oi" << std::endl;
}

int Application::init() {

	SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL2
	window = SDL_CreateWindow("Widgets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	Renderer::get_instance().init(window);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	add_widget<Button>(Position(0, 0), Dimension(200, 40), []() { std::cout << "Clicked button 1\n";  });
	add_widget<Button>(Position(0, 50), Dimension(200, 40), []() { std::cout << "Clicked button 2\n"; });

	return 0;
}


void Application::render() {

	SDL_RenderClear(Renderer::get_sdl_impl());
	for (auto& element : clickable_elements) {
		if (element == NULL || !element || element == nullptr) {
			std::cout << "Element is null\n";
		}
		else {
			element->render();

		}
	}
	SDL_SetRenderDrawColor(Renderer::get_sdl_impl(), 33, 33, 33, 0);

	SDL_RenderPresent(Renderer::get_sdl_impl());
}

void Application::on_mouse_press(SDL_MouseButtonEvent& mouse_event) {
	if (mouse_event.button == SDL_BUTTON_LEFT) {
		SDL_Rect mouse_rect{
			mouse_event.x,
			mouse_event.y,
			20,
			20,
		};
	
		//  loop through clickable elements and see which one the mouse is currently colliding with
		for (auto& element : clickable_elements) {
			if (Collision::CheckRectCollision(element->get_rect(), mouse_rect)) {
				element->onclick();
			}
		}
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

			case SDL_MOUSEMOTION:

			default:
				break;
		}

	}
}

void Application::update(float deltaTime) {

}


void Application::run() {

	while (!should_quit)	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_last_frame + FRAME_TARGET_TIME));
		float deltaTime = this->get_delta_time();
		Application::render();
		Application::update(deltaTime);
		Application::process_input();
	}
}

