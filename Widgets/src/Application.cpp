#include "Application.h"
#include "ui_widgets/Button.h"
#include "ui_widgets/Text.h"

Application::Application() : should_quit(false), ticks_last_frame(0) {
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

template<typename T, typename ...TArgs>
T* Application::add_widget(TArgs ...args) {
	T *widget = new T(std::forward<TArgs>(args)...);

	if (widget->is_interactive) {
		clickable_elements.emplace_back(widget);
	}

	return widget;
}

bool Application::init() {
	SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL2
	window = SDL_CreateWindow("Widgets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	Renderer::get_instance().init(window);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return false;
	}

	Button* a = this->add_widget<Button>(Position(230, 75), Dimension(200, 40), []() { std::cout << "Clicked button 1\n"; });
	Button* b = this->add_widget<Button>(Position(457, 349), Dimension(200, 40), []() { std::cout << "Clicked button 2\n"; });
	Text* t1 = new Text("Hai", Position(0, 0), 0xcc9222FF);
	Text* t2 = new Text("Hui", Position(0, 0), 0x3377AAFF);
	t1->setParent(a);
	t2->setParent(b);
	a->append_child(t1);
	b->append_child(t2);

	return true;
}

void Application::on_mouse_press(SDL_MouseButtonEvent &mouse_event) {
	if (mouse_event.button == SDL_BUTTON_LEFT) {
		SDL_Rect mouse_rect {
			mouse_event.x,
			mouse_event.y,
			20,
			20,
		};

		//  loop through clickable elements and see which one the mouse is currently colliding with
		for (auto &element : clickable_elements) {
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

void Application::render() {

	SDL_RenderClear(Renderer::get_sdl_impl());
	for (auto &element : clickable_elements) {
		if (element == NULL || !element || element == nullptr) {
			std::cout << "Element is null\n";
		} else {
			element->render();

		}
	}
	SDL_SetRenderDrawColor(Renderer::get_sdl_impl(), 33, 33, 33, 0);

	SDL_RenderPresent(Renderer::get_sdl_impl());
}

void Application::run() {

	while (!should_quit) {
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_last_frame + FRAME_TARGET_TIME));
		float deltaTime = this->get_delta_time();
		Application::render();
		Application::update(deltaTime);
		Application::process_input();
	}
}

void Application::update(float deltaTime) {

}