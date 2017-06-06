#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string> 

class display
{
public:
	display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void Update();
	bool IsClosed();

	virtual ~display();

protected:

private:
	display(const display& other) {}
	void operator=(const display& other) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;

};

#endif DISPLAY_H

