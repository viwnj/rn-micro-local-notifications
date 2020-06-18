#include "Application.h"
#include "ui_widgets/Button.h"

template<typename t, typename t2>
void report(t info, t2 error) {
	std::cout << info << error << std::endl;
}

template<typename t>
void report(t info) {
	return report(info, "");
}

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

template <typename T, typename ...TArgs>
void Application::add_widget(TArgs ...args) {
	T* widget = new T(std::forward<TArgs>(args)...);

	if (widget->is_interactive) {
		clickable_elements.emplace_back(widget);
	}
}

bool Application::init() {
	SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL2
	window = SDL_CreateWindow("Widgets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	Renderer::get_instance().init(window);

	if (window == NULL) {
		report("Could not create window: ", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	report("creating context", "");
	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_MakeCurrent(window, context);

	report("init glew");
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << std::endl;
		return false;
	}

	this->add_widget<Button>(Position(-1, 0), Dimension(1, 1), []() { std::cout << "Clicked button 1\n";  });
	this->add_widget<Button>(Position(0, 1), Dimension(1, 1), []() { std::cout << "Clicked button 2\n"; });

	report("setting fps");
	SDL_GL_SetSwapInterval(1);

	report("calling initGL");
	this->initGL();

	return true;
}

bool Application::initGL() {
	report("create program");
	this->gShader = new Shader("shaders/vertex", "shaders/fragment");

	return true;
}

void Application::on_mouse_press(SDL_MouseButtonEvent& mouse_event) {
	if (mouse_event.button == SDL_BUTTON_LEFT) {
		SDL_Rect mouse_rect{
			mouse_event.x,
			mouse_event.y,
			1,
			1,
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
	while (SDL_PollEvent(&event)) {
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

void Application::render() {

	//Clear color buffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//Bind program
	if (this->gShader != NULL) {
		this->gShader->use();
	}

	for (auto &element : clickable_elements) {
		if (element == NULL || !element || element == nullptr) {
			std::cout << "Element is null\n";
		} else {
			element->render();
		}
	}

	SDL_GL_SwapWindow(window);
}

void Application::run() {
	while (!should_quit)	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_last_frame + FRAME_TARGET_TIME));
		get_delta_time();
		Application::update();
		Application::render();
	}
}

void Application::update() {
	Application::process_input();
}