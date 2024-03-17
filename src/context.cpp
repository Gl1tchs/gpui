#include "gpui/context.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

namespace gpui {

Context::Context(const char* title, u32 width, u32 height) {
	// Initialize SDL
	GPUI_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "");

	// Create an SDL window and OpenGL context
	window = SDL_CreateWindow(
			title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!window) {
		SDL_Quit();
		GPUI_LOG_FATAL("Failed to create SDL window: {}", SDL_GetError());
		GPUI_ASSERT(false);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Create an OpenGL context
	gl_context = SDL_GL_CreateContext(window);
	if (!gl_context) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		GPUI_LOG_FATAL(
				"Failed to create OpenGL ES context: {}", SDL_GetError());
		GPUI_ASSERT(false);
	}

	// Load OpenGL functions using Glad
	if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();
		GPUI_ASSERT(false, "Failed to initialize OpenGL ES context via Glad");
	}

#ifdef GPUI_DEBUG
	GPUI_LOG_INFO("GL Version: {}", (const char*)glGetString(GL_VERSION));
	GPUI_LOG_INFO("GL Vendor: {}", (const char*)glGetString(GL_VENDOR));
	GPUI_LOG_INFO("GL Renderer: {}", (const char*)glGetString(GL_RENDERER));
	GPUI_LOG_INFO("GL Shading Version: {}",
			(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif
}

Context::~Context() {
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Context::is_running() const { return running; }

void Context::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			running = false;
		}
	}

	// Clear the screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap buffers
	SDL_GL_SwapWindow(window);
}

} // namespace gpui
