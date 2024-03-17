/*
 * include/gpui/context.h
 *
 * defines context type as well as it's configuration and functionality
 */

#pragma once

struct SDL_Window;
typedef void* SDL_GLContext;

namespace gpui {

/**
 * Window context of the application, handles following operations:
 *  - Window create and destroy events
 *  - Input handling
 *  - OpenGL context initialization
 */
GPUI_API class Context {
public:
	Context(const char* title, u32 width, u32 height);
	~Context();

	bool is_running() const;

	void update();

private:
	SDL_Window* window;
	SDL_GLContext gl_context;

	bool running = true;
};

} // namespace gpui
